# Graphic blobs

A self-contained BG graphic: optional palette, tilemap and tile data in one
byte string, loaded by `sub_080065D4` (via `sub_080077C8`, which then writes
the tilemap with `WriteBgGraphicTilemap_candidate`). Users include the battle
backgrounds, the Wizard Cracker minigame, the Lupin potion cutscene and the
debug collector-cards menu. `LoadEmbeddedPalette_candidate` reads the same
header for the palette alone.

## Layout (PROVEN for the battle background blob at `0x08856710`; other flag combinations are read from `sub_080065D4`, STRUCTURAL MATCH)

```
u8   flags0
u8   flags1
...  palette         bit 0: 512 bytes (256 colors); else bit 1: 32 bytes (16)
u16  length, data    bit 2: raw bytes DMA'd to the start of VRAM
...  tilemap         bits 3 and 4: u16 width, u16 height, then one cell per
                     tile (bytes if flags1 bit 0, else halfwords); padded to
                     an even byte count
u16  length, stream  bit 4: tile data, decoded into the BG's character block
```

| Bit | Meaning |
|---|---|
| `flags0` 0 / 1 | 512-byte / 32-byte palette |
| `flags0` 2 | raw VRAM block |
| `flags0` 3 | tilemap present |
| `flags0` 4 | tile stream present |
| `flags0` 5-6 | tile stream codec: 0 raw, 1 BIOS RLE, 2 BIOS LZ77, 3 GammaLz |
| `flags0` 7 | 8 bpp tiles (64 bytes per tile; else 32) |
| `flags1` 0 | tilemap cells are bytes |
| `flags1` 6-7 | tilemap is split over several 32x32 screens (0x40, 0x80, 0xC0 select the layouts) |

`length` is the stream's size in the ROM. Codec 3 calls
`g_pDecompressGammaLzEntry` on the data right after the length. That stream has
no outer 4-byte header (flags and size): it starts at the table-size, sentinel,
distance-width and prefix-width bytes, so `tools/graphics/decode_gamma_lz.py`
needs those 4 bytes prepended to decode it. The decoded size is not stored.

## Battle backgrounds

`InitBattleBackground_candidate` indexes a table at `0x0804E09C` by room id
(55 rooms, 8 bytes each): a pointer to the floor blob, then to the wall blob.
The 55 rooms share 14 floor/wall pairs. The 28 blobs are contiguous from
`0x08856710` to `0x08882CFC`, and each blob's parsed end is the next blob's
start (**PROVEN**, all 28). They alternate:

- floor, flags `0xF9 0x01`: 32x32 tilemap of byte cells, GammaLz 8 bpp tiles
  (1024 to 20800 bytes decoded);
- wall, flags `0x19 0x00`: 32x9 tilemap of halfword cells (tile, flips and
  palette bank as in a BG screen entry), raw 4 bpp tiles.

Every blob renders as a coherent image with its own palette (stone, tile,
carpet, grass, sand, wood floors; castle, library, clock-hall and forest
walls). Which room uses which pair is not yet mapped. The alternate pair
used for rooms `8`-`15` when the quest flag `0x1A` is set (`0x08882CFC`,
`0x08886004`) follows the table's last blob.

## The blob run

195 blobs are contiguous from `0x08856710` to `0x089AD364` (JP
`0x08856540`-`0x089AD194`, the same bytes; **PROVEN**: the
walk, which reads each blob's length from the blob, ends there; the bytes
after it are not a blob). After the 30 above come 165 more, all wall-type
(`0x19 0x00`, 4 bpp, halfword cells). Their images are full-screen effect
frames (burst and streak sequences among them) and a few screens with number
grids; the users of these blobs are not traced.

## Extraction

`just extract-graphic-blobs` writes `data/graphic_blobs/bg_graphics/`
(gitignored): one indexed PNG per blob, `<name>.png`, and `bank.json` with each
blob's flags. The pixel values are palette indices (`bank * 16 + color number`
for 4 bpp, the color number for 8 bpp), and the PNG palette is the blob's 256
colors. `just pack-graphic-blobs` rebuilds the blobs; the manifest row is
`graphic-blobs <start> <end> <dir> <name>`, and each blob gets a label
`g<BlobName>` and a declaration in `include/gen/<name>.h`.

The tiles and tilemap are derived from the image, in the order the original
tool produced them (all 195 blobs reproduce): tiles in order of first use, a
cell reuses an earlier tile when it matches it or its horizontal, vertical or
both-ways flipped copy (tried in that order), and a tile's palette bank is part
of its identity, so two cells with the same pixels but different banks use
separate tiles. Byte-cell blobs have no flips. Three floor blobs carry 58 or 69
tiles after the last one the tilemap uses; they are kept in
`<name>.unused.png`. Palette entries with the unused bit 15 set are listed per
blob as `highBits`. The GammaLz tile streams re-encode byte for byte
(`tools/graphics/encode_gamma_lz.py`, without the outer header).

See [`battle.md`](../memory-map/battle.md) for the loader functions.
