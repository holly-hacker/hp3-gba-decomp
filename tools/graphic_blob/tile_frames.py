"""Tile frames: a 16-bit kind and byte size, then that many bytes of 4 bpp tile
data, raw or (kind bits 5-6 = 3) a GammaLz stream without its outer header; kind
bit 7 marks 8 bpp tiles (see docs/formats/special_scene_frames.md).

A frame is edited as <name>.png, a sheet of its tiles, 8 per row, in
grayscale (the real palette is not known). A pixel is the 4-bit (or, for an
8 bpp frame, 8-bit) color number and color 0 is marked transparent. The kind,
which is not derived from the tile data, and the tile count are kept in
the run's settings.
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import blobs
from blobs import ROM_BASE, decode_gamma_lz_stream, encode_gamma_lz_stream
from tile_streams import GRAY, TILES_PER_ROW, sheet, tiles_from_sheet  # noqa: F401

GRAY8 = [(i, i, i) for i in range(256)]


CODEC_RAW, CODEC_GAMMA_LZ = 0, 3
KIND_8BPP = 0x80


def parse(rom: bytes, addr: int):
    """The frame at ROM address addr: (kind, tiles), the address just past it,
    and its raw bytes."""
    pos = addr - ROM_BASE
    kind, size = struct.unpack_from("<HH", rom, pos)
    codec = (kind >> 5) & 3
    if codec == CODEC_RAW:
        data = rom[pos + 4:pos + 4 + size]
        end = ROM_BASE + pos + 4 + size
    elif codec == CODEC_GAMMA_LZ:
        data, end = decode_gamma_lz_stream(rom, addr + 4)
        if end - addr - 4 != size:
            raise ValueError(f"{addr:#x}: stream is {end - addr - 4} bytes, its size says {size}")
    else:
        raise ValueError(f"{addr:#x}: unsupported frame kind {kind:#x}")
    return (kind, blobs._unpack_tiles(data, bool(kind & KIND_8BPP))), end, rom[pos:end - ROM_BASE]


def build(kind: int, tiles) -> bytes:
    data = blobs._pack_tiles(tiles, bool(kind & KIND_8BPP))
    if (kind >> 5) & 3 == CODEC_GAMMA_LZ:
        data = encode_gamma_lz_stream(data)
    return struct.pack("<HH", kind, len(data)) + data
