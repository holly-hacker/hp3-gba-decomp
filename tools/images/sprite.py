"""Convert between indexed PNG sprites and their ROM tile, frame, and palette data.

A sprite is one indexed-color PNG plus two settings: `offset`, the pixel
position of the image's top-left corner relative to the object's anchor, and
`compression`, the tile-data codec. Everything else follows from the image;
see docs/formats/graphics.md ("Sprite images").

- palette: 2**bpp little-endian BGR555 entries, taken from the PNG palette.
- tiles: the image cut into OAM cells (see cut_cells), each cell's 8x8 tiles
  row-major, compressed and followed by zero padding.
- frames: a one-frame ObjectFrameData record describing those cells.
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
MAX_TILES_PER_SIDE = 15


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


def _cell_pixels(width: int, height: int):
    """Yield (x, y) for every pixel in tile-data order."""
    for cx, cy, cw, ch in cut_cells(width // 8, height // 8):
        for ty in range(cy, cy + ch):
            for tx in range(cx, cx + cw):
                for y in range(ty * 8, ty * 8 + 8):
                    for x in range(tx * 8, tx * 8 + 8):
                        yield x, y


def pack_pixels(pixels: list[int], width: int, height: int, bpp: int) -> bytes:
    ordered = [pixels[y * width + x] for x, y in _cell_pixels(width, height)]
    if bpp == 8:
        return bytes(ordered)
    return bytes(lo | hi << 4 for lo, hi in zip(ordered[0::2], ordered[1::2]))


def unpack_pixels(data: bytes, width: int, height: int, bpp: int) -> list[int]:
    if bpp == 8:
        values = list(data)
    else:
        values = [v for byte in data for v in (byte & 0xF, byte >> 4)]
    pixels = [0] * (width * height)
    for value, (x, y) in zip(values, _cell_pixels(width, height)):
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


def encode_frames(width: int, height: int, offset: tuple[int, int], compression: str, bpp: int) -> bytes:
    cells = cut_cells(width // 8, height // 8)
    tile_bytes = width * height * bpp // 8
    ox, oy = offset
    if tile_bytes > 0xFFFF or width > 0xFF or height > 0xFF:
        raise ValueError(f"{width}x{height} sprite exceeds the frame record's fields")
    out = bytearray(struct.pack("<BB4xHHBBH", width, height, 1, tile_bytes, 0, 0, 2))
    out += struct.pack("<BBBBHhh", len(cells) | CELL_COUNT_FLAGS[compression], 0, width, height, 0, ox, oy)
    tile = 0
    for cx, cy, cw, ch in cells:
        x, y = ox + cx * 8, oy + cy * 8
        if not (-256 <= x < 256 and -256 <= y < 256):
            raise ValueError(f"cell position ({x}, {y}) exceeds the 9-bit OAM range")
        if tile >= 1 << 10:
            raise ValueError(f"cell tile offset {tile} exceeds 10 bits")
        shape, size = OAM_SHAPES[(cw, ch)]
        word = (x & 0x1FF) | (y & 0x1FF) << 9 | size << 18 | shape << 20 | tile << 22
        out += struct.pack("<I", word)
        tile += cw * ch
    return bytes(out)


def decode_frames(data: bytes) -> tuple[int, int, tuple[int, int], str]:
    width, height = data[0], data[1]
    flags = data[0xE] & 0xE0
    offset = struct.unpack_from("<hh", data, 0x14)
    by_flag = {flag: name for name, flag in CELL_COUNT_FLAGS.items()}
    if flags not in by_flag:
        raise ValueError(f"unknown cell-count flags {flags:#04x}")
    return width, height, offset, by_flag[flags]


def component_length(kind: str, data: bytes, bpp: int) -> int:
    """Byte length of the component that starts `data`, read from the
    component itself."""
    if kind == "palette":
        return 2 << bpp
    if kind == "tiles":
        raw, compression = decompress_tiles(data)
        return len(compress_tiles(raw, compression))
    if kind == "frames":
        frame_count, header_extra, part_count = struct.unpack_from("<H2xBB", data, 6)
        if frame_count != 1:
            raise ValueError(f"frame record has {frame_count} frames; only 1 is supported")
        cell_count = data[0xE] & 0x1F
        return 0xE + 0xA + header_extra * 2 + part_count * 6 + cell_count * 4
    raise ValueError(f"unknown component kind {kind!r}")


def read_png(path: Path, bpp: int) -> tuple[int, int, list[int], list[tuple[int, int, int]]]:
    with Image.open(path) as image:
        if image.mode != "P":
            raise ValueError(f"expected an indexed-color PNG, got mode {image.mode}")
        width, height = image.size
        if width % 8 or height % 8:
            raise ValueError(f"{width}x{height} is not a multiple of 8 pixels")
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


def build(path: Path, offset: tuple[int, int], compression: str, bpp: int) -> dict[str, bytes]:
    width, height, pixels, colors = read_png(path, bpp)
    return {
        "palette": encode_palette(colors, bpp),
        "tiles": compress_tiles(pack_pixels(pixels, width, height, bpp), compression),
        "frames": encode_frames(width, height, offset, compression, bpp),
    }


def extract(components: dict[str, bytes], path: Path, bpp: int) -> dict:
    """Write one sprite PNG and return its settings. Fails unless rebuilding
    from the PNG reproduces every component byte for byte."""
    raw, compression = decompress_tiles(components["tiles"])
    width, height, offset, frame_compression = decode_frames(components["frames"])
    if frame_compression != compression:
        raise ValueError(f"{path.name}: frame flags imply {frame_compression}, tiles use {compression}")
    if len(raw) != width * height * bpp // 8:
        raise ValueError(f"{path.name}: {len(raw)} tile bytes do not fill {width}x{height} at {bpp}bpp")
    colors = decode_palette(components["palette"], bpp)
    write_png(path, width, height, unpack_pixels(raw, width, height, bpp), colors, bpp)
    rebuilt = build(path, offset, compression, bpp)
    for kind in COMPONENT_KINDS:
        if rebuilt[kind] != components[kind]:
            raise ValueError(f"{path.name}: rebuilt {kind} differs from the ROM")
    return {"offset": list(offset), "compression": compression}


def extract_bank(source: Path, bpp: int, order: tuple[str, ...],
                 sprites: list[tuple[str, dict[str, bytes]]], index_only: bool = False) -> None:
    """Write each sprite's PNG and the bank's bank.json. With index_only,
    keep existing PNGs and regenerate only the index."""
    source.mkdir(parents=True, exist_ok=True)
    images = []
    for name, components in sprites:
        path = source / f"{name}.png"
        if index_only:
            if not path.is_file():
                raise ValueError(f"missing {path}; extract the bank first")
            _, _, offset, compression = decode_frames(components["frames"])
            settings = {"offset": list(offset), "compression": compression}
        else:
            settings = extract(components, path, bpp)
        images.append({"name": name, **settings})
    lines = ",\n".join(f"    {json.dumps(image)}" for image in images)
    (source / "bank.json").write_text(
        f'{{\n  "format": 2,\n  "bpp": {bpp},\n  "componentOrder": {json.dumps(list(order))},\n'
        f'  "images": [\n{lines}\n  ]\n}}\n')
