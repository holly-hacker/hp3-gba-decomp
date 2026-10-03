"""Graphic blobs: a BG palette, tilemap and tile data in one byte string.

See docs/formats/graphic_blob.md. A blob is edited as one indexed PNG of the
whole image, <name>.png, where a pixel is bank * 16 + color number for 4 bpp
tiles and the color number for 8 bpp tiles, and the PNG palette is the blob's
256-color palette. Color 0 of each bank (of the palette for 8 bpp) is marked
transparent in the PNG; its color is still data. Tiles that no tilemap cell uses go in <name>.unused.png, a
sheet of 16 tiles per row. The tiles and tilemap are rebuilt from the image
the way the original tool made them: tiles in order of first use, a tile is
reused when a cell matches it or its flipped copy (tried unflipped,
horizontal, vertical, both), and a tile's palette bank is part of its identity.

A blob without a palette (flags0 bit 0 clear) draws with whatever palette is
already loaded; its PNG then carries a palette only for viewing, which the
packer ignores.

Supported flags: palette (flags0 bit 0, optional), tilemap and tiles (bits 3 and 4),
raw or GammaLz tiles (bits 5-6 = 0 or 3), 4 or 8 bpp (bit 7), byte or
halfword tilemap cells (flags1 bit 0).
"""
import struct
import sys
from pathlib import Path

from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "graphics"))
from decode_gamma_lz import decode_gamma_lz_stream  # noqa: E402
from encode_gamma_lz import encode_gamma_lz_stream  # noqa: E402

ROM_BASE = 0x08000000
PALETTE_BYTES = 512
CODEC_RAW, CODEC_GAMMA_LZ = 0, 3
FLAGS0_MASK = 0x01 | 0x08 | 0x10 | 0x60 | 0x80
FLIPS = ((0, 0), (1, 0), (0, 1), (1, 1))


class Blob:
    """flags0, flags1, palette (512 bytes, or None), tilemap size, cells (tile,
    h, v, bank per cell) and tiles (one tuple of 64 color numbers each)."""

    def __init__(self, flags0, flags1, palette, width, height, cells, tiles):
        self.flags0, self.flags1 = flags0, flags1
        self.palette, self.width, self.height = palette, width, height
        self.cells, self.tiles = cells, tiles

    @property
    def bpp8(self) -> bool:
        return bool(self.flags0 & 0x80)

    @property
    def byte_cells(self) -> bool:
        return bool(self.flags1 & 1)

    @property
    def codec(self) -> int:
        return (self.flags0 >> 5) & 3


def check_flags(flags0: int, flags1: int) -> None:
    if (flags0 & ~FLAGS0_MASK or flags1 & ~1 or (flags0 & 0x18) != 0x18
            or (flags0 >> 5) & 3 not in (CODEC_RAW, CODEC_GAMMA_LZ)):
        raise ValueError(f"unsupported blob flags {flags0:#04x} {flags1:#04x}")


def flip(tile, h: int, v: int):
    return tuple(tile[(7 - y if v else y) * 8 + (7 - x if h else x)]
                 for y in range(8) for x in range(8))


def _unpack_tiles(data: bytes, bpp8: bool):
    size = 64 if bpp8 else 32
    if len(data) % size:
        raise ValueError(f"tile data of {len(data)} bytes is not a whole number of tiles")
    tiles = []
    for i in range(0, len(data), size):
        chunk = data[i:i + size]
        tiles.append(tuple(chunk) if bpp8 else tuple((chunk[j // 2] >> (4 * (j & 1))) & 15 for j in range(64)))
    return tiles


def _pack_tiles(tiles, bpp8: bool) -> bytes:
    if bpp8:
        return b"".join(bytes(t) for t in tiles)
    return b"".join(bytes(t[j] | t[j + 1] << 4 for j in range(0, 64, 2)) for t in tiles)


def parse(rom: bytes, addr: int) -> tuple[Blob, int, bytes]:
    """Parse the blob at ROM address addr. Returns it, the address just past
    it, and the blob's raw bytes."""
    start = pos = addr - ROM_BASE
    flags0, flags1 = rom[pos], rom[pos + 1]
    check_flags(flags0, flags1)
    pos += 2
    palette = None
    if flags0 & 1:
        palette = rom[pos:pos + PALETTE_BYTES]
        pos += PALETTE_BYTES
    width, height = struct.unpack_from("<HH", rom, pos)
    pos += 4
    count = width * height
    if flags1 & 1:
        cells = [(c, 0, 0, 0) for c in rom[pos:pos + count]]
        pos += count + (count & 1)
    else:
        raw = struct.unpack_from(f"<{count}H", rom, pos)
        cells = [(c & 0x3FF, (c >> 10) & 1, (c >> 11) & 1, c >> 12) for c in raw]
        pos += 2 * count
    (length,) = struct.unpack_from("<H", rom, pos)
    pos += 2
    if (flags0 >> 5) & 3 == CODEC_RAW:
        data = rom[pos:pos + length]
    else:
        data, end = decode_gamma_lz_stream(rom, ROM_BASE + pos)
        if end - ROM_BASE - pos != length:
            raise ValueError(f"{addr:#x}: stream is {end - ROM_BASE - pos} bytes, its length says {length}")
    pos += length
    blob = Blob(flags0, flags1, palette, width, height, cells, _unpack_tiles(data, bool(flags0 & 0x80)))
    return blob, ROM_BASE + pos, rom[start:pos]


def build(blob: Blob) -> bytes:
    """The blob's ROM bytes."""
    out = bytearray((blob.flags0, blob.flags1))
    if blob.palette is not None:
        out += blob.palette
    out += struct.pack("<HH", blob.width, blob.height)
    if blob.byte_cells:
        out += bytes(c[0] for c in blob.cells)
        out += b"\0" * (len(blob.cells) & 1)
    else:
        out += struct.pack(f"<{len(blob.cells)}H",
                           *(t | h << 10 | v << 11 | bank << 12 for t, h, v, bank in blob.cells))
    data = _pack_tiles(blob.tiles, blob.bpp8)
    stream = data if blob.codec == CODEC_RAW else encode_gamma_lz_stream(data)
    out += struct.pack("<H", len(stream)) + stream
    return bytes(out)


def used_tiles(blob: Blob) -> int:
    return max((c[0] for c in blob.cells), default=-1) + 1


def decode_palette(data: bytes):
    """(r, g, b) per entry, and the entries whose unused bit 15 is set."""
    values = struct.unpack("<256H", data)
    colors = [tuple(((v >> s) & 31) << 3 | ((v >> s) & 31) >> 2 for s in (0, 5, 10)) for v in values]
    return colors, [i for i, v in enumerate(values) if v & 0x8000]


def encode_palette(colors, high_bits) -> bytes:
    values = [(r >> 3) | (g >> 3) << 5 | (b >> 3) << 10 for r, g, b in colors]
    for i in high_bits:
        values[i] |= 0x8000
    return struct.pack("<256H", *values)


def image_pixels(blob: Blob) -> list[int]:
    """The blob's image as palette indices, row by row."""
    w = blob.width * 8
    pixels = [0] * (w * blob.height * 8)
    for n, (t, h, v, bank) in enumerate(blob.cells):
        tile = flip(blob.tiles[t], h, v)
        add = 0 if blob.bpp8 else bank * 16
        x0, y0 = (n % blob.width) * 8, (n // blob.width) * 8
        for y in range(8):
            row = (y0 + y) * w + x0
            pixels[row:row + 8] = [p + add for p in tile[y * 8:y * 8 + 8]]
    return pixels


def layout_of(blob: Blob) -> list[int]:
    """Each cell's tile number and flips (tilemap cell without the palette bank)."""
    return [t | h << 10 | v << 11 for t, h, v, _ in blob.cells]


def blob_from_image(flags0: int, flags1: int, palette: bytes, width: int, height: int,
                    pixels: list[int], unused: list[tuple], layout=None) -> Blob:
    """Rebuild the tiles and tilemap from an image, as the original tool did.
    With a layout (see layout_of), every cell takes the given tile and flips
    instead; tiles must be numbered in order of first use and every cell of a
    tile must show the same pixels."""
    check_flags(flags0, flags1)
    bpp8, byte_cells = bool(flags0 & 0x80), bool(flags1 & 1)
    w = width * 8
    index, tiles, cells = {}, [], []
    for n in range(width * height):
        x0, y0 = (n % width) * 8, (n // width) * 8
        image = tuple(pixels[(y0 + y) * w + x0 + x] for y in range(8) for x in range(8))
        bank = 0
        if not bpp8:
            banks = {p >> 4 for p in image}
            if len(banks) != 1:
                raise ValueError(f"cell ({n % width}, {n // width}) mixes palette banks {sorted(banks)}")
            bank = banks.pop()
        if layout is not None:
            tile, h, v = layout[n] & 0x3FF, (layout[n] >> 10) & 1, (layout[n] >> 11) & 1
            image = flip(image, h, v)
            mask = 0xFF if bpp8 else 0x0F
            image = tuple(p & mask for p in image)
            if tile == len(tiles):
                tiles.append(image)
            elif tile > len(tiles) or tiles[tile] != image:
                raise ValueError(f"cell ({n % width}, {n // width}) does not match tile {tile} of its layout")
            cells.append((tile, h, v, bank))
            continue
        for h, v in ((0, 0),) if byte_cells else FLIPS:
            found = index.get(flip(image, h, v))
            if found is not None:
                cells.append((found, h, v, bank))
                break
        else:
            index[image] = len(tiles)
            tiles.append(image)
            cells.append((len(tiles) - 1, 0, 0, bank))
    if byte_cells and len(tiles) > 256:
        raise ValueError(f"{len(tiles)} tiles do not fit byte tilemap cells")
    mask = 0xFF if bpp8 else 0x0F
    if layout is None:
        tiles = [tuple(p & mask for p in t) for t in tiles]
    tiles = tiles + unused
    return Blob(flags0, flags1, palette, width, height, cells, tiles)


def read_png(path: Path):
    with Image.open(path) as image:
        if image.mode != "P":
            raise ValueError(f"{path}: expected an indexed-color PNG, got mode {image.mode}")
        flat = image.getpalette() or []
        colors = [tuple(flat[i:i + 3]) for i in range(0, len(flat), 3)]
        colors += [(0, 0, 0)] * (256 - len(colors))
        return image.size, list(image.get_flattened_data()), colors


def transparent_indices(bpp8: bool) -> list[int]:
    """Color 0 of the palette (of each bank for 4 bpp) is transparent on the
    GBA, so the PNG marks it, whatever color the art tool left in it."""
    return [0] if bpp8 else list(range(0, 256, 16))


def write_png(path: Path, size, pixels, colors, transparent=()) -> None:
    image = Image.new("P", size)
    image.putpalette([c for rgb in colors for c in rgb])
    image.putdata(pixels)
    if transparent:
        image.info["transparency"] = bytes(0 if i in transparent else 255 for i in range(256))
    image.save(path)


def unused_sheet(tiles: list[tuple]) -> tuple[tuple[int, int], list[int]]:
    rows = (len(tiles) + 15) // 16
    pixels = [0] * (128 * rows * 8)
    for n, tile in enumerate(tiles):
        x0, y0 = (n % 16) * 8, (n // 16) * 8
        for y in range(8):
            pixels[(y0 + y) * 128 + x0:(y0 + y) * 128 + x0 + 8] = tile[y * 8:y * 8 + 8]
    return (128, rows * 8), pixels


def unused_from_sheet(pixels: list[int], count: int) -> list[tuple]:
    return [tuple(pixels[((n // 16) * 8 + y) * 128 + (n % 16) * 8 + x] for y in range(8) for x in range(8))
            for n in range(count)]
