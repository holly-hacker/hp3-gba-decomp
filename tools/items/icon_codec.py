"""Decode a real item's icon (pIcon1/pIcon2/pIcon3) into RGBA pixels.
See docs/formats/graphics.md's "Item icons" section for how this format
was identified and verified (rendered and visually confirmed against
two items -- a belt and a potion bottle -- via Ghidra call-graph tracing
from ItemEntry.pIcon1/2/3 into SpawnObject/LoadObjTileSheet).

- pIcon1: a 32-byte palette -- 2-byte header (unidentified, ignored) +
  15 BGR555 colors. Index 0 is always transparent (GBA OBJ palette
  convention, not stored in the resource itself).
- pIcon3: a frame/layout header. Fixed 12-byte part: +0x06 is a u16
  frame count. Followed by one u16 offset per frame (relative to the
  header's own +0x0C), each pointing at a small record with pixel width
  (+0x02, u8), height (+0x03, u8), and a u16 source offset (+0x04) into
  pIcon2. Every real item has exactly 1 frame -- see
  tools/items/extract_item_icons.py; this module errors out if that
  ever isn't true rather than silently picking frame 0.
- pIcon2: the tile pixel data the frame record's source offset points
  into, header-prefixed like any generic resource (byte0's nibble is
  the type, byte1..3 LE the decompressed size): type 3 (BIOS RLUnComp,
  11 of 79 real items) or type 7, which is FUN_0801de5c's *own* nibble
  for the type-4 proprietary codec (distinct from sub_0801DD90's nibble
  4 for the same codec -- two different dispatchers, two different
  nibble->codec mappings, same underlying codec). No other nibble
  appears among the 79 real items.
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent.parent / "graphics"))
from decode_bios import decode_bios
from decode_type4 import CODEC_ADDR, decode_type4

ROM_BASE = 0x08000000


def bgr555_to_rgba(value: int) -> tuple[int, int, int, int]:
    r = (value & 0x1F) * 255 // 31
    g = ((value >> 5) & 0x1F) * 255 // 31
    b = ((value >> 10) & 0x1F) * 255 // 31
    return (r, g, b, 255)


def decode_palette(rom: bytes, addr: int) -> list[tuple[int, int, int, int]]:
    off = addr - ROM_BASE
    colors = [(0, 0, 0, 0)]  # index 0: transparent, not stored in the resource
    for i in range(15):
        value = struct.unpack_from("<H", rom, off + 2 + i * 2)[0]
        colors.append(bgr555_to_rgba(value))
    return colors


def read_frame(rom: bytes, pIcon3: int) -> tuple[int, int, int]:
    """Returns (width, height, source_offset) for the single frame every
    real item has -- see module docstring."""
    off = pIcon3 - ROM_BASE
    frame_count = struct.unpack_from("<H", rom, off + 0x06)[0]
    if frame_count != 1:
        raise ValueError(f"pIcon3 {pIcon3:#010x}: expected exactly 1 frame, got {frame_count}")
    table_base = off + 0x0C
    frame_off = struct.unpack_from("<H", rom, table_base)[0]
    record = table_base + frame_off
    width = rom[record + 0x02]
    height = rom[record + 0x03]
    source_offset = struct.unpack_from("<H", rom, record + 0x04)[0]
    return width, height, source_offset


def decode_tiles(rom: bytes, ver: str, pIcon2: int, source_offset: int, decoded_size: int) -> bytes:
    header_addr = pIcon2 + source_offset
    header = struct.unpack_from("<I", rom, header_addr - ROM_BASE)[0]
    type_nibble = (header & 0xFF) >> 4
    size = header >> 8
    if size != decoded_size:
        raise ValueError(f"{header_addr:#010x}: header declares {size} decoded bytes, "
                          f"frame record expects {decoded_size} (width*height/2)")
    if type_nibble == 3:
        # sub_0801DE5C's case-3 branch passes header_addr+4 (past this
        # generic dispatcher header) straight into svc 0x15
        # (RLUnCompVram), which reads its OWN mandatory 4-byte
        # type+size header from wherever it's given -- so a second,
        # identical header sits at header_addr+4, and the real RLE
        # token stream only starts at header_addr+8. Skipping only the
        # outer header (the correct convention for type 7 below, which
        # has no such duplicate) is a dead end here: the duplicate
        # header's own bytes get fed into the decoder as real tokens,
        # corrupting the result -- see docs/formats/graphics.md's "Item
        # icons" section.
        inner_header = struct.unpack_from("<I", rom, header_addr - ROM_BASE + 4)[0]
        if inner_header != header:
            raise ValueError(f"{header_addr:#010x}: expected a duplicated BIOS header at +4 "
                              f"for type 3, got {inner_header:#010x} != {header:#010x}")
        return decode_bios(rom, header_addr + 4)[:decoded_size]
    if type_nibble == 7:
        codec_addr = CODEC_ADDR.get(ver)
        if codec_addr is None:
            raise ValueError(f"type-4 codec address not confirmed for ver={ver!r}")
        return decode_type4(rom, header_addr + 4, codec_addr)[:decoded_size]
    raise ValueError(f"{header_addr:#010x}: unhandled icon tile-data type nibble {type_nibble:#x}")


def tiles_to_rgba(tile_data: bytes, width: int, height: int,
                   palette: list[tuple[int, int, int, int]]) -> list[tuple[int, int, int, int]]:
    """4bpp GBA tile data (8x8 tiles, row-major within each tile, tiles
    laid out row-major left-to-right/top-to-bottom) -> a flat width*height
    RGBA pixel list."""
    pixels = [(0, 0, 0, 0)] * (width * height)
    idx = 0
    for tile_y in range(height // 8):
        for tile_x in range(width // 8):
            for y in range(8):
                for x_pair in range(0, 8, 2):
                    byte = tile_data[idx]
                    idx += 1
                    px = tile_x * 8 + x_pair
                    py = tile_y * 8 + y
                    pixels[py * width + px] = palette[byte & 0xF]
                    pixels[py * width + px + 1] = palette[(byte >> 4) & 0xF]
    return pixels


def decode_icon(rom: bytes, ver: str, pIcon1: int, pIcon2: int, pIcon3: int
                 ) -> tuple[int, int, list[tuple[int, int, int, int]]]:
    """Returns (width, height, rgba_pixels)."""
    palette = decode_palette(rom, pIcon1)
    width, height, source_offset = read_frame(rom, pIcon3)
    tile_data = decode_tiles(rom, ver, pIcon2, source_offset, width * height // 2)
    pixels = tiles_to_rgba(tile_data, width, height, palette)
    return width, height, pixels
