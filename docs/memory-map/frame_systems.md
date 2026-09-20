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
- **`TickOverworldBeforeObjects_candidate`**: three calls. `TickCameraFocus_candidate`
  (`0x0800A03C`, JP `0x0800A03C`) runs slot 0's camera focus and any scripted camera
  effect. `UpdateOverworldCamera_candidate` (`0x0803DA4C`, JP `0x0803DAB4`) turns the
  focus point into `g_CameraPosition_candidate` (focus minus the half screen, clamped to
  the room) and loads BG tiles on demand as it crosses tile boundaries.
  `TickRoomTileAnimations_candidate` (`0x08020228`, JP `0x08020210`) steps the room's
  animated tiles: 8-byte entries `{set, step, delay, flags, x, y}` at `0x03002F24`
  (count at `0x03002F28`) added by `AddRoomTileAnimation_candidate` (`0x080201C8`, JP
  `0x080201B0`). When an entry's delay hits 0, `0x08020278` copies the frame's tiles
  (frame lists come from the sets at `0x08060400`; delay `0xFF` loops, `0xFE` halts) to
  the entry's tile position on the BG layers in the frame's mask.
  `FindRoomTileAnimation_candidate` (`0x08020504`, JP `0x080204EC`) looks an entry up by
  tile; room object capture/restore saves and restores its state that way, and
  `SpawnRoomTileAnimationObject_candidate` (`0x08020490`, JP `0x08020478`) creates the
  room object that owns one.

## Camera focus (`TickCameraFocus_candidate`), STRUCTURAL MATCH

Two slots (the control slots), all three arrays adjacent in IWRAM:

| Array | Addr | Layout |
|---|---|---|
| `g_aCameraEffects_candidate` | `0x03002090` | `CameraEffect`, `0x2C` bytes |
| `g_aCameraFocusSlots` | `0x030020E8` | `CameraFocusSlot`, `0x38` bytes: focus `nX/nY` (16.16), latched copy, `pTarget`, `wPinned` |
| `g_aCameraFollowOffsets` | `0x03002158` | per-slot `(X, Y)` offset set by `SetCameraFollowTarget_candidate` |

The focus follows `pTarget` unless `wPinned` is set. `CameraEffect.bState` selects a
scripted effect started by room script opcodes `0x10` and `0x12`:

- **1, pan**: `MoveCameraFocusToward_candidate` (`0x0800A1F0`) steps the focus toward
  the target by `nStep` along the angle and returns 8 on arrival. Until `wCounter`
  reaches 0 the focus just holds on the target. On arrival, if the target is the
  controlled object the effect ends and its velocity and `bActionSubState` are
  restored. Once, `RespawnRowAndRunChain_candidate(bRespawnRow, bChainRow)` runs, and a
  pending script yield (`dwResumeScript`) resumes through
  `ResumeRoomSwitchStateChain_candidate`. Opcode `0x10` freezes the controlled object
  (velocity saved and zeroed) while the pan runs.
- **3, shake**: the focus follows the target with a `±nStep` offset on Y (vertical) every other frame for
  `dwFramesLeft` frames (forever when `dwRunForever` is set). At the end it runs the
  row/chain and calls `sub_0803FE98`, an unidentified wrapper around `0x08049E50`.
- **0, idle**: only the follow behavior.

Whether state 3 is visibly a shake in play, and what `sub_0803FE98` does, are
UNCONFIRMED.

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
