#!/usr/bin/env python3
"""Decode one BG tile using its tileset's canonical Huffman table.

The packed tile offset counts bits from the start of ROM. Each 32-bit
little-endian word supplies bits least-significant bit first. See
docs/formats/graphics.md, "On-demand per-tile BG streaming".
"""
import struct
import sys

ROM_BASE = 0x08000000


def decode_bgtile(rom: bytes, bit_offset: int, context_bytes: bytes,
                  output_size: int = 0x20) -> bytes:
    """Decode output_size bytes from a tile stream using count/base/symbol."""
    if len(context_bytes) != 292:
        raise ValueError("BG tile context must be 292 bytes")
    if output_size & 1:
        raise ValueError("BG tile output size must be even")
    counts = context_bytes[:18]
    bases = context_bytes[18:36]
    symbols = context_bytes[36:]
    word_pos = (bit_offset >> 5) * 4
    word = struct.unpack_from("<I", rom, word_pos)[0] >> (bit_offset & 31)
    bits_left = 32 - (bit_offset & 31)
    output = bytearray()
    while len(output) < output_size:
        code = 0
        for length in range(18):
            if bits_left == 0:
                word_pos += 4
                word = struct.unpack_from("<I", rom, word_pos)[0]
                bits_left = 32
            code = (code << 1) | (word & 1)
            word >>= 1
            bits_left -= 1
            if code < counts[length]:
                output.append(symbols[bases[length] + code])
                break
            code -= counts[length]
        else:
            raise ValueError("invalid BG tile Huffman code")
    return bytes(output)


def build_tile_offsets(blob_base: int, offset_table_bytes: bytes, num_entries: int) -> list[int]:
    """Expand the gap-coded offset table to one ROM bit offset per tile."""
    mask = 0xFFFFFFFF
    val = (blob_base + (-0x7FFFEDC)) * 8 & mask
    pos = 2  # skip 2-byte internal header
    offsets = []
    for _ in range(num_entries):
        offsets.append(val)
        b = offset_table_bytes[pos]
        if b == 0xFF:
            gap = (offset_table_bytes[pos + 1] << 8) + offset_table_bytes[pos + 2]
            pos += 3
        else:
            gap = 0x20 + b
            pos += 1
        val = (val + gap) & mask
    return offsets


def main() -> None:
    sys.exit("no standalone CLI -- see dump_bg_tiles.py")


if __name__ == "__main__":
    main()
