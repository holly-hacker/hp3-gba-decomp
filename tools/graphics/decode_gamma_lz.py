#!/usr/bin/env python3
"""Decode a DecompressGammaLz resource from its outer-header address.

See docs/formats/graphics.md, "The DecompressGammaLz codec, decoded".
Usage: decode_gamma_lz.py <ver> <hex addr> (writes decoded bytes to stdout)
"""
import struct
import sys

ROM_BASE = 0x08000000


class _BitReader:
    """Read MSB-first bits from successive little-endian 32-bit words."""

    def __init__(self, rom: bytes, pos: int):
        self.rom = rom
        self.pos = pos
        self.word = 0
        self.remaining = 0

    def bits(self, count: int) -> int:
        value = 0
        for _ in range(count):
            if self.remaining == 0:
                self.word = struct.unpack_from("<I", self.rom, self.pos)[0]
                self.pos += 4
                self.remaining = 32
            self.remaining -= 1
            value = (value << 1) | ((self.word >> self.remaining) & 1)
        return value

    def gamma(self) -> int:
        ones = 0
        while ones < 7 and self.bits(1):
            ones += 1
        return (1 << ones) | self.bits(ones)


def decode_gamma_lz(rom: bytes, hdr_addr: int) -> bytes:
    """Decode the resource at hdr_addr, including its optional delta pass."""
    pos = hdr_addr - ROM_BASE
    header = rom[pos:pos + 4]
    extra_pass = bool(header[0] & 0x80)
    expected_size = header[1] | (header[2] << 8) | (header[3] << 16)
    pos += 4
    table_size, sentinel, distance_width, prefix_width = rom[pos:pos + 4]
    pos += 4
    if table_size == 0 or table_size & 3 or prefix_width > 8:
        raise ValueError(f"invalid GammaLz header at {hdr_addr:#x}")
    table = rom[pos:pos + table_size]
    pos += table_size
    reader = _BitReader(rom, pos)
    output = bytearray()
    literal_tail_width = 8 - prefix_width

    while True:
        prefix = reader.bits(prefix_width)
        if prefix != sentinel:
            output.append((prefix << literal_tail_width) | reader.bits(literal_tail_width))
            continue

        selector = reader.gamma()
        if selector >= 2:
            distance_code = reader.gamma()
            if distance_code == 0xFF:
                break
            distance_high = ((distance_code - 1) << distance_width) | reader.bits(distance_width)
            distance = (distance_high << 8) | reader.bits(8)
            distance += 1
            if distance > len(output):
                raise ValueError(f"invalid GammaLz distance {distance} at {hdr_addr:#x}")
            for _ in range(selector + 1):
                output.append(output[-distance])
            continue

        if reader.bits(1) == 0:
            # Selector 1, lookahead 00: length-two back-reference.
            distance = reader.bits(8) + 1
            if distance > len(output):
                raise ValueError(f"invalid GammaLz distance {distance} at {hdr_addr:#x}")
            output.append(output[-distance])
            output.append(output[-distance])
        elif reader.bits(1) == 0:
            # Selector 1, lookahead 01: swap the sentinel with a new
            # prefix, then emit the old sentinel as a literal prefix.
            new_sentinel = reader.bits(prefix_width)
            old_sentinel, sentinel = sentinel, new_sentinel
            output.append((old_sentinel << literal_tail_width) |
                          reader.bits(literal_tail_width))
        else:
            # Selector 1, lookahead 1: byte fill. Long runs gain a
            # high byte from a second gamma code.
            run_code = reader.gamma()
            high = 0
            if run_code >= 0x80:
                run_code = ((run_code << 1) | reader.bits(1)) & 0xFF
                high = reader.gamma() - 1
            fill_code = reader.gamma()
            if fill_code < 0x20:
                fill = table[fill_code - 1]
            else:
                fill = ((fill_code << 3) | reader.bits(3)) & 0xFF
            output.extend(bytes((fill,)) * (run_code + 1 + (high << 8)))

    if len(output) != expected_size:
        raise ValueError(f"{hdr_addr:#x}: decoded {len(output)} bytes, expected {expected_size}")
    result = bytes(output)
    return _apply_delta_pass(result) if extra_pass else result


def _apply_delta_pass(buf: bytes) -> bytes:
    """Integrate delta-coded u16 values when the outer-header flag is set."""
    n = len(buf) // 2
    vals = list(struct.unpack(f"<{n}H", buf[:n * 2]))
    for i in range(1, n):
        vals[i] = (vals[i] + vals[i - 1]) & 0xFFFF
    return struct.pack(f"<{n}H", *vals) + buf[n * 2:]


def main() -> None:
    if len(sys.argv) != 3:
        sys.exit(f"usage: {sys.argv[0]} <ver> <hex addr>")
    ver, addr_s = sys.argv[1], sys.argv[2]
    addr = int(addr_s, 16)
    with open(f"baserom.{ver}.gba", "rb") as f:
        rom = f.read()
    sys.stdout.buffer.write(decode_gamma_lz(rom, addr))


if __name__ == "__main__":
    main()
