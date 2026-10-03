"""Tile streams: a 16-bit width and height, then 4 bpp tile data as a GammaLz
stream without its outer header (see docs/formats/graphic_blob.md).

A stream is edited as <name>.png, a sheet of its tiles, 8 per row, in
grayscale (the real palette is not known). A pixel is the 4-bit color number
and color 0 is marked transparent. The width and height, which are not
derived from the tile data, and the tile count are kept in bank.json.
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import blobs
from blobs import ROM_BASE, decode_gamma_lz_stream, encode_gamma_lz_stream

TILES_PER_ROW = 8
GRAY = [(i * 17, i * 17, i * 17) for i in range(16)] + [(0, 0, 0)] * 240


def parse(rom: bytes, addr: int):
    """The stream at ROM address addr: (width, height, tiles), the address
    just past it, and its raw bytes."""
    pos = addr - ROM_BASE
    width, height = struct.unpack_from("<HH", rom, pos)
    data, end = decode_gamma_lz_stream(rom, addr + 4)
    return (width, height, blobs._unpack_tiles(data, False)), end, rom[pos:end - ROM_BASE]


def build(width: int, height: int, tiles) -> bytes:
    return struct.pack("<HH", width, height) + encode_gamma_lz_stream(blobs._pack_tiles(tiles, False))


def sheet(tiles):
    """Size and pixels of the tile sheet."""
    rows = (len(tiles) + TILES_PER_ROW - 1) // TILES_PER_ROW
    w = TILES_PER_ROW * 8
    pixels = [0] * (w * rows * 8)
    for n, tile in enumerate(tiles):
        x0, y0 = (n % TILES_PER_ROW) * 8, (n // TILES_PER_ROW) * 8
        for y in range(8):
            pixels[(y0 + y) * w + x0:(y0 + y) * w + x0 + 8] = tile[y * 8:y * 8 + 8]
    return (w, rows * 8), pixels


def tiles_from_sheet(pixels, count: int):
    w = TILES_PER_ROW * 8
    return [tuple(pixels[((n // TILES_PER_ROW) * 8 + y) * w + (n % TILES_PER_ROW) * 8 + x]
                  for y in range(8) for x in range(8)) for n in range(count)]
