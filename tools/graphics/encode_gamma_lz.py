#!/usr/bin/env python3
"""Encode data as a DecompressGammaLz resource, byte-identical to the ROM.

Token choices come from pucrunch_gammalz.py (Pucrunch 1.11's passes, LGPL);
this file writes the game's container around them. See
docs/formats/graphics.md, "The DecompressGammaLz codec, decoded";
decode_gamma_lz.py is the inverse.

- Outer header: type 6 in bits 4-7, delta flag 0x80, 24-bit decoded size.
- Inner header: table size, initial escape prefix, LZ distance extra bits,
  escape (prefix) bits; then the RLE byte table.
- Tokens are written MSB-first into little-endian 32-bit words, and the
  last word is zero-padded.
- The resource is also encoded after u16 delta coding, and that version is
  kept when it is strictly shorter.

Usage: encode_gamma_lz.py <ver> <hex addr> (re-encodes the ROM resource
and reports whether it matches)
"""
import struct
import sys

from pucrunch_gammalz import LITERAL, LZ77, RANKS, RLE, parse

TYPE_GAMMA_LZ = 6
DELTA_FLAG = 0x80
# Final byte of every 32-entry table (read from one past the 31 ranks).
TABLE_TAIL = 0x45


class _BitWriter:
    def __init__(self):
        self.words = bytearray()
        self.word = 0
        self.count = 0

    def bits(self, value: int, count: int) -> None:
        for shift in range(count - 1, -1, -1):
            self.word = (self.word << 1) | ((value >> shift) & 1)
            self.count += 1
            if self.count == 32:
                self.words += struct.pack("<I", self.word)
                self.word = self.count = 0

    def gamma(self, value: int) -> None:
        ones = value.bit_length() - 1
        self.bits((1 << ones) - 1, ones)
        if ones < 7:
            self.bits(0, 1)
        self.bits(value - (1 << ones), ones)

    def finish(self) -> bytes:
        if self.count:
            self.bits(0, 32 - self.count)
        return bytes(self.words)


def _encode_once(data: bytes, delta: bool) -> bytes:
    p = parse(data)
    pw, dw = p.escape_bits, p.extra_lz_pos_bits
    tail = 8 - pw
    escape = p.start_escape >> tail if pw else 0
    first_escape = escape
    codes: dict[int, int] = {}
    for rank in range(1, RANKS):
        codes.setdefault(p.rle_values[rank], rank)

    w = _BitWriter()
    for mode, pos, length, dist in p.tokens:
        if mode == LITERAL:
            byte = data[pos]
            if (byte >> tail) != escape:
                w.bits(byte, 8)
                continue
            # Escaped literal: switch escape, then the literal's low bits.
            new = p.new_escapes[pos] >> tail if pw else 0
            w.bits(escape, pw)
            w.gamma(1)
            w.bits(0b10, 2)
            w.bits(new, pw)
            w.bits(byte & ((1 << tail) - 1), tail)
            escape = new
            continue
        w.bits(escape, pw)
        if mode == LZ77 and length > 2:
            w.gamma(length - 1)
            w.gamma(((dist - 1) >> (8 + dw)) + 1)
            w.bits(((dist - 1) >> 8) & ((1 << dw) - 1), dw)
            w.bits((dist - 1) & 0xFF, 8)
        elif mode == LZ77:
            w.gamma(1)
            w.bits(0, 1)
            w.bits(dist - 1, 8)
        else:
            assert mode == RLE
            w.gamma(1)
            w.bits(0b11, 2)
            count = length - 1
            if count < 0x80:
                w.gamma(count)
            else:
                w.gamma(0x80 | ((count & 0xFF) >> 1))
                w.bits(count & 1, 1)
                w.gamma((count >> 8) + 1)
            value = data[pos]
            code = codes.get(value, 32 + (value >> 3))
            w.gamma(code)
            if code >= 32:
                w.bits(value & 7, 3)
    w.bits(escape, pw)
    w.gamma(2)
    w.gamma(255)

    table_size = min(32, 4 * (p.rle_used // 4 + 1))
    table = bytes(p.rle_values[1:table_size + 1])
    if table_size == 32:
        table += bytes((TABLE_TAIL,))
    n = len(data)
    header = bytes((TYPE_GAMMA_LZ << 4 | (DELTA_FLAG if delta else 0),
                    n & 0xFF, (n >> 8) & 0xFF, n >> 16,
                    table_size, first_escape, dw, pw))
    return header + table + w.finish()


def _delta_code(data: bytes) -> bytes:
    """Inverse of decode_gamma_lz._apply_delta_pass."""
    n = len(data) // 2
    vals = struct.unpack(f"<{n}H", data[:n * 2])
    deltas = [(vals[i] - vals[i - 1]) & 0xFFFF if i else vals[0] for i in range(n)]
    return struct.pack(f"<{n}H", *deltas) + data[n * 2:]


def encode_gamma_lz(data: bytes) -> bytes:
    """Return the complete resource (headers, table, and bitstream)."""
    data = bytes(data)
    if len(data) >= 1 << 24:
        raise ValueError("GammaLz input must be under 16 MiB")
    plain = _encode_once(data, False)
    delta = _encode_once(_delta_code(data), True)
    return delta if len(delta) < len(plain) else plain


def main() -> None:
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} <ver> <hex addr>")
    from decode_gamma_lz import ROM_BASE, decode_gamma_lz
    ver, addr = sys.argv[1], int(sys.argv[2], 16)
    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()
    encoded = encode_gamma_lz(decode_gamma_lz(rom, addr))
    start = addr - ROM_BASE
    match = rom[start:start + len(encoded)] == encoded
    print(f"{addr:#x}: {len(encoded)} bytes, {'match' if match else 'MISMATCH'}")
    sys.exit(0 if match else 1)


if __name__ == "__main__":
    main()
