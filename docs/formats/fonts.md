# Text fonts

Ten variable-width 2 bpp Latin fonts, contiguous at US `0x08E65D6C`-`0x08E6D438`
(JP `0x08E836C4`-`0x08E8AD90`, the same bytes; **PROVEN**), and in JP four
two-byte-glyph fonts for kana and kanji just before them
(`0x08E63D50`-`0x08E836C4`). The text engine (`DrawString`, `GetGlyphWidth`;
see [`text.md`](text.md)) reads them through `FontDescriptor`s in RAM.

## Selection (STRUCTURAL MATCH)

`SelectTextFont(index, color, ...)` points `gTextRenderState` at the descriptor
`index` of `g_aFontDescriptors` (`0x03002F30`, two descriptors per font index:
`0x14` bytes each in US, `0x18` in JP, which adds `pGlyphFlags`).
`InitTextMacroTable` fills them at boot through `LoadFontDescriptor(index,
slot)`, which reads the blob header below from a ROM table of `{font pointer,
value}` entries. The value is copied into the descriptor's `unk6`; its meaning
is not traced.

- US `g_aFontTable`, 12 entries at `0x080604DC`, slot 0 only: 0-9 are the ten
  Latin fonts in ROM order (values 8, 8, 8, 16, 16, 13, 16, 8, 8, 8); entries
  10 and 11 reuse fonts 7 and 9 (values 12 and 8).
- JP fills both slots. Slot 1 comes from `g_aExtFontTable` (12 entries at
  `0x08060408`): 0-2 and 7-9 are the 9-pixel kanji font (value 9), 3-4 the
  first 12-pixel kanji font (16), 5-6 the second 12-pixel one (16), 10 the
  first 12-pixel one again (12), 11 the 8-pixel one (8). Slot 0 comes from
  `g_aFontTable` (12 entries at `0x08060468`): the ten Latin fonts in ROM order
  (values 8, 8, 8, 16, 16, 13, 16, 8, 8, 8), then Latin fonts 5 and 9 (12 and
  8; US reuses 7 and 9). Both slots take `unk6` from `g_aExtFontTable`.

## Font blob (PROVEN: all fourteen rebuild byte for byte)

```
u16 first, last      glyph codes covered, little-endian
u8  height           rows per glyph
u8  0
u16 offsets_at       0x0010 (big-endian, as are the next three)
u16 flags_at         offset of the glyph flags, 0 for none
u16 widths_at        offset of the widths
u16 0
u16 bitmaps_at       offset of the bitmaps
u16[n] offsets       bitmap offsets, little-endian, from bitmaps_at
flags                2 bits per glyph, low bits first, padded to 4 bytes
u8[n]  widths        pixels per glyph
bitmaps              per glyph, width * height pixels of 2 bits, column by
                     column, the rows of a column top to bottom, low bits
                     first; each glyph padded to a byte, packed in order
zeros                to a multiple of 4 bytes
```

Each table starts on a 4-byte boundary. The Latin fonts cover `0x20`-`0xBC` (157
glyphs, no flags). The kanji fonts cover `0xF000`-`0xF423` (1060 two-byte
codes), have a flags table (`FontDescriptor.pGlyphFlags`; see `DrawTextLine`)
and a fixed width equal to their height.

The offsets are the running sum of the glyph sizes, so they are derived. The
draw loop (`DrawString`) reads a glyph by column, ORs the 2-bit value into the
destination pixel with the current color as base, and skips value 0. Which
fonts are used where is not mapped.

The Latin heights are 8 (fonts 0-2 and 7-9), 13 (font 3) and 15 (fonts 4-6); the kanji fonts are 9, 12, 12 and 8 (in ROM order).
Latin glyphs `A`-`Z` and `0`-`9` render as those characters at their ASCII codes (a
visual check); the other codes are not checked. The kanji fonts render kana and
kanji.

## Extraction

A `fonts` run (see [`graphics.md`](graphics.md) "Graphics build format")
covers the ten fonts as one grayscale PNG glyph atlas per font
(`Font00`-`Font09`, 16 glyphs per row, each cell as wide as the widest glyph,
pixel value 0 transparent); its `fonts` settings list each font's range,
height and glyph widths (and flags).
