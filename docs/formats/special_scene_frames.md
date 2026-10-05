# Special scene tile frames

A pool of 128 raw 4 bpp tile frames for the BG tile animation system
(`TickBgTileAnimations_candidate`, `0x0800A610`), used by
`RoomScriptOpPlaySpecialSceneEffect`. See [`graphic_blob.md`](graphic_blob.md)
for the neighbouring blob formats.

## Layout (US `0x081B2E98`-`0x081DB29C`; JP `0x081B2CC8`-`0x081DB0CC`)

| Part | Size | Contents |
|---|---|---|
| `gTrainWindowNightPalette` | `0x204` | flags `0xA1 0x00`, 512 bytes of colors, a zero halfword; `LoadEmbeddedPalette_candidate` reads the colors |
| 128 frames | `0x504` each | `u16 kind` (always `0x0010`), `u16 size` (always `0x0500`), then `size` bytes of 4 bpp tiles |

`0x204 + 128 * 0x504` is exactly the 164,868-byte span (**PROVEN**). The `SpecialSceneFrames`
graphics group claims the whole span: the palette as a one-entry 8 bpp
`image-bank` run (`TrainWindowNight`), then the frames as a `tile-frames` run. A frame
holds 40 tiles. They are not an 8x5 image: they are the tile numbers 0-39 of the
room's layer 0 (palette bank 15 in rooms 5, 6 and 7, **PROVEN** from the layer
files), so the room's block map arranges them into the four window views. The
tick function copies each tile of the current frame into the BG's character data
through a tile-slot lookup (`sub_0803E9E0`); the BG control word is
`g_dwSpecialSceneBgControl` (`0x1D03`: priority 3, character block 0, screen
block 29, 4 bpp; STRUCTURAL MATCH).

## Animation tables (STRUCTURAL MATCH, from the tick function)

`g_aSpecialSceneBg2`, `g_aSpecialSceneBg0` and `g_aSpecialSceneBg1`
(`0x08063074`, `0x0806347C`, `0x08063884`) are animation resources:
`u8 flags` (3), `u8 entry count` (`0x80`), `u16`, `u32 buffer size` (`0x500`),
then entries `{frame pointer, duration}` at offset 8. Each tick advances an
entry's duration counter; on rollover the next frame's tile data (frame + 4,
`size` bytes) is copied by `sub_08007F20` into a buffer allocated at `0x500`
bytes. The three resources list the same 128 frames in the same order.
Where the buffer ends up in VRAM and the palette bank are not traced.

## Use (STRUCTURAL MATCH)

The frames are the scenery outside the Hogwarts Express windows: rooms 5, 6 and 7
(baggage, passenger and buffet cars) set `pBgControlOverrideA` to
`g_aSpecialSceneBg2`. The three resources differ only in the per-entry durations
(ticks per frame; a duration of 0 holds the current frame, from the tick function):

| Resource | Mode of `PlaySpecialSceneEffect` | Durations | Where it is selected |
|---|---|---|---|
| `g_aSpecialSceneBg2` | 2 | 1 for all 128 | default moving train; mode 2 is run after the fight in `Room06V3Chain20` |
| `g_aSpecialSceneBg1` | 1 | 2 x16, 4 x11, 8 x9, then 0 | train slowing to a stop; `Room06V1Chain7` ("Why's the train stopped?") |
| `g_aSpecialSceneBg0` | 0 | 0 for all 128 | stopped; no script sets mode 0, but entering rooms 5-7 with `g_abQuestEventState[0x1d] == 1` applies it |

Mode 3 loads `gTrainWindowNightPalette` (the alternate presentation palette for room 6) instead of
selecting an animation. The two palettes (the room's own and this one) are
probably the day and night looks of the scenery, switched when the Dementors
appear (**UNCONFIRMED**; the script that runs mode 3 is `Room06V3Chain29`).

## Viewing

The frame PNGs are raw tile sheets, not the picture. To see the scenery, draw a
room's layer 0 (rooms 5-7, `data/graphics/rooms/`) with tiles 0-39 taken from one
frame and palette bank 15 of the room's palette A (day) or of
`gTrainWindowNightPalette` (night); stepping through the 128 frames animates it.
This is a render for inspection, not something the build or an extractor makes.

## Compressed frames

Two more frame pools, contiguous at US `0x08D48D74`-`0x08D56A68`, use frame kinds
`0x70` and `0xF0`. Kind bits 5-6 = 3 mean the size is the length of a GammaLz
stream, which decodes to the tiles (the draw code calls the codec through
`0x030028D0`); kind bit 7 marks 8 bpp tiles (**PROVEN** for `0xF0`: the BG
control word `g_dwDivinationTeaBg2Control` has the 256-color bit set and the
frames decode to 64 tiles of 64 bytes, a 64x64 texture of three color numbers).

| Bank | Frames | Tiles each | Resource (buffer size) | Used by |
|---|---|---|---|---|
| `ServePumpkinJuiceFrames` | 16 | 60 (4 bpp) | `g_ServePumpkinJuiceTable` `0x08069328` (`0x780`) | `InitializeUnusedServePumpkinJuiceMinigame` |
| `DivinationTeaFrames` | 64 | 64 (8 bpp) | `g_DivinationTeaTable` `0x0806BB70` (`0x1000`) | `InitializeDivinationTeaMinigame` |

Their resources have the layout above (flags `2`, `0x10` and `0x40` entries). The
frames are consecutive: each starts where the previous stream ends.

## Extraction

A `tile-frames` run, `SpecialSceneFrames` (see [`graphics.md`](graphics.md)
"Graphics build format"), covers the 128 frames (`0x081B309C`-`0x081DB29C`;
the palette stays raw) as one grayscale PNG tile sheet per frame (8 tiles per
row, color 0 transparent, `TrainWindowSceneryFrame001`-`128`); its `frames`
settings list each frame's kind and tile count. All frames rebuild byte for
byte.
