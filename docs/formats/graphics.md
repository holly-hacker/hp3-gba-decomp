# Graphics asset format

The C under `src/` defines how the game reads its graphics:
`DecompressResource`/`DecompressResourceVram` (`include/decompress.h`), the
actor frame data (`include/actor.h`), and BG tile streaming
(`src/scroll/`). This document covers the build format and how the original
tools encoded the data.

## Compressed resources

A resource begins with a 4-byte `ResourceHeader`. Bits 4-6 of byte 0 give
the type, bit 7 asks for the `u16` delta pass, and bytes 1-3 hold the
decoded size. The two dispatchers map types to codecs differently. A BIOS
RLE stream on the VRAM path (type 3) repeats the header at `+4`.

| Codec | Python decoder | Python encoder |
|---|---|---|
| BIOS LZ77 / Huffman / RLE | `decode_bios.py` | `encode_bios_rle.py`, `encode_bios_lz77.py` |
| `DecompressLzRle` | `decode_lz_rle.py` | `encode_lz_rle.py` |
| `DecompressGammaLz` | `decode_gamma_lz.py` | `encode_gamma_lz.py` + `pucrunch_gammalz.py` |
| `DecompressBgTile` | `decode_bgtile.py` | `bgtileset.py` |

The tools are in `tools/graphics/`. Each encoder's docstring gives the
parse rules that reproduce the ROM's streams.

### GammaLz: Pucrunch 1.11

The GammaLz token stream is
[Pucrunch](https://a1bert.kapsi.fi/Dev/pucrunch/) 1.11 (30-Jan-2000) by
Pasi Ojala, run with its default options. The 1.11 DOS build
(`pucrunch_x86_old.zip`, run in DOSBox with `-d -c0`) chooses the same
tokens, escape and distance widths, initial escape, and rank table for the
pre-delta data of all 1,605 GammaLz resources in the US ROM. The 1.11
source survives only in Internet Archive snapshots of
`www.cs.tut.fi/~albert/Dev/pucrunch/pucrunch.c` (2001-2006). Later releases
make different choices: 1.14 adds an all-lengths search in `OptimizeLength`,
drops the RESCAN condition `lzlen > rle`, and cuts the fill ranks from 31
to 15.

`pucrunch_gammalz.py` translates 1.11's token-choosing passes (LGPL v2.1),
and `encode_gamma_lz.py` writes the game's container around them. The
container differs from Pucrunch's own output:

- the 4-byte codec header (see `asm/decompress_gamma_lz.s`) replaces
  Pucrunch's C64 header.
- the fill table is `rleValues[1..]` rounded up to a multiple of 4 bytes
  (`min(32, 4*(rleUsed/4+1))`), so unused ranks keep their initial
  ranking. Every 32-byte table ends in `0x45`.
- distance low bytes are stored as they are, not XORed with `0xFF`.
- bits are packed MSB-first into little-endian 32-bit words, and the last
  word is zero-padded.
- a resource is also compressed after `u16` delta coding, and that version
  is used, with flag `0x80`, when its stream is strictly shorter.

The match search is O(n^2), so the largest resource (63 KB) takes about
15 s to encode. The build cache (`tools/buildcache.py`) and
`build/cache/gammalz/` keep the encoded results.

## Graphics build format

A `graphics <feature> <Group>` manifest row claims one group:
contiguous graphics of one feature, such as a minigame's sprites and
backgrounds. `graphics/<feature>.yaml` describes the feature's groups for
both versions. A version that lacks a group has no row for it. A group is a
list of runs, and each run has one kind: `image-bank` (this document),
`graphic-blobs` and `tile-streams` ([`graphic_blob.md`](graphic_blob.md)),
`tile-frames` ([`special_scene_frames.md`](special_scene_frames.md)),
`fonts` ([`fonts.md`](fonts.md)) or `room-graphics`
([`room_graphics.md`](room_graphics.md)):

```yaml
groups:
  - name: PumpkinGraphics
    runs:
      - kind: image-bank
        count: 43
        names: {1: Pumpkin001}
      - kind: graphic-blobs
        names: [ServePumpkinJuiceBg0Graphic, ServePumpkinJuiceBg1Graphic, ServePumpkinJuiceBg2Graphic]
```

`names` either lists one name per item or maps one-based positions to
names. A mapped name covers the items from its position up to the next
entry, counting up the name's trailing number, and `count` gives the run's
length. Every item is labeled `g<Name>`, and images add a component suffix
(`gItem001Tiles`). Other keys are the kind's options, such as an image
run's `bpp`. Only values that differ from the kind's `OPTIONS` defaults are
written.

The editable files live in `data/graphics/<feature>/` (`battle`,
`overworld`, `menus`, `cutscenes`, `minigames/<game>`, `rooms`). Each
directory's `graphics.json` (`format: 2`) holds each group's item settings,
run by run, without names or addresses. Every file in the directory must
belong to exactly one group. A subdirectory with its own `graphics.json` is
a nested feature: `menus/us` and `menus/jp` hold the groups only one
version has, whose files would otherwise collide.

`just pack <ver>` (`tools/graphics/pack_graphics.py`, kinds in
`tools/graphics/kinds/`) builds every item through the build cache and
writes `build/<ver>/graphics/<Group>.bin` and `.s`.
`include/gen/graphics/<feature>.h` declares the
labels of every group in the feature, including groups only the other
version has, so the headers are the same for both versions and are
committed.

`just extract-graphics [group ...]` (`tools/graphics/extract_graphics.py`)
walks each group from its start in the donor ROM, which the script lists
with its end for each version. It takes each item's length from the item
itself and each run's length from its names, and the walk must end exactly
at the group's end. Each group is extracted once, from the US ROM if its
manifest has the group and from JP otherwise, and every item must rebuild
byte for byte. With no group names it replaces all of `data/graphics/`.

An `image-bank` run's options are:

- `bpp`: 4 or 8.
- `componentOrder`: the ROM order of each image's `palette`/`tiles`/`frames`
  components.
- `storedCells`.
- `noPalette`.
- `paletteHeader`/`paletteTrailer`: bytes around every palette.
- `paletteSources`: maps a sprite without a palette to the item whose
  palette the game draws it with. Extraction colors the sprite's PNGs with
  that palette, and packing ignores it.

An image's settings in `graphics.json` take one of three forms:

- a **derived sprite**, `{offset, compression}`: one frame, `<name>.png`,
  with cells cut from the image size (see "Sprite images").
- a **stored-layout sprite**, `{palette, header, frames}`: `<name>.png`, a
  sheet of all its frames. Each frame lists `offset`, `compression`, `cells`
  (`[x, y, w, h]` in tiles), `parts` and `extra`, plus `size` when the frame
  is smaller than the sheet's cells. `palette: false` means the sprite's
  palette lives elsewhere. Its PNG then carries the `paletteSources` palette
  or a gray one, and packing ignores it.
- a **palette**, `{paletteOnly: true}`: `<name>.png`, a one-row swatch whose
  PNG palette is the data.

Components are labeled `g<Name><Component>`, and components an entry lacks
are skipped. Packing fails on a PNG that is not indexed, on a pixel index
or palette outside the bit depth, and on a drawn pixel outside every cell.
In a stored-layout run:

- a sprite's tiles are its frame streams back to back.
- a sprite's palette is present only when the next data is not a tile
  stream.
- a palette that is not followed by tiles is its own entry.
- a sprite without a palette whose next data is not a tile stream is listed
  in `noPalette`.

## Sprite images

Each image is one indexed PNG plus a few settings per frame.
`tools/images/sprite.py` derives everything else and requires every
component to rebuild byte for byte.

- **PNG**: each frame's full pixel canvas, 4-bit or 8-bit indexed. Its
  `PLTE` is the ROM palette in order, including entry 0's stored color
  (usually `0x7C1F` magenta), and `tRNS` makes index 0 transparent for
  viewing. Channels convert as `c5 << 3 | c5 >> 2` on extraction and
  `c8 >> 3` on packing. Short palettes are padded with black.
- **Sheet** (stored-layout sprites): the frames in order, left to right, 8
  per row, in equal cells as large as the widest and tallest frame. A frame
  fills its cell's top-left corner, `size` pixels when smaller than the
  cell. Every other sheet pixel must be index 0.
- **`offset`**: the canvas's top-left pixel relative to the actor's anchor.
- **`compression`**: `lzrle` (`DecompressResourceVram` type 7), `rle`
  (type 3), `gammalz` (type 6) or `raw` (type 0), chosen per frame. Some
  sprites mix codecs. No size rule picks between them: every `rle` item
  icon would be 2-5 bytes smaller as `lzrle`.
- **`padding`** (stored-cells frames only, optional): the bytes after the
  stream's last token, recorded when any of them is nonzero.

**Cell cutting** (derived sprites; every item icon and portrait matches
it): each canvas dimension, in tiles, splits into power-of-two strips,
smallest first (7 -> 1, 2, 4; 10 -> 2, 8). Cells are emitted row strip by
row strip, with column strips left to right. A strip intersection that has
no OAM shape is halved along its longer side (8x1 -> two 4x1, 1x8 -> two
1x4, top or left first). Each cell's tile offset is the running tile count
at the sprite's bit depth. The tile data is the cells' 8x8 tiles, row-major
within each cell, with the low nibble first at 4bpp.

**Stored cells**: the overworld monster sprites and the battle sprites fit
their cells to the drawing. They skip empty areas and shift cells to cover
the art, and similar frames of one sprite can get different layouts. No
rule is known that reproduces every layout, so these banks keep each
frame's cells.

**Tile streams** are made of the 4-byte resource header, the compressed
stream, then zero bytes up to a word boundary at least five bytes past the
last token. The first of those zero bytes is the LzRle end token. `raw` and
`gammalz` streams instead end on a word boundary followed by one padding
word. Padding is zero in all but four sprite streams: two GammaLz words
(`00 14 33 00`, `00 14 A4 00`) and two LzRle tails with a single `0x10`
byte.

## Unconfirmed

- Why every 32-byte GammaLz fill table ends in `0x45`. It may be one entry
  past the 31 ranks.
- The nonzero stream padding and the BG tileset residue bytes look like
  leftover memory from the original tools.
- Whether any code uses the ally head frames other than frame 0 (the
  turn-order icon).
- Help sprite record 14 looks unused: the help pages never draw indices
  3-6, 8 or 14. Pages outside the help page data were not searched.
- No `DecompressResource` type-4 (LzRle) resource exists, so that path's
  stream layout (`hdr`, not `hdr+4`) has never been exercised.
