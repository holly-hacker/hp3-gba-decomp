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

## Rain tile streams

40 streams follow the blob run, `0x089AD364`-`0x089AE030` (JP
`0x089AD194`-`0x089ADE60`), contiguous to the end (**PROVEN**). Each is a
u16 width (always 112), a u16 height (36 to 120) and a headerless GammaLz
stream of 4 bpp tiles: 32 streams of 1024 bytes and 8 of 288. Rendered as tile
sheets, the first 32 show short diagonal streaks and the last 8 small ring and
dot shapes, which read as rain and rain splashes (**UNCONFIRMED**: the tile
arrangement, palette and the use of the width and height are not known).

Two lists point at them (`g_RainStreakList_candidate` at `0x08053B18` with 32
entries, `g_RainSplashList_candidate` at `0x08053C20` with 8; JP
`0x08053A44` and `0x08053B4C`). Each is an 8-byte control block, then
entries `{stream, tag}` (tag 1 and 2 respectively). The block is what the
effect script copies from `EffectBgRecord::pControls`
(`g_aEffectBgRecords_candidate` at `0x080544D4`) into
`g_adwEffectBgControlOverride_candidate`; what reads the entries is not traced.

`just extract-tile-streams` and `just pack-tile-streams` handle them like the
blobs, with `tile-streams <start> <end> <dir> <name>` rows and
`data/tile_streams/`: one grayscale PNG tile sheet per stream (8 tiles per
row, color 0 transparent), named `RainStreak01`-`32` and `RainSplash01`-`08`,
and a `bank.json` with each stream's width, height and tile count.

## Other blob runs

The rest of the blobs outside `BgGraphics` (US `0x080BCEA0`, `0x08A30814`-`0x08E65D6C`;
JP the same bytes, 0xC4 to 0x201C lower) form 17 runs, each a bank
(`MenuCursor`, `OwlCare`, `CoolTrain`, ...) with its own
`data/graphic_blobs/<bank>/` directory. A run is a chain of blobs whose parsed
ends meet (**PROVEN**: every GammaLz stream's length matches its length field,
and all rebuild byte for byte); unrelated data separates the runs. They add
flags `0x19 0x00` (raw 4 bpp tiles), `0x99 0x01` and `0xF9 0x00`/`0x01` (8 bpp)
to the battle set, and one 128x132-tile map.

A blob with a `label` row at its address in the manifest takes that symbol
(`g_Foo` becomes PNG `Foo`, with `symbol` in `bank.json`); the others are
numbered `<Bank>001`... by position in the run.

Blobs without a palette (flags0 bit 0 clear: `0x78`, `0xF8`) draw with a palette
that is already loaded. Their PNGs show the colors of a blob or label that
`bank.json` records as `palette` (gray when none), and the packer ignores it.
The sources are set in `PALETTE_SOURCES` in `extract_graphic_blobs.py`; see
[`../memory-map/menu_screen.md`](../memory-map/menu_screen.md) for which are
established. Four blobs have more tiles than their images' distinct tiles: the tile
numbering is not the standard rebuild's. They list their tilemap cells'
tiles and flips as `layout` in `bank.json`, and every cell of a tile must keep
the same pixels. Blobs with flags `0x7A` carry a 16-color (32-byte) palette (flags0 bit 1)
instead of a 256-color one; the PNG shows it as colors 0-15. The `0xFF`
palette-data labels are not supported and stay raw.

`MainMenuTitles` (US only) holds the main menu's per-language title logos
(seven distinct 15x5-tile palette-less blobs, the entries of
`g_apMainMenuTitleGraphic`, whose first two entries are the same blob) and
`g_MainMenuBg2Graphic`, also palette-less. JP has one title blob, identical to
the first US one, and a `g_MainMenuBg2Graphic` that carries its own palette
(flags `0x79`), so it is its own bank, `MainMenuJp`, in a separate directory.
The title blob (`g_UnusedMainMenuTitleGraphic`) is unused in JP: its only
reference is the lone entry of a title table that no JP code reads. A halfword
tilemap with an odd cell count is followed by one zero cell (the 15x5 titles).

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
