#!/usr/bin/env python3
"""Encode data in the GBA BIOS LZ77UnComp format, byte-identical to the ROM's encoder.

tools/graphics/decode_bios.py's lz77_uncomp is the inverse. The result starts
with the 4-byte BIOS header (type 1, decompressed size). The parse reproduces
every LZ77 stream among the room tilemap, block and collision resources: the
longest match wins (at most 18 bytes), the nearest one on a tie, a match must
be at least 3 bytes, and the distance is at least 2 (distance 1 would make the
VRAM-safe 16-bit writes overlap).
"""
MIN_MATCH = 3
MAX_MATCH = 18
MIN_DISTANCE = 2
WINDOW = 4096


def encode_bios_lz77(data: bytes) -> bytes:
    if len(data) >= 1 << 24:
        raise ValueError("LZ77 input exceeds the 24-bit size field")
    out = bytearray((0x10, len(data) & 0xFF, (len(data) >> 8) & 0xFF, len(data) >> 16))
    positions: dict[bytes, list[int]] = {}
    for start in range(len(data) - 2):
        positions.setdefault(data[start:start + 3], []).append(start)
    pending = len(data)
    i = 0
    n = len(data)
    while i < n:
        flags = 0
        block = bytearray()
        for bit in range(8):
            if i >= n:
                break
            best_len, best_dist = 0, 0
            for src in reversed(positions.get(data[i:i + 3], ())):
                if src >= i:
                    continue
                dist = i - src
                if dist > WINDOW:
                    break
                if dist < MIN_DISTANCE:
                    continue
                length = 0
                while length < MAX_MATCH and i + length < n and data[i + length - dist] == data[i + length]:
                    length += 1
                if length > best_len:
                    best_len, best_dist = length, dist
                    if length == MAX_MATCH:
                        break
            if best_len >= MIN_MATCH:
                flags |= 0x80 >> bit
                block.append(((best_len - MIN_MATCH) << 4) | ((best_dist - 1) >> 8))
                block.append((best_dist - 1) & 0xFF)
                i += best_len
            else:
                block.append(data[i])
                i += 1
        out.append(flags)
        out.extend(block)
    del pending
    return bytes(out)
