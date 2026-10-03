"""Text fonts: a variable-width 2 bpp bitmap font (see docs/formats/fonts.md).

A font blob is a 16-byte header, a table of glyph bitmap offsets, an optional
table of glyph flags, a width per glyph and the bitmaps:

    u16 first, last      first and last glyph code (little-endian)
    u8  height           rows per glyph
    u8  0
    u16 offsets_at       offset of the bitmap offset table (big-endian); 0x10
    u16 flags_at         offset of the flags, or 0 for none (big-endian)
    u16 widths_at        offset of the widths (big-endian)
    u16 0
    u16 bitmaps_at       offset of the bitmaps (big-endian)
    u16[n] offsets       little-endian, from bitmaps_at; the running sum of the
                         glyph sizes
    flags                2 bits per glyph, low bits first, padded to 4 bytes
    u8[n] widths
    bitmaps              per glyph, in order: width * height pixels of 2 bits,
                         column by column, the rows of a column top to bottom,
                         low bits first, padded to a byte
    zeros                to a multiple of 4 bytes

Each table starts on a 4-byte boundary. A font is edited as <name>.png, an
atlas of its glyphs, 16 per row, each in a cell as wide as the widest glyph
and as tall as the font. A pixel is the 2-bit value (0 is transparent). Glyph
widths and flags are kept in bank.json: they are not derived from the pixels.
"""
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "graphic_blob"))
from blobs import ROM_BASE  # noqa: E402

GLYPHS_PER_ROW = 16
OFFSETS_AT = 0x10
GRAY = [(255, 255, 255), (170, 170, 170), (85, 85, 85), (0, 0, 0)] + [(0, 0, 0)] * 252


class Font:
    def __init__(self, first, last, height, widths, glyphs, flags=None):
        self.first, self.last, self.height = first, last, height
        self.widths, self.flags = widths, flags
        self.glyphs = glyphs        # per glyph: list of height rows of width values 0-3


def _bitmap_size(width: int, height: int) -> int:
    return (width * height * 2 + 7) // 8


def _align4(n: int) -> int:
    return n + (-n % 4)


def _layout(count: int, has_flags: bool):
    """Offsets of the flags (0 for none), widths and bitmaps."""
    flags_at = _align4(OFFSETS_AT + 2 * count) if has_flags else 0
    after_flags = flags_at + 4 * ((count + 15) // 16) if has_flags else OFFSETS_AT + 2 * count
    widths_at = _align4(after_flags)
    return flags_at, widths_at, _align4(widths_at + count)


def parse(rom: bytes, addr: int) -> tuple[Font, int, bytes]:
    """The font at ROM address addr, the address just past it, and its bytes."""
    pos = addr - ROM_BASE
    first, last = struct.unpack_from("<HH", rom, pos)
    height = rom[pos + 4]
    count = last - first + 1
    offsets_at, flags_at, widths_at, zero, bitmaps_at = struct.unpack_from(">5H", rom, pos + 6)
    if rom[pos + 5] != 0 or zero != 0 or offsets_at != OFFSETS_AT or count <= 0 \
            or (flags_at, widths_at, bitmaps_at) != _layout(count, bool(flags_at)):
        raise ValueError(f"{addr:#x}: unsupported font header {bytes(rom[pos:pos + 16]).hex()}")
    widths = list(rom[pos + widths_at:pos + widths_at + count])
    size = _align4(bitmaps_at + sum(_bitmap_size(w, height) for w in widths))
    raw = rom[pos:pos + size]
    offsets = struct.unpack_from(f"<{count}H", raw, OFFSETS_AT)
    flags = None
    if flags_at:
        flags = [(raw[flags_at + i // 4] >> (2 * (i % 4))) & 3 for i in range(count)]
    glyphs, cursor = [], 0
    for i, width in enumerate(widths):
        if offsets[i] != cursor:
            raise ValueError(f"{addr:#x}: glyph {i} is not packed in order")
        n = _bitmap_size(width, height)
        data = raw[bitmaps_at + cursor:bitmaps_at + cursor + n]
        cols = [[(data[(2 * k) // 8] >> ((2 * k) % 8)) & 3 for k in range(x * height, (x + 1) * height)]
                for x in range(width)]
        glyphs.append([[cols[x][y] for x in range(width)] for y in range(height)])
        cursor += n
    font = Font(first, last, height, widths, glyphs, flags)
    if build(font) != raw:
        raise ValueError(f"{addr:#x}: font does not rebuild to its bytes")
    return font, addr + size, raw


def build(font: Font) -> bytes:
    count = len(font.widths)
    flags_at, widths_at, bitmaps_at = _layout(count, font.flags is not None)
    out = bytearray(struct.pack("<HH", font.first, font.last))
    out += bytes([font.height, 0]) + struct.pack(">5H", OFFSETS_AT, flags_at, widths_at, 0, bitmaps_at)
    bitmaps, offsets = bytearray(), []
    for width, glyph in zip(font.widths, font.glyphs):
        offsets.append(len(bitmaps))
        data = bytearray(_bitmap_size(width, font.height))
        k = 0
        for x in range(width):
            for y in range(font.height):
                data[(2 * k) // 8] |= glyph[y][x] << ((2 * k) % 8)
                k += 1
        bitmaps += data
    out += struct.pack(f"<{count}H", *offsets)
    if font.flags is not None:
        out += b"\0" * (flags_at - len(out))
        table = bytearray(4 * ((count + 15) // 16))
        for i, v in enumerate(font.flags):
            table[i // 4] |= v << (2 * (i % 4))
        out += table
    out += b"\0" * (widths_at - len(out))
    out += bytes(font.widths)
    out += b"\0" * (bitmaps_at - len(out))
    out += bitmaps
    out += b"\0" * (-len(out) % 4)
    return bytes(out)


def atlas(font: Font):
    """Size and pixels of the glyph atlas."""
    cw, ch = max(font.widths), font.height
    rows = (len(font.glyphs) + GLYPHS_PER_ROW - 1) // GLYPHS_PER_ROW
    w = GLYPHS_PER_ROW * cw
    pixels = [0] * (w * rows * ch)
    for n, glyph in enumerate(font.glyphs):
        x0, y0 = (n % GLYPHS_PER_ROW) * cw, (n // GLYPHS_PER_ROW) * ch
        for y, row in enumerate(glyph):
            pixels[(y0 + y) * w + x0:(y0 + y) * w + x0 + len(row)] = row
    return (w, rows * ch), pixels


def glyphs_from_atlas(pixels, widths, height: int):
    cw = max(widths)
    w = GLYPHS_PER_ROW * cw
    glyphs = []
    for n, width in enumerate(widths):
        x0, y0 = (n % GLYPHS_PER_ROW) * cw, (n // GLYPHS_PER_ROW) * height
        glyphs.append([[pixels[(y0 + y) * w + x0 + x] for x in range(width)] for y in range(height)])
    return glyphs
