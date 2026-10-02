#!/usr/bin/env python3
"""Decode and encode a room BG tileset resource (dwBgTilesetA/B in the room table).

Layout, byte for byte (see docs/formats/graphics.md, "On-demand per-tile BG
streaming"):

  u16 size          bytes from the end of this head to the Huffman table, minus 8
  u16 tile_count
  resource          the per-tile offset table, a dispatcher resource that is
                    stored (type 0) or GammaLz (type 6), whichever is smaller:
                    u16 tile_count, one gap per tile (the tile's length in bits:
                    one byte 0x20 + n for 0x20..0x11E, else 0xFF and a
                    big-endian u16), then 2 bytes of tool residue
  zero padding      to a multiple of 4 bytes
  4 bytes           tool residue
  u32 0x20 | (tile_count * 32) << 8
  292 bytes         canonical Huffman table: count[18], base[18], symbol[256]
  bitstream         every tile's 32 bytes as Huffman codes, MSB-first codes
                    packed LSB-first into little-endian words, padded to a word
  4 bytes           tool residue

The three residue values are leftover memory from the tool that built the
ROM (zero in about half of the tilesets, otherwise text fragments).
"""
import collections
import heapq
import struct
from dataclasses import dataclass

from decode_bgtile import decode_bgtile
from decode_gamma_lz import ROM_BASE, decode_gamma_lz_with_end
from encode_gamma_lz import _encode_once

TABLE_SIZE = 292
TILE_BYTES = 32


@dataclass
class Tileset:
    tiles: list[bytes]
    offset_table_residue: bytes   # 2 bytes after the gaps
    head_residue: bytes           # 4 bytes before the Huffman header word
    end_residue: bytes            # 4 bytes after the bitstream


def _gap_bytes(gaps: list[int]) -> bytes:
    out = bytearray()
    for gap in gaps:
        if 0x20 <= gap <= 0x20 + 0xFE:
            out.append(gap - 0x20)
        else:
            out += bytes([0xFF, gap >> 8, gap & 0xFF])
    return bytes(out)


def _huffman_lengths(freq: dict[int, int]) -> dict[int, int]:
    heap = [(count, i, [sym]) for i, (sym, count) in enumerate(sorted(freq.items()))]
    heapq.heapify(heap)
    depth = {sym: 0 for sym in freq}
    serial = len(heap)
    while len(heap) > 1:
        c1, _, s1 = heapq.heappop(heap)
        c2, _, s2 = heapq.heappop(heap)
        for sym in s1 + s2:
            depth[sym] += 1
        serial += 1
        heapq.heappush(heap, (c1 + c2, serial, s1 + s2))
    return depth


def _code_table(depth: dict[int, int]) -> tuple[bytes, dict[int, tuple[int, int]]]:
    """The 292-byte table and each symbol's (code, length)."""
    counts = [0] * 18
    for length in depth.values():
        counts[length - 1] += 1
    symbols = sorted(depth, key=lambda s: (depth[s], s))
    bases, total = [], 0
    for count in counts:
        bases.append(total & 0xFF)
        total += count
    table = bytes(counts) + bytes(bases) + bytes(symbols) + bytes(256 - len(symbols))
    codes, first, index = {}, 0, 0
    for length in range(18):
        for k in range(counts[length]):
            codes[symbols[index]] = (first + k, length + 1)
            index += 1
        first = (first + counts[length]) << 1
    return table, codes


def encode_tileset(ts: Tileset) -> bytes:
    freq = collections.Counter(b for tile in ts.tiles for b in tile)
    table, codes = _code_table(_huffman_lengths(freq))
    stream = bytearray()
    word = bits_in_word = total_bits = 0
    gaps = []
    for tile in ts.tiles:
        start = total_bits
        for byte in tile:
            code, length = codes[byte]
            for shift in range(length - 1, -1, -1):
                word |= ((code >> shift) & 1) << bits_in_word
                bits_in_word += 1
                total_bits += 1
                if bits_in_word == 32:
                    stream += struct.pack("<I", word)
                    word = bits_in_word = 0
        gaps.append(total_bits - start)
    if bits_in_word:
        stream += struct.pack("<I", word)

    raw = struct.pack("<H", len(ts.tiles)) + _gap_bytes(gaps) + ts.offset_table_residue
    stored = bytes([0x00]) + len(raw).to_bytes(3, "little") + raw
    packed = _encode_once(raw, False)
    container = packed if len(packed) < len(stored) else stored
    aligned = (len(container) + 3) & ~3
    return (struct.pack("<HH", aligned + 4, len(ts.tiles))
            + container + bytes(aligned - len(container))
            + ts.head_residue
            + bytes([0x20]) + (len(ts.tiles) * TILE_BYTES).to_bytes(3, "little")
            + table + bytes(stream) + ts.end_residue)


def decode_tileset(rom: bytes, ptr: int) -> Tileset:
    """Decode the tileset at ROM address ptr."""
    off = ptr - ROM_BASE
    size, count = struct.unpack_from("<HH", rom, off)
    header = rom[off + 4]
    if header & 0x80 or (header >> 4) & 7 not in (0, 6):
        raise ValueError(f"{ptr:#x}: unexpected offset table header {header:#x}")
    if (header >> 4) & 7 == 0:
        raw_size = int.from_bytes(rom[off + 5:off + 8], "little")
        raw = rom[off + 8:off + 8 + raw_size]
        container_len = 4 + raw_size
    else:
        raw, end = decode_gamma_lz_with_end(rom, ptr + 4)
        container_len = end - (ptr + 4)
    aligned = (container_len + 3) & ~3
    if size != aligned + 4 or struct.unpack_from("<H", raw)[0] != count:
        raise ValueError(f"{ptr:#x}: inconsistent tileset head")

    pos, gaps = 2, []
    for _ in range(count):
        if raw[pos] == 0xFF:
            gaps.append((raw[pos + 1] << 8) | raw[pos + 2])
            pos += 3
        else:
            gaps.append(0x20 + raw[pos])
            pos += 1
    offset_residue = raw[pos:]
    if len(offset_residue) != 2:
        raise ValueError(f"{ptr:#x}: unexpected offset table tail")

    head_residue = rom[off + 4 + aligned:off + 8 + aligned]
    if rom[off + 8 + aligned:off + 12 + aligned] != bytes([0x20]) + (count * TILE_BYTES).to_bytes(3, "little"):
        raise ValueError(f"{ptr:#x}: unexpected tile data header")
    table_off = off + 12 + aligned
    context = rom[table_off:table_off + TABLE_SIZE]
    stream_bit = (table_off + TABLE_SIZE) * 8
    tiles = []
    for gap in gaps:
        tiles.append(decode_bgtile(rom, stream_bit, context))
        stream_bit += gap
    stream_end = (stream_bit + 31) // 32 * 4
    end_residue = rom[stream_end:stream_end + 4]
    return Tileset(tiles, offset_residue, head_residue, end_residue)


def tileset_length(ts: Tileset) -> int:
    return len(encode_tileset(ts))
