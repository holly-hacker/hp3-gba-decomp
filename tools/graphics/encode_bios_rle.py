#!/usr/bin/env python3
"""Encode data in the GBA BIOS RLUnComp format, byte-identical to the ROM's encoder.

tools/graphics/decode_bios.py's rl_uncomp is the inverse. The result starts
with the 4-byte BIOS header (type 3, decompressed size). The parse reproduces
every RLE stream in the US item-icon bank: a run of at least 3 equal bytes is
a run token, anything else accumulates as literals, and both token kinds are
capped at 127 bytes even though the format allows 130-byte runs and 128-byte
literal blocks.
"""
MAX_TOKEN = 127
MIN_RUN = 3


def encode_bios_rle(data: bytes) -> bytes:
    if len(data) >= 1 << 24:
        raise ValueError("RLE input exceeds the 24-bit size field")
    out = bytearray((0x30, len(data) & 0xFF, (len(data) >> 8) & 0xFF, len(data) >> 16))
    literal_start = 0
    i = 0

    def flush_literals(end: int) -> None:
        for start in range(literal_start, end, MAX_TOKEN):
            chunk = data[start:min(end, start + MAX_TOKEN)]
            out.append(len(chunk) - 1)
            out.extend(chunk)

    while i < len(data):
        j = i + 1
        while j < len(data) and j - i < MAX_TOKEN and data[j] == data[i]:
            j += 1
        if j - i >= MIN_RUN:
            flush_literals(i)
            out.extend((0x80 | (j - i - MIN_RUN), data[i]))
            i = j
            literal_start = i
        else:
            i += 1
    flush_literals(len(data))
    return bytes(out)
