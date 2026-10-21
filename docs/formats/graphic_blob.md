# Graphic blobs

A graphic blob is a self-contained BG graphic: an optional palette, a
tilemap and tile data in one byte string, read by `LoadGraphicBlobTiles`. The
flags are listed in `tools/graphic_blob/blobs.py`. A GammaLz tile stream in a
blob has no outer resource header, so the codec header comes right after the
length.

## Contents

- **Battle backgrounds** (`g_aBattleBackgroundPairs`): 14 floor/wall pairs
  (stone, tile, carpet, grass, sand and wood floors; castle, library,
  clock-hall and forest walls). Floors are 32x32 byte-cell maps with GammaLz
  8 bpp tiles, and walls are 32x9 halfword-cell maps with raw 4 bpp tiles.
- **Battle effect backgrounds** (`g_aEffectBgRecords_candidate`): 165
  wall-type blobs after the battle backgrounds in `BgGraphics`. Seven are
  single screens (`BgGraphic001`-`007`), and the rest are the frames of
  five animated backgrounds (`BattleEffectBg1`-`5`: bursts, streaks and
  number grids).
- **Rain tile streams** (`RainTiles`): 40 streams after the blob run. Each
  is a `u16` width (always 112), a `u16` height and a headerless GammaLz
  stream of 4 bpp tiles. `g_RainStreakList_candidate` (32 streams of diagonal
  streaks) and `g_RainSplashList_candidate` (8 streams of rings and dots)
  hand them to `RegisterBgTileAnimation`. Reading them as rain and splashes
  is **UNCONFIRMED**, and so is the tile arrangement.
- 17 other runs elsewhere, one per feature bank (`MenuCursor`, `OwlCare`,
  `CoolTrain`, ...).

## Extraction

A `graphic-blobs` run (see [`graphics.md`](graphics.md) "Graphics build
format") holds one indexed PNG per blob. The rebuild rules (tile order,
flip matching, palette-less blobs) are in `blobs.py`, and all blobs rebuild
byte for byte. Other details are kept per blob in its settings:

- Four blobs have more tiles than their image's distinct tiles. They list
  each cell's tile and flips as `layout`.
- Three floor blobs have 58 or 69 tiles after the last tile the tilemap
  uses. These go in `<name>.unused.png`.
- Palette entries with the unused bit 15 set are listed as `highBits`.
- A halfword tilemap with an odd cell count is followed by one zero cell.
- Blobs with the `0xFF` palette-data flags are not supported and stay raw.

The main menu's title logos are US-only (`MainMenuTitles`, `menus/us`). JP
has one title blob, the same as the first US one. Its only reference is a
title table that no JP code reads.
