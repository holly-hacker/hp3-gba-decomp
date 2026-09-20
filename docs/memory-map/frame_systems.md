# Per-frame subsystem tick — memory map

See [`../README.md`](../README.md) for the confidence-key legend. Addresses are US.

## `TickFrameSystems` (`0x0802C820`), PROVEN

Called once per frame from `TickGameModeStack` after the game mode's update
function. Calls, in order:

| Call | Addr | Runs when |
|---|---|---|
| `TickOverworldBeforeObjects_candidate` | `0x0802B0DC` | current game mode (`0x03003EF4`) is 8 (overworld) |
| `TickActiveObjects` | `0x080015B8` | always |
| `TickParticleEmitters` | `0x08031748` | always |
| `TickBgLayers_candidate` | `0x08006EF4` | always |
| `TickScreenWindows_candidate` | `0x08045970` | always |
| `TickPaletteAnimations_candidate` | `0x0800D2F4` | always |
| `TickBgTileAnimations_candidate` | `0x0800A610` | always |
| `HideUnusedOamEntries` | `0x08030184` | always |
| `HandleOverworldPauseMenuInput` | `0x0802AEF8` | game mode is 8 |

## Callees, STRUCTURAL MATCH (roles read from the code; names carry `_candidate`)

- **`TickBgLayers_candidate`**: walks 4 BG layer records (`0x6C` bytes at
  `0x03001E84`, the same array `SetBgPriority` writes through). Flag bits at `+0x18`:
  `1` scroll tween toward `+0x34/+0x38` over `+0x3C` frames (or `0x0802BF8C` when
  the duration is 0), `8` sine wobble (`0x08007228`, table `0x0806589C`), `4`
  ping-pong zoom, `2` rotation, `0x4000` matrix dirty. A dirty matrix is rebuilt
  into the BG affine parameters and reference point (`0x7800`/`0x5000` centre
  constants).
- **`TickScreenWindows_candidate`**: two hardware-window records (`0x3C` bytes at
  `0x03006228`, two rects each) tweened or drifted per frame. `sub_08045988`
  writes the rects to `WINxH`/`WINxV` (`0x04000040`+) at vblank; the setters are
  `SetScreenWindowRect_candidate` and `SetScreenWindowLayers_candidate`.
- **`TickPaletteAnimations_candidate`**: 12 frame-cycling slots (`0x8` bytes at
  `0x03002280`, `0x0800D7E8`) and up to 12 blend/fade slots (`0x14` bytes at
  `0x030022F8`, `0x0800D9D4`, per-channel 5-bit RGB interpolation). Both mark a
  pending flag that the palette flush DMA consumes; see
  [`../formats/graphics.md`](../formats/graphics.md).
- **`TickBgTileAnimations_candidate`**: up to `0x03002168` entries of `0x10` bytes at
  `0x0300216C`; steps a frame index and counter, then re-uploads the tiles with
  `0x08007F20` (a copy/RLE/LZ77 VRAM loader chosen by header bits) to the VRAM
  address in `0x030021AC[i]`.
- **`TickOverworldBeforeObjects_candidate`**: three calls. `TickQueuedObjectMove_candidate`
  (`0x0800A03C`, JP `0x0800A03C`) runs slot 0's `g_aQueuedObjectMoves` state machine and,
  on completion, its follow-up room chain. `UpdateOverworldCamera_candidate`
  (`0x0803DA4C`, JP `0x0803DAB4`) writes `g_CameraPosition_candidate` from the followed
  object and loads BG tiles on demand as it crosses tile boundaries.
  `TickRoomTileAnimations_candidate` (`0x08020228`, JP `0x08020210`) counts down a list
  of 8-byte entries that write room BG tiles when they expire.

## `HandleOverworldPauseMenuInput` (`0x0802AEF8`, JP `0x0802AF54`), PROVEN

Runs last in the overworld frame. It first calls `HandleWanderingMonsterTouch`, then
opens a menu only when every gate passes: the controlled object's `bActionSubState`
is not 5, `g_dwRoomChainRanThisFrame_candidate` (`0x03001DF0`) is clear, no game mode
transition is pending, the slot's queued object move is not active (`bState != 1`),
`g_dwGameModeFlags & 0x80000811` is clear, the player object is not
`ObjectFlagAnimPaused`, and its `bActionState` is `0x21`. Then:

- Start (`0x8` in `g_wKeysPressed`) pushes `InGameMenu` (`0x0A`); Select (`0x4`)
  pushes `Options` (`0x05`).
- While `g_dwPauseMenuLocked` is set, either key only plays sound 3.
- Otherwise, when `g_dwPauseMenuCooldown` is 0: consume the key, zero the player's
  velocity, set the cooldown to 4, play sound 1, push the mode and set `g_bUnk03005E18`.

`g_dwRoomChainRanThisFrame_candidate` is set to 1 by `RespawnRowAndRunChain_candidate`
(and `sub_08005D30`) around a room chain and cleared unconditionally at the end of
this function every frame. `g_bUnk03005E18` is also set to 1 on entry to
`RestoreRoomObjectState` and cleared on exit; no reader was found.

## UNCONFIRMED

The exact in-game effects each tick drives (which BG layers wobble, which windows
are used where) and the meaning of the entry fields not listed above.
