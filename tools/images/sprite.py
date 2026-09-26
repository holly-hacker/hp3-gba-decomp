"""Convert between indexed PNG sprites and their ROM tile, frame, and palette data.

See docs/formats/graphics.md ("Sprite images"). A bank.json image entry is
one of:

- a derived sprite, {name, offset, compression}: one frame, <name>.png,
  OAM cells cut from the image size (cut_cells);
- a stored-layout sprite, {name, palette, header, frames}: <name>.<i>.png
  per frame, each frame listing its offset, compression, OAM cells (in
  tiles), attached parts, and extra halfwords;
- a palette, {name, paletteOnly}: <name>.png, a swatch whose PNG palette
  is the data.

Components: palette (2**bpp BGR555 entries from the PNG palette), tiles
(each frame's cell tiles, compressed, one stream per frame), and frames
(an ObjectFrameData record).
"""
import json
import struct
import sys
from pathlib import Path

from PIL import Image

sys.path.insert(0, str(Path(__file__).parent.parent / "graphics"))
from decode_bios import rl_uncomp  # noqa: E402
from decode_lz_rle import decode_lz_rle  # noqa: E402
from encode_bios_rle import encode_bios_rle  # noqa: E402
from encode_lz_rle import encode_lz_rle  # noqa: E402

ROM_BASE = 0x08000000
COMPONENT_KINDS = ("palette", "tiles", "frames")

# DecompressResourceVram type per codec, and the value of the frame
# descriptor's bCellCount bits 5-7 that accompanies it in every ROM sprite.
COMPRESSION_TYPES = {"rle": 3, "lzrle": 7}
CELL_COUNT_FLAGS = {"rle": 0x20, "lzrle": 0x40}

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


def compress_tiles(raw: bytes, compression: str) -> bytes:
    """Resource header, compressed stream, then at least five zero bytes
    ending on a word boundary (LzRle's end token counts as the first)."""
    if compression not in COMPRESSION_TYPES:
        raise ValueError(f"unknown compression {compression!r}")
    size = len(raw)
    header = struct.pack("<I", COMPRESSION_TYPES[compression] << 4 | size << 8)
    if compression == "lzrle":
        body = header + encode_lz_rle(raw)
        return body.ljust(_align4(len(body) + 4), b"\0")
    # DecompressResourceVram passes header+4 to the BIOS, which reads its
    # own copy of the header there.
    body = header + encode_bios_rle(raw)
    return body.ljust(_align4(len(body) + 5), b"\0")


def decompress_tiles(data: bytes) -> tuple[bytes, str]:
    header = struct.unpack_from("<I", data)[0]
    size = header >> 8
    by_type = {t: name for name, t in COMPRESSION_TYPES.items()}
    compression = by_type.get(header >> 4 & 0xF) if header & 0x8F == 0 else None
    if compression == "lzrle":
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
    except (ValueError, IndexError, struct.error):
        return None
    encoded = compress_tiles(raw, compression)
    return len(encoded) if data[:len(encoded)] == encoded else None


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
    return bytes(out)


def _sign9(value: int) -> int:
    value &= 0x1FF
    return value - 0x200 if value & 0x100 else value


def decode_frames(data: bytes) -> dict:
    """Parse an ObjectFrameData record; returns its fields and byte length."""
    width, height = data[0], data[1]
    header = list(struct.unpack_from("<4b", data, 2))
    frame_count, tile_bytes, extra_count, part_count = struct.unpack_from("<HHBB", data, 6)
    offsets = struct.unpack_from(f"<{frame_count}H", data, FRAME_HEADER_SIZE)
    by_flag = {flag: name for name, flag in CELL_COUNT_FLAGS.items()}
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
    if entry.get("paletteOnly"):
        _, _, _, colors = read_png(source / f"{entry['name']}.png", bpp)
        return {"palette": encode_palette(colors, bpp)}
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
        stream = compress_tiles(raw, spec["compression"])
        streams.append(stream)
        frames.append({"width": width, "height": height, "offset": spec["offset"],
                       "compression": spec["compression"],
                       "cells": cells, "parts": spec["parts"], "extra": spec["extra"],
                       "tile_bytes": len(raw), "stream_bytes": len(stream)})
    components = {"tiles": b"".join(streams), "frames": encode_frames(frames, header)}
    if own_palette:
        components["palette"] = encode_palette(palette, bpp)
    return components


def entry_settings(name: str, components: dict[str, bytes], stored_cells: bool) -> dict:
    """The bank.json entry for ROM components, without writing any PNG."""
    if "tiles" not in components:
        return {"name": name, "paletteOnly": True}
    record = decode_frames(components["frames"])
    if stored_cells:
        keys = ("offset", "compression", "cells", "parts", "extra")
        return {"name": name, "palette": "palette" in components, "header": record["header"],
                "frames": [{k: f[k] for k in keys} for f in record["frames"]]}
    if len(record["frames"]) != 1 or any(record["header"]) or "palette" not in components:
        raise ValueError(f"{name}: needs stored cells (multi-frame, header data, or no palette)")
    frame = record["frames"][0]
    return {"name": name, "offset": frame["offset"], "compression": frame["compression"]}


def extract(source: Path, name: str, components: dict[str, bytes], bpp: int, stored_cells: bool) -> dict:
    """Write one image entry's PNGs and return its bank.json entry. Fails
    unless rebuilding from the PNGs reproduces every component byte for byte."""
    entry = entry_settings(name, components, stored_cells)
    if entry.get("paletteOnly"):
        count = 1 << bpp
        write_png(source / f"{name}.png", count, 1, list(range(count)),
                  decode_palette(components["palette"], bpp), bpp)
    else:
        record = decode_frames(components["frames"])
        colors = (decode_palette(components["palette"], bpp) if "palette" in components
                  else gray_palette(bpp))
        for path_name, frame in zip(image_files(entry), record["frames"]):
            raw, _ = decompress_tiles(components["tiles"][frame["tile_offset"]:])
            w, h = frame["width"], frame["height"]
            cells = [tuple(c) for c in frame["cells"]] if stored_cells else cut_cells(w // 8, h // 8)
            write_png(source / path_name, w, h, unpack_pixels(raw, w, h, cells, bpp), colors, bpp)
    rebuilt = build(source, entry, bpp)
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


def extract_bank(source: Path, bpp: int, order: tuple[str, ...], entries: list[tuple[str, dict[str, bytes]]],
                 stored_cells: bool = False, index_only: bool = False) -> None:
    """Write each image's PNGs and the bank's bank.json. With index_only,
    keep existing PNGs and regenerate only the index."""
    source.mkdir(parents=True, exist_ok=True)
    images = []
    for name, components in entries:
        if index_only:
            entry = entry_settings(name, components, stored_cells)
            missing = [f for f in image_files(entry) if not (source / f).is_file()]
            if missing:
                raise ValueError(f"missing {source / missing[0]}; extract the bank first")
        else:
            entry = extract(source, name, components, bpp, stored_cells)
        images.append(entry)
    lines = ",\n".join(_entry_json(image) for image in images)
    (source / "bank.json").write_text(
        f'{{\n  "format": 2,\n  "bpp": {bpp},\n  "componentOrder": {json.dumps(list(order))},\n'
        f'  "images": [\n{lines}\n  ]\n}}\n')
