"""Tile frames: a 16-bit kind and byte size, then that many bytes of raw 4 bpp
tile data (see docs/formats/special_scene_frames.md).

A frame is edited as <name>.png, a sheet of its tiles, 8 per row, in
grayscale (the real palette bank is not known). A pixel is the 4-bit color
number and color 0 is marked transparent. The kind, which is not derived from
the tile data, and the tile count are kept in bank.json.
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import blobs
from blobs import ROM_BASE
from tile_streams import GRAY, TILES_PER_ROW, sheet, tiles_from_sheet  # noqa: F401


def parse(rom: bytes, addr: int):
    """The frame at ROM address addr: (kind, tiles), the address just past it,
    and its raw bytes."""
    pos = addr - ROM_BASE
    kind, size = struct.unpack_from("<HH", rom, pos)
    end = pos + 4 + size
    return (kind, blobs._unpack_tiles(rom[pos + 4:end], False)), ROM_BASE + end, rom[pos:end]


def build(kind: int, tiles) -> bytes:
    data = blobs._pack_tiles(tiles, False)
    return struct.pack("<HH", kind, len(data)) + data
