# Controller input — memory map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout.

## `UpdateKeyInput` / `ResetKeyInput`, PROVEN

All code from `UpdateKeyInput` through `InitScrollGrid` (US
`0x080254A8`-`0x08025D28`, JP `0x08025504`-`0x08025D84`; same code, JP
`+0x5C`) is matched in `src/input/`, declared in `include/input.h`. See
[Cursor helpers](#cursor-helpers-proven) for the functions after the key
state.

| Name | US addr | JP addr | Called from |
|---|---|---|---|
| `UpdateKeyInput` | `0x080254A8` | `0x08025504` | Once per game-loop iteration, from `TickGameModeStack` (`0x0802C6B4`), immediately before dispatching the current game mode's update function. |
| `ResetKeyInput` | `0x080258F8` | `0x08025954` | `InitializeOverworld` and the two Select/Start consume-and-push-mode paths in `HandleOverworldPauseMenuInput (0x0802AEF8)` (see below). |

`UpdateKeyInput` maintains the frame's held/pressed/released key state:

```c
if (g_wInputDisabled != 0) {
    // clears g_wKeysHeld/g_wKeysHeldPrevious/g_wKeysPressed/g_wKeysReleased
    // and all four per-player arrays to 0, then returns
} else if ((g_dwGameModeFlags & 0x20) != 0) {
    // serial-link input: update both players' masks from the link
    // input buffer (g_awSerialKeysReceived, 0x03005A0C, see
    // docs/memory-map/serial.md), then select the local player's slot
    // (`GetSerialPlayerId`, US `0x0803FA94`, JP `0x0803FAFC`: the local
    // multiplayer terminal ID, see serial.md)
    ...
    g_wKeysHeldPrevious = g_awPlayerKeysHeldPrevious[localPlayer];
    g_wKeysHeld = g_awPlayerKeysHeld[localPlayer];
} else {
    // local input
    g_wKeysHeldPrevious = g_wKeysHeld;
    g_wKeysHeld = REG_KEYINPUT ^ 0x3FF;  // active-low -> active-high
    // ALSO mirrors into slot 0 of the per-player arrays -- easy to miss,
    // this is not dead code the link branch alone reaches
    g_awPlayerKeysHeldPrevious[0] = g_wKeysHeldPrevious;
    g_awPlayerKeysHeld[0] = g_wKeysHeld;
    g_awPlayerKeysPressed[0] = (g_wKeysHeld ^ g_wKeysHeldPrevious) & g_wKeysHeld;
    g_awPlayerKeysReleased[0] = (g_wKeysHeld ^ g_wKeysHeldPrevious) & g_wKeysHeldPrevious;
}
if (g_wInputDisabled == 0) {
    g_wKeysPressed  = g_wKeysHeld & ~g_wKeysHeldPrevious;
    g_wKeysReleased = g_wKeysHeldPrevious & ~g_wKeysHeld;
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
| `g_wInputDisabled` | `0x030034F4` | Nonzero forces `UpdateKeyInput` to clear all key state instead of reading input. Cleared by `EnableKeyInput` (US `0x08025954`, called from `InitInputSystem`) and set to 1 by `DisableKeyInput`; both also write the same value to both entries of `g_awPlayerInputDisabled_candidate`. |
| `g_awPlayerInputDisabled_candidate` | `0x03003506` | `u16[2]`, the per-player counterpart of `g_wInputDisabled` by position and by the two writers above. `DisableKeyInput` has no callers found, and no reader was found. |
| `g_awPlayerKeysHeld` | `0x030034F6` | `u16[2]`, per-player held-key masks, serial-link input path only. |
| `g_awPlayerKeysHeldPrevious` | `0x030034FA` | `u16[2]`, previous-frame counterpart of the above. |
| `g_awPlayerKeysPressed` | `0x030034FE` | `u16[2]`, per-player newly-pressed masks. |
| `g_awPlayerKeysReleased` | `0x03003502` | `u16[2]`, per-player newly-released masks. |

JP addresses (`ram_symbols.jp.inc`): every global on this page sits `0x60`
higher than its US address, from `g_wKeysHeld` (`0x0300354C`) through
`g_dwScrollGridVisibleRows` (`0x0300358C`), and `g_awSerialKeysReceived` is
`0x03005A6C`.

## Cursor helpers, PROVEN

**`StepCursorByKeys(pValue, min, max, wrap, keys, decrementKeys,
incrementKeys)`** steps `*pValue` down or up by one when `keys` has a
decrement or increment key, stopping at `min`/`max`, or wrapping to the
other end when `wrap` is nonzero. It returns 1 if `*pValue` changed. The six
variants pass one player's pressed or held keys and a fixed key pair:

| Function | Keys | Pair |
|---|---|---|
| `StepCursorUpDown` / `...UpDownHeld` | pressed / held | Up, Down |
| `StepCursorLeftRight` / `...LeftRightHeld` | pressed / held | Left, Right |
| `StepCursorShoulder` / `...ShoulderHeld` | pressed / held | L, R |

The ROM compiles `StepCursorByKeys` into every variant and the held
variants into the `StepScroll*` functions below, while also keeping each
out of line; `include/input_inline.h` reproduces this with `extern inline`
definitions. Only the generic `StepCursorByKeys`, the shoulder variants
and the scroll functions have no callers found.

**Scrolling list and grid.** `InitScrollList(rowCount)` and
`InitScrollGrid(selection, itemCount, columnCount, visibleRows)` set the
globals below; `StepScrollListSelection(visibleRows, wrap, player)`,
`StepScrollGridRow(wrap, player)` and `StepScrollGridColumn(wrap, player)`
move them with held keys and return the selected row or column. A list that
fits in its window moves only the cursor; a longer one keeps the cursor near
the middle and scrolls `g_dwScrollListTopRow`. That scrolling path tests Up
and treats every other case as Down, so with neither key held it steps down.
`StepScrollGridColumn` limits the column to the items in the current row,
and `StepScrollGridRow` pulls the column back when scrolling down onto a
partial last row. No callers were found for any of these, nor other code
referencing the globals.

| Symbol | US addr | Meaning |
|---|---|---|
| `g_dwScrollListRowCount` | `0x0300350C` | Rows in the list or grid. |
| `g_dwScrollListTopRow` | `0x03003510` | First visible row. |
| `g_dwScrollListCursorRow` | `0x03003514` | Cursor row within the window; the selected row is `TopRow + CursorRow`. |
| `g_dwScrollGridColumn` | `0x03003520` | Grid cursor column. |
| `g_dwScrollGridItemCount` | `0x03003524` | Grid item count. |
| `g_dwScrollGridColumnCount` | `0x03003528` | Items per grid row. |
| `g_dwScrollGridVisibleRows` | `0x0300352C` | Grid rows visible at once. |

**Others.** `DisableKeyInput` (uncalled) is `EnableKeyInput` with 1.
`GetDpadDirection` maps `g_wKeysHeld`'s D-pad bits through
`g_abDpadDirection` (US `0x08060E7C`, JP `0x08060E08`, `s8[16]`) to a
`Direction`, or `DirectionNone` for no key or opposing keys. Both callers
pass it with an object to `sub_08003FB8` and store that result in the
object's `bFacing`. `GetAnyPlayerKeysHeld`
and `GetAnyPlayerKeysPressed` OR together the low byte (A through Down) of
both players' masks; `ToggleFlag(p)` sets `*p = (*p == 0)`. The last three
have no callers found.

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
