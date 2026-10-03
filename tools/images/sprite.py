"""Convert between indexed PNG sprites and their ROM tile, frame, and palette data.

See docs/formats/graphics.md ("Sprite images"). A bank.json image entry is
one of:

- a derived sprite, {name, offset, compression}: one frame, <name>.png,
  OAM cells cut from the image size (cut_cells);
- a stored-layout sprite, {name, palette, header, frames}: <name>.<i>.png
  per frame, each frame listing its offset, compression, OAM cells (in
  tiles), attached parts, and extra halfwords;
- a palette, {name, paletteOnly}: <name>.png, a swatch whose PNG palette
  is the data. highBits lists the entries whose unused bit 15 is set, which
  a PNG palette cannot hold.

Components: palette (2**bpp BGR555 entries from the PNG palette), tiles
(each frame's cell tiles, compressed, one stream per frame), and frames
(an ObjectFrameData record).
"""
import hashlib
import json
import os
import struct
import sys
from concurrent.futures import ProcessPoolExecutor
from itertools import repeat
from pathlib import Path

from PIL import Image

sys.path.insert(0, str(Path(__file__).parent.parent / "graphics"))
from decode_bios import rl_uncomp  # noqa: E402
from decode_gamma_lz import decode_gamma_lz_with_end  # noqa: E402
from decode_lz_rle import decode_lz_rle  # noqa: E402
from encode_bios_rle import encode_bios_rle  # noqa: E402
from encode_gamma_lz import encode_gamma_lz  # noqa: E402
from encode_lz_rle import encode_lz_rle  # noqa: E402

ROM_BASE = 0x08000000
COMPONENT_KINDS = ("palette", "tiles", "frames")

# DecompressResourceVram type per codec, and the value of the frame
# descriptor's bCellCount bits 5-7 that accompanies it in every ROM sprite.
# bCellCount bits 5-7 are 0 for both raw and GammaLz frames; their codec
# comes from the tile stream's resource header.
COMPRESSION_TYPES = {"raw": 0, "rle": 3, "gammalz": 6, "lzrle": 7}
CELL_COUNT_FLAGS = {"raw": 0x00, "rle": 0x20, "gammalz": 0x00, "lzrle": 0x40}
# Every tile stream ends with padding bytes. They are usually zero; the few
# nonzero values are not derived from the data and are stored in the
# frame's "padding" setting.
PADDING_WORD = 4
GAMMA_LZ_CACHE = Path("build/cache/gammalz")

# (width, height) in tiles -> (OAM shape, OAM size)
OAM_SHAPES = {
    (1, 1): (0, 0), (2, 2): (0, 1), (4, 4): (0, 2), (8, 8): (0, 3),
    (2, 1): (1, 0), (4, 1): (1, 1), (4, 2): (1, 2), (8, 4): (1, 3),
    (1, 2): (2, 0), (1, 4): (2, 1), (2, 4): (2, 2), (4, 8): (2, 3),
}
SHAPE_TILES = {code: wh for wh, code in OAM_SHAPES.items()}
MAX_TILES_PER_SIDE = 15
FRAME_HEADER_SIZE = 0xC
FRAME_DESC_SIZE = 0xA
PART_SIZE = 6


def _align4(n: int) -> int:
    return (n + 3) & ~3


def _bands(tiles: int) -> list[int]:
    """Power-of-two strips, smallest first: 7 -> [1, 2, 4]."""
    return [1 << bit for bit in range(4) if tiles & (1 << bit)]


def _split(x: int, y: int, w: int, h: int) -> list[tuple[int, int, int, int]]:
    if (w, h) in OAM_SHAPES:
        return [(x, y, w, h)]
    if w > h:
        return _split(x, y, w // 2, h) + _split(x + w // 2, y, w // 2, h)
    return _split(x, y, w, h // 2) + _split(x, y + h // 2, w, h // 2)


def cut_cells(width_tiles: int, height_tiles: int) -> list[tuple[int, int, int, int]]:
    """OAM cells (x, y, w, h in tiles) covering the image, in ROM order.

    Each dimension is split into power-of-two strips, smallest first. Cells
    are emitted by row strip, then column strip; a strip intersection with
    no OAM shape is halved along its longer side.
    """
    for tiles in (width_tiles, height_tiles):
        if not 1 <= tiles <= MAX_TILES_PER_SIDE:
            raise ValueError(f"sprite side of {tiles} tiles is outside 1..{MAX_TILES_PER_SIDE}")
    cells = []
    y = 0
    for h in _bands(height_tiles):
        x = 0
        for w in _bands(width_tiles):
            cells += _split(x, y, w, h)
            x += w
        y += h
    return cells


def encode_palette(colors: list[tuple[int, int, int]], bpp: int) -> bytes:
    count = 1 << bpp
    if len(colors) > count:
        raise ValueError(f"palette has {len(colors)} colors; {bpp}bpp allows {count}")
    colors = list(colors) + [(0, 0, 0)] * (count - len(colors))
    return b"".join(struct.pack("<H", (r >> 3) | (g >> 3) << 5 | (b >> 3) << 10) for r, g, b in colors)


def decode_palette(data: bytes, bpp: int) -> list[tuple[int, int, int]]:
    if len(data) != 2 << bpp:
        raise ValueError(f"palette is {len(data)} bytes; {bpp}bpp needs {2 << bpp}")
    colors = []
    for (value,) in struct.iter_unpack("<H", data):
        if value & 0x8000:
            raise ValueError(f"palette entry {value:#06x} sets bit 15")
        channels = (value & 0x1F, (value >> 5) & 0x1F, (value >> 10) & 0x1F)
        colors.append(tuple(c << 3 | c >> 2 for c in channels))
    return colors


def high_bits(data: bytes) -> list[int]:
    """Indices of the palette entries whose unused bit 15 is set."""
    return [i for i, value in enumerate(struct.unpack(f"<{len(data) // 2}H", data)) if value & 0x8000]


def clear_high_bits(data: bytes) -> bytes:
    return bytes(b & 0x7F if i & 1 else b for i, b in enumerate(data))


def set_high_bits(data: bytes, indices: list[int]) -> bytes:
    out = bytearray(data)
    for i in indices:
        out[i * 2 + 1] |= 0x80
    return bytes(out)


def gray_palette(bpp: int) -> list[tuple[int, int, int]]:
    """Display palette for a sprite whose palette lives outside its bank."""
    count = 1 << bpp
    return [(v, v, v) for v in (i * 255 // (count - 1) for i in range(count))]


def _cell_pixels(cells):
    """Yield (x, y) for every pixel in tile-data order."""
    for cx, cy, cw, ch in cells:
        for ty in range(cy, cy + ch):
            for tx in range(cx, cx + cw):
                for y in range(ty * 8, ty * 8 + 8):
                    for x in range(tx * 8, tx * 8 + 8):
                        yield x, y


def pack_pixels(pixels: list[int], width: int, cells, bpp: int) -> bytes:
    ordered = [pixels[y * width + x] for x, y in _cell_pixels(cells)]
    if bpp == 8:
        return bytes(ordered)
    return bytes(lo | hi << 4 for lo, hi in zip(ordered[0::2], ordered[1::2]))


def unpack_pixels(data: bytes, width: int, height: int, cells, bpp: int) -> list[int]:
    if bpp == 8:
        values = list(data)
    else:
        values = [v for byte in data for v in (byte & 0xF, byte >> 4)]
    pixels = [0] * (width * height)
    for value, (x, y) in zip(values, _cell_pixels(cells)):
        pixels[y * width + x] = value
    return pixels


def _gamma_lz(raw: bytes) -> bytes:
    """encode_gamma_lz, cached by input hash under build/ (it is slow)."""
    path = GAMMA_LZ_CACHE / f"{hashlib.sha256(raw).hexdigest()}.bin"
    try:
        return path.read_bytes()
    except FileNotFoundError:
        pass
    encoded = encode_gamma_lz(raw)
    path.parent.mkdir(parents=True, exist_ok=True)
    tmp = path.with_suffix(f".{os.getpid()}.tmp")
    tmp.write_bytes(encoded)
    tmp.replace(path)
    return encoded


def _stream_body(raw: bytes, compression: str) -> tuple[bytes, int]:
    """A tile stream without its trailing padding, and the padding length.

    LzRle and RLE streams end with zero bytes to a word boundary at least
    four or five bytes past the header and tokens (LzRle's end token counts
    as the first); raw and GammaLz streams end on a word boundary followed
    by one padding word. GammaLz writes its own header."""
    if compression not in COMPRESSION_TYPES:
        raise ValueError(f"unknown compression {compression!r}")
    header = struct.pack("<I", COMPRESSION_TYPES[compression] << 4 | len(raw) << 8)
    if compression == "gammalz":
        body = _gamma_lz(raw)
        return body, PADDING_WORD
    if compression == "raw":
        body = (header + raw).ljust(_align4(4 + len(raw)), b"\0")
        return body, PADDING_WORD
    if compression == "lzrle":
        body = header + encode_lz_rle(raw)
        return body, _align4(len(body) + 4) - len(body)
    # DecompressResourceVram passes header+4 to the BIOS, which reads its
    # own copy of the header there.
    body = header + encode_bios_rle(raw)
    return body, _align4(len(body) + 5) - len(body)


def compress_tiles(raw: bytes, compression: str, padding: list[int] | None = None) -> bytes:
    """Resource header, compressed stream, and padding (zero unless given)."""
    body, length = _stream_body(raw, compression)
    if padding is None:
        padding = [0] * length
    elif len(padding) != length:
        raise ValueError(f"{compression} stream needs {length} padding bytes, not {len(padding)}")
    return body + bytes(padding)


def _decompress_gamma_lz(data: bytes) -> tuple[bytes, int]:
    """Decoded tiles and the stream length, excluding the padding word."""
    raw, end = decode_gamma_lz_with_end(data, ROM_BASE)
    return raw, end - ROM_BASE


def decompress_tiles(data: bytes) -> tuple[bytes, str]:
    header = struct.unpack_from("<I", data)[0]
    size = header >> 8
    by_type = {t: name for name, t in COMPRESSION_TYPES.items()}
    compression = by_type.get(header >> 4 & 0xF) if header & 0x8F == 0 else None
    if header & 0xFF in (0x60, 0xE0):  # GammaLz carries its delta flag in bit 7
        compression = "gammalz"
    if compression == "gammalz":
        raw = _decompress_gamma_lz(data)[0]
    elif compression == "raw":
        if not size or size % 32 or 4 + size > len(data):
            raise ValueError(f"raw tiles of {size} bytes do not fit")
        raw = data[4:4 + size]
    elif compression == "lzrle":
        raw = decode_lz_rle(data, ROM_BASE + 4)
    elif compression == "rle":
        if struct.unpack_from("<I", data, 4)[0] != header:
            raise ValueError("RLE tiles lack the duplicated BIOS header")
        raw = rl_uncomp(data, ROM_BASE + 4)
    else:
        raise ValueError(f"unsupported tile resource header {header:#010x}")
    if len(raw) != size:
        raise ValueError(f"tiles decode to {len(raw)} bytes; header declares {size}")
    return raw, compression


def tile_stream_length(data: bytes) -> int | None:
    """Length of the tile stream starting `data`, or None if none starts there."""
    try:
        raw, compression = decompress_tiles(data)
        if compression in ("raw", "gammalz"):
            # Not re-encoded here; the rebuilt sprite is compared later.
            length = _body_length(data, compression, raw) + PADDING_WORD
            return length if length <= len(data) else None
    except (ValueError, IndexError, struct.error):
        return None
    body, padding = _stream_body(raw, compression)
    length = len(body) + padding
    return length if data[:len(body)] == body and length <= len(data) else None


def _body_length(stream: bytes, compression: str, raw: bytes) -> int:
    """Length of a ROM tile stream before its padding."""
    if compression == "gammalz":
        return _decompress_gamma_lz(stream)[1]
    if compression == "raw":
        return _align4(4 + len(raw))
    return len(_stream_body(raw, compression)[0])


def encode_frames(frames: list[dict], header: list[int]) -> bytes:
    """ObjectFrameData for frames of {width, height, offset, compression, cells, parts, extra},
    each frame's tiles being its own stream of the given byte lengths."""
    extra_count = len(frames[0]["extra"])
    part_count = len(frames[0]["parts"])
    width = max(f["width"] for f in frames)
    height = max(f["height"] for f in frames)
    tile_bytes = max(f["tile_bytes"] for f in frames)
    if tile_bytes > 0xFFFF or width > 0xFF or height > 0xFF:
        raise ValueError(f"{width}x{height} sprite exceeds the frame record's fields")
    out = bytearray(struct.pack("<BB4bHHBB", width, height, *header, len(frames),
                                tile_bytes, extra_count, part_count))
    desc_size = FRAME_DESC_SIZE + extra_count * 2 + part_count * PART_SIZE
    offset = 2 * len(frames)
    for f in frames:
        out += struct.pack("<H", offset)
        offset += desc_size + 4 * len(f["cells"])
    tile_offset = 0
    for f in frames:
        if len(f["extra"]) != extra_count or len(f["parts"]) != part_count:
            raise ValueError("every frame needs the same number of extra halfwords and parts")
        if len(f["cells"]) > 0x1F:
            raise ValueError(f"{len(f['cells'])} cells exceed the 5-bit cell count")
        ox, oy = f["offset"]
        out += struct.pack("<BBBBHhh", len(f["cells"]) | CELL_COUNT_FLAGS[f["compression"]], 0,
                           f["width"], f["height"], tile_offset, ox, oy)
        out += struct.pack(f"<{extra_count}H", *f["extra"])
        for part in f["parts"]:
            out += struct.pack("<6b", *part)
        tile = 0
        for cx, cy, cw, ch in f["cells"]:
            x, y = ox + cx * 8, oy + cy * 8
            if not (-256 <= x < 256 and -256 <= y < 256):
                raise ValueError(f"cell position ({x}, {y}) exceeds the 9-bit OAM range")
            if tile >= 1 << 10:
                raise ValueError(f"cell tile offset {tile} exceeds 10 bits")
            shape, size = OAM_SHAPES[(cw, ch)]
            out += struct.pack("<I", (x & 0x1FF) | (y & 0x1FF) << 9 | size << 18 | shape << 20 | tile << 22)
            tile += cw * ch
        tile_offset += f["stream_bytes"]
    return bytes(out).ljust(_align4(len(out)), b"\0")


def _sign9(value: int) -> int:
    value &= 0x1FF
    return value - 0x200 if value & 0x100 else value


def decode_frames(data: bytes) -> dict:
    """Parse an ObjectFrameData record; returns its fields and byte length,
    including the zero padding to a word boundary."""
    width, height = data[0], data[1]
    header = list(struct.unpack_from("<4b", data, 2))
    frame_count, tile_bytes, extra_count, part_count = struct.unpack_from("<HHBB", data, 6)
    offsets = struct.unpack_from(f"<{frame_count}H", data, FRAME_HEADER_SIZE)
    # Flag 0 leaves the codec to the tile stream header (see resolve_compressions).
    by_flag = {0x00: None, 0x20: "rle", 0x40: "lzrle"}
    frames = []
    end = FRAME_HEADER_SIZE + 2 * frame_count
    for offset in offsets:
        base = FRAME_HEADER_SIZE + offset
        if base != end:
            raise ValueError("frame descriptors are not stored in order")
        count_flags, unused, fw, fh, tile_offset, ox, oy = struct.unpack_from("<BBBBHhh", data, base)
        flags = count_flags & 0xE0
        if flags not in by_flag or unused:
            raise ValueError(f"unsupported frame descriptor flags {count_flags:#04x}/{unused:#04x}")
        pos = base + FRAME_DESC_SIZE
        extra = list(struct.unpack_from(f"<{extra_count}H", data, pos))
        pos += 2 * extra_count
        parts = [list(struct.unpack_from("<6b", data, pos + PART_SIZE * i)) for i in range(part_count)]
        pos += PART_SIZE * part_count
        cells = []
        tile = 0
        for i in range(count_flags & 0x1F):
            word = struct.unpack_from("<I", data, pos + 4 * i)[0]
            x, y = _sign9(word) - ox, _sign9(word >> 9) - oy
            cw, ch = SHAPE_TILES[((word >> 20) & 3, (word >> 18) & 3)]
            if x % 8 or y % 8 or word >> 22 != tile:
                raise ValueError("cell is not tile-aligned or out of tile order")
            cells.append([x // 8, y // 8, cw, ch])
            tile += cw * ch
        end = pos + 4 * len(cells)
        frames.append({"width": fw, "height": fh, "tile_offset": tile_offset, "offset": [ox, oy],
                       "compression": by_flag[flags], "extra": extra, "parts": parts, "cells": cells})
    if any(data[end:_align4(end)]):
        raise ValueError("frame record padding is not zero")
    end = _align4(end)
    return {"width": width, "height": height, "header": header, "tile_bytes": tile_bytes,
            "frames": frames, "length": end}


def component_length(kind: str, data: bytes, bpp: int) -> int:
    """Byte length of the component that starts `data`, read from the
    component itself. Tiles here means a single frame's stream."""
    if kind == "palette":
        return 2 << bpp
    if kind == "tiles":
        length = tile_stream_length(data)
        if length is None:
            raise ValueError("no tile stream starts here")
        return length
    if kind == "frames":
        return decode_frames(data)["length"]
    raise ValueError(f"unknown component kind {kind!r}")


def read_png(path: Path, bpp: int) -> tuple[int, int, list[int], list[tuple[int, int, int]]]:
    with Image.open(path) as image:
        if image.mode != "P":
            raise ValueError(f"expected an indexed-color PNG, got mode {image.mode}")
        width, height = image.size
        flat = image.getpalette() or []
        colors = [tuple(flat[i:i + 3]) for i in range(0, len(flat), 3)]
        pixels = list(image.get_flattened_data())
    if max(pixels) >= 1 << bpp:
        raise ValueError(f"pixel index {max(pixels)} exceeds {bpp}bpp")
    encode_palette(colors, bpp)
    return width, height, pixels, colors


def write_png(path: Path, width: int, height: int, pixels: list[int],
              colors: list[tuple[int, int, int]], bpp: int) -> None:
    image = Image.new("P", (width, height))
    image.putpalette([c for color in colors for c in color])
    image.putdata(pixels)
    # Index 0 is the OBJ transparent color; its stored RGB stays in PLTE.
    image.save(path, bits=bpp, transparency=0)


def image_files(entry: dict) -> list[str]:
    """PNG file names an image entry uses."""
    if "frames" in entry:
        return [f"{entry['name']}.{i}.png" for i in range(len(entry["frames"]))]
    return [f"{entry['name']}.png"]


def _frame_tiles(path: Path, frame_cells, bpp: int):
    width, height, pixels, colors = read_png(path, bpp)
    if width % 8 or height % 8:
        raise ValueError(f"{path.name}: {width}x{height} is not a multiple of 8 pixels")
    cells = frame_cells(width // 8, height // 8)
    covered = set(_cell_pixels(cells))
    stray = [(x, y) for y in range(height) for x in range(width)
             if pixels[y * width + x] and (x, y) not in covered]
    if stray:
        raise ValueError(f"{path.name}: pixel {stray[0]} lies outside every OAM cell")
    return width, height, cells, pack_pixels(pixels, width, cells, bpp), colors


def build(source: Path, entry: dict, bpp: int) -> dict[str, bytes]:
    """Encode one bank.json image entry into its ROM components."""
    bpp = entry.get("bpp", bpp)
    if entry.get("paletteOnly"):
        _, _, _, colors = read_png(source / f"{entry['name']}.png", bpp)
        return {"palette": set_high_bits(encode_palette(colors, bpp), entry.get("highBits", []))}
    if "frames" in entry:
        specs = entry["frames"]
        header = entry["header"]
        own_palette = entry["palette"]
    else:
        specs = [{"offset": entry["offset"], "compression": entry["compression"],
                  "cells": None, "parts": [], "extra": []}]
        header = [0, 0, 0, 0]
        own_palette = True
    frames, streams, palette = [], [], None
    for path_name, spec in zip(image_files(entry), specs):
        stored = spec["cells"]
        frame_cells = (lambda w, h: [tuple(c) for c in stored]) if stored is not None else cut_cells
        width, height, cells, raw, colors = _frame_tiles(source / path_name, frame_cells, bpp)
        if palette is None:
            palette = colors
        stream = compress_tiles(raw, spec["compression"], spec.get("padding"))
        streams.append(stream)
        frames.append({"width": width, "height": height, "offset": spec["offset"],
                       "compression": spec["compression"],
                       "cells": cells, "parts": spec["parts"], "extra": spec["extra"],
                       "tile_bytes": len(raw), "stream_bytes": len(stream)})
    components = {"tiles": b"".join(streams), "frames": encode_frames(frames, header)}
    if own_palette:
        components["palette"] = encode_palette(palette, bpp)
    return components


def resolve_compressions(record: dict, tiles: bytes) -> dict:
    """Fill in the codec of flag-0 frames from their stream headers."""
    for frame in record["frames"]:
        if frame["compression"] is None:
            compression = decompress_tiles(tiles[frame["tile_offset"]:])[1]
            if CELL_COUNT_FLAGS[compression]:
                raise ValueError(f"{compression} tiles in a frame with cell-count flags 0")
            frame["compression"] = compression
    return record


def _stream_paddings(tiles: bytes, frames: list[dict]) -> list[list[int] | None]:
    """Each frame's padding bytes if any is nonzero, else None."""
    ends = [f["tile_offset"] for f in frames[1:]] + [len(tiles)]
    paddings = []
    for frame, end in zip(frames, ends):
        stream = tiles[frame["tile_offset"]:end]
        raw, compression = decompress_tiles(stream)
        padding = stream[_body_length(stream, compression, raw):]
        paddings.append(list(padding) if any(padding) else None)
    return paddings


def _sprite_bpp(tiles: bytes, record: dict) -> int:
    """Bit depth from the first frame's tile bytes per cell pixel."""
    frame = record["frames"][0]
    pixels = sum(64 * w * h for _, _, w, h in frame["cells"])
    raw = decompress_tiles(tiles[frame["tile_offset"]:])[0]
    if len(raw) * 8 not in (4 * pixels, 8 * pixels):
        raise ValueError(f"{len(raw)} tile bytes fit neither 4 nor 8 bpp for {pixels} pixels")
    return len(raw) * 8 // pixels


def entry_settings(name: str, components: dict[str, bytes], stored_cells: bool, bpp: int) -> dict:
    """The bank.json entry for ROM components, without writing any PNG.
    A stored-cells sprite whose tiles are not at the bank's bit depth
    records its own bpp."""
    if "tiles" not in components:
        entry = {"name": name, "paletteOnly": True}
        if high := high_bits(components["palette"]):
            entry["highBits"] = high
        return entry
    record = resolve_compressions(decode_frames(components["frames"]), components["tiles"])
    paddings = _stream_paddings(components["tiles"], record["frames"])
    if stored_cells:
        keys = ("offset", "compression", "cells", "parts", "extra")
        frames = []
        for frame, padding in zip(record["frames"], paddings):
            frames.append({k: frame[k] for k in keys})
            if padding:
                frames[-1]["padding"] = padding
        entry = {"name": name, "palette": "palette" in components, "header": record["header"],
                 "frames": frames}
        sprite_bpp = _sprite_bpp(components["tiles"], record)
        if sprite_bpp != bpp:
            if "palette" in components:
                raise ValueError(f"{name}: {sprite_bpp}bpp tiles with a {bpp}bpp palette")
            entry["bpp"] = sprite_bpp
        return entry
    if any(paddings):
        raise ValueError(f"{name}: needs stored cells (nonzero GammaLz padding)")
    if len(record["frames"]) != 1 or any(record["header"]) or "palette" not in components:
        raise ValueError(f"{name}: needs stored cells (multi-frame, header data, or no palette)")
    frame = record["frames"][0]
    return {"name": name, "offset": frame["offset"], "compression": frame["compression"]}


def extract(source: Path, name: str, components: dict[str, bytes], bpp: int, stored_cells: bool) -> dict:
    """Write one image entry's PNGs and return its bank.json entry. Fails
    unless rebuilding from the PNGs reproduces every component byte for byte."""
    entry = entry_settings(name, components, stored_cells, bpp)
    bank_bpp, bpp = bpp, entry.get("bpp", bpp)
    if entry.get("paletteOnly"):
        count = 1 << bpp
        write_png(source / f"{name}.png", count, 1, list(range(count)),
                  decode_palette(clear_high_bits(components["palette"]), bpp), bpp)
    else:
        record = decode_frames(components["frames"])
        colors = (decode_palette(components["palette"], bpp) if "palette" in components
                  else gray_palette(bpp))
        for path_name, frame in zip(image_files(entry), record["frames"]):
            raw, _ = decompress_tiles(components["tiles"][frame["tile_offset"]:])
            w, h = frame["width"], frame["height"]
            cells = [tuple(c) for c in frame["cells"]] if stored_cells else cut_cells(w // 8, h // 8)
            write_png(source / path_name, w, h, unpack_pixels(raw, w, h, cells, bpp), colors, bpp)
    rebuilt = build(source, entry, bank_bpp)
    if rebuilt != components:
        diff = sorted(set(rebuilt) ^ set(components)) or [k for k in components if rebuilt[k] != components[k]]
        raise ValueError(f"{name}: rebuilt {', '.join(diff)} differs from the ROM")
    return entry


def _entry_json(image: dict) -> str:
    """One line per image, or per frame for stored-layout sprites."""
    if "frames" not in image:
        return f"    {json.dumps(image)}"
    head = json.dumps({k: v for k, v in image.items() if k != "frames"})[:-1]
    frames = ",\n".join(f"      {json.dumps(frame)}" for frame in image["frames"])
    return f'    {head}, "frames": [\n{frames}\n    ]}}'


def map_images(fn, *args, gamma_lz: bool):
    """map(fn, *args), across processes when GammaLz encoding is involved."""
    if not gamma_lz:
        return list(map(fn, *args))
    with ProcessPoolExecutor() as pool:
        return list(pool.map(fn, *args))


def _uses_gamma_lz(components: dict[str, bytes]) -> bool:
    if "frames" not in components:
        return False
    record = resolve_compressions(decode_frames(components["frames"]), components["tiles"])
    return any(f["compression"] == "gammalz" for f in record["frames"])


def extract_bank(source: Path, bpp: int, order: tuple[str, ...], entries: list[tuple[str, dict[str, bytes]]],
                 stored_cells: bool = False, index_only: bool = False,
                 palette_header: list[int] | None = None, palette_trailer: list[int] | None = None) -> None:
    """Write each image's PNGs and the bank's bank.json. With index_only,
    keep existing PNGs and regenerate only the index. The optional palette
    header and trailer are the bytes around every palette in the bank."""
    source.mkdir(parents=True, exist_ok=True)
    if index_only:
        images = []
        for name, components in entries:
            entry = entry_settings(name, components, stored_cells, bpp)
            missing = [f for f in image_files(entry) if not (source / f).is_file()]
            if missing:
                raise ValueError(f"missing {source / missing[0]}; extract the bank first")
            images.append(entry)
    else:
        names = [name for name, _ in entries]
        components = [c for _, c in entries]
        images = map_images(extract, repeat(source), names, components, repeat(bpp), repeat(stored_cells),
                            gamma_lz=any(map(_uses_gamma_lz, components)))
    lines = ",\n".join(_entry_json(image) for image in images)
    wrap = "".join(f'  "{key}": {json.dumps(value)},\n'
                   for key, value in (("paletteHeader", palette_header), ("paletteTrailer", palette_trailer))
                   if value is not None)
    (source / "bank.json").write_text(
        f'{{\n  "format": 2,\n  "bpp": {bpp},\n  "componentOrder": {json.dumps(list(order))},\n{wrap}'
        f'  "images": [\n{lines}\n  ]\n}}\n')
