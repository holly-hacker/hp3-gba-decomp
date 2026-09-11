# Controller input — memory map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout.

## `UpdateKeyInput` / `ResetKeyInput`, PROVEN

Named in `functions.us.cfg`/`functions.jp.cfg`; their bytes remain in
raw `.incbin` regions.
Read directly from `full_disasm.s` for both versions; JP required adding a
`functions.jp.cfg` seed for `UpdateKeyInput` since `gbadisasm` did not
auto-detect its boundary there (`just disasm-compare` confirmed byte-exact
for both versions after seeding).

| Name | US addr | JP addr | Called from |
|---|---|---|---|
| `UpdateKeyInput` | `0x080254A8` | `0x08025504` | Once per game-loop iteration, from `TickGameModeStack` (`0x0802C6B4`), immediately before dispatching the current game mode's update function. |
| `ResetKeyInput` | `0x080258F8` | `0x08025954` | `InitializeOverworld` and the two Select/Start consume-and-push-mode paths in `HandleOverworldPauseMenuInput (0x0802AEF8)` (see below). |

`UpdateKeyInput` maintains the frame's held/pressed/released key state:

```c
if (g_wInputDisabled == 0) {
    if ((g_dwGameModeFlags & 0x20) == 0) {
        // local input
        g_wKeysHeldPrevious = g_wKeysHeld;
        g_wKeysHeld = KEYINPUT ^ 0x3FF;  // active-low -> active-high
    } else {
        // serial-link input: update both players' masks from the link
        // input buffer (0x03005A0C, see docs/memory-map/link.md), then
        // select the local player's slot (index from FUN_0803FA94,
        // which returns gLinkCtxPlayerCount's local-player index)
        ...
        g_wKeysHeldPrevious = g_awPlayerKeysHeldPrevious[localPlayer];
        g_wKeysHeld = g_awPlayerKeysHeld[localPlayer];
    }
    g_wKeysPressed  = g_wKeysHeld & ~g_wKeysHeldPrevious;
    g_wKeysReleased = g_wKeysHeldPrevious & ~g_wKeysHeld;
} else {
    // clears g_wKeysHeld/g_wKeysHeldPrevious/g_wKeysPressed/g_wKeysReleased
    // and all four per-player arrays to 0
}
```

`ResetKeyInput` unconditionally clears the same four scalars and the four
per-player arrays (12 halfwords total) -- used to discard whatever edge is
pending when entering a new context (overworld init) or after a menu
consumes a Select/Start press, so it doesn't leak into the next frame.

## Globals

All `u16`, standard GBA `KEYINPUT` bit order (active-high once XORed, as
`UpdateKeyInput` does):

| Bit | Mask | Button |
|---:|---:|---|
| 0 | `0x001` | A |
| 1 | `0x002` | B |
| 2 | `0x004` | Select |
| 3 | `0x008` | Start |
| 4 | `0x010` | Right |
| 5 | `0x020` | Left |
| 6 | `0x040` | Up |
| 7 | `0x080` | Down |
| 8 | `0x100` | R |
| 9 | `0x200` | L |

| Symbol | US addr | Meaning |
|---|---|---|
| `g_wKeysHeld` | `0x030034EC` | Current held-key mask. Also folded into `Mt19937AutoSeed`'s seed as a cheap entropy source (see `docs/memory-map/rng.md`) -- that's not what the address is *for*. |
| `g_wKeysHeldPrevious` | `0x030034EE` | Held-key mask from the previous frame's update. |
| `g_wKeysPressed` | `0x030034F0` | Keys newly pressed this frame: `currentHeld & ~previousHeld`. By far the most-read of these globals (144 cross-references) -- menu, battle, cutscene, and minigame update functions across the ROM test it for edge-triggered button presses. Some consumers clear it to `0` after handling a press, consuming the event for the rest of the frame (e.g. `HandleOverworldPauseMenuInput (0x0802AEF8)`'s Select/Start dispatch). |
| `g_wKeysReleased` | `0x030034F2` | Keys newly released this frame: `previousHeld & ~currentHeld`. No confirmed readers yet. |
| `g_wInputDisabled` | `0x030034F4` | Nonzero forces `UpdateKeyInput` to clear all key state instead of reading input. Set/cleared by two small helper functions at `0x08025954`/`0x08025978` (US) that also fill a small unrelated block at `0x030034D0`-`0x030034D7` -- not yet identified as one of the globals in this table (four bytes, purpose unconfirmed). |
| `g_awPlayerKeysHeld` | `0x030034F6` | `u16[2]`, per-player held-key masks, serial-link input path only. |
| `g_awPlayerKeysHeldPrevious` | `0x030034FA` | `u16[2]`, previous-frame counterpart of the above. |
| `g_awPlayerKeysPressed` | `0x030034FE` | `u16[2]`, per-player newly-pressed masks. |
| `g_awPlayerKeysReleased` | `0x03003502` | `u16[2]`, per-player newly-released masks. |

JP addresses for the per-player/edge globals are not yet mapped (no matched
C source currently reads them on the JP side); `g_wKeysHeld` is the one
exception, already named in `ram_symbols.jp.inc` at `0x0300354C` for the
shared `Mt19937AutoSeed` source.

## Known readers

- `TickBattleMenuInput` (`0x080101D0`) -- battle top-menu cursor: `0x10`
  (Right) advances the list index by `+1`, `0x20` (Left) moves it back by
  `-1`, both wrapping via `0x08012E38`. See `docs/memory-map/battle-ui.md`.
- `TickBattleTurnStateMachine` state 5 (message-wait) -- `0x01` (A) fast-
  forwards the 30-tick wait. See `docs/memory-map/battle.md`.
- `UpdateFolioBrutiGridCursor` (`0x08036BB8`) -- `0x10`/`0x20`/`0x40`/`0x80`
  (Right/Left/Up/Down) move the bestiary grid cursor, with a one-cell skip
  at the grid's dead final slot. See `docs/formats/folio_bruti.md`.
- `HandleOverworldPauseMenuInput (0x0802AEF8)` -- overworld pause-menu entry: `0x08` (Start) opens
  `InGameMenu`, `0x04` (Select) opens `Options`, each consuming the press
  (`g_wKeysPressed = 0`) before pushing the mode.
- `UpdateMainMenu` (`0x08043646`-area) -- `0x08` (Start) advances the
  title-screen state machine past "Press START".
