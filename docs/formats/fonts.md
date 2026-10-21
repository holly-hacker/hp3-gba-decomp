# Text fonts

The game has ten variable-width 2 bpp Latin fonts (US and JP, the same
bytes). JP also has four kanji/kana fonts just before them, at 9, 12, 12 and
8 pixels high in ROM order. The Latin fonts cover codes `0x20`-`0xBC`. The
kanji fonts cover two-byte codes `0xF000`-`0xF423`, carry a glyph flags table
and use a fixed width equal to their height. The matched C (`src/font/`)
selects and draws them. The blob layout is in `tools/fonts/fonts.py`.

Latin glyphs `A`-`Z` and `0`-`9` render as those characters at their ASCII
codes. The other codes were not checked visually. See [`text.md`](text.md)
for the charmap.

A `fonts` run (see [`graphics.md`](graphics.md) "Graphics build format")
holds each font as a grayscale PNG glyph atlas (`Font00`-`Font09`). The
font's range, height, glyph widths and flags are in the run's settings.
