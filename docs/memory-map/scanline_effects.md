# Scanline effects (VCount-interrupt callback list) — memory map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout. Addresses are US.
JP has not been matched.

## Mechanism, PROVEN

A small engine runs game-supplied callbacks at chosen scanlines through the
VCount interrupt (IE bit 2, `DISPSTAT` bit 5 and bits 8-15). State lives in IWRAM:

- `g_ScanlineEffectState` (`0x03005E20`): `+0` pending flag (`u32`, 1 = a staged
  table waits to be committed), `+4` active entry index (`u32`), `+8` the live
  table, 19 entries of 0x10 bytes (`0x130` bytes).
- `g_ScanlineEffectStaging` (`0x03005F58`, = state `+0x138`): a same-sized staging
  table. Callers fill it; `CommitScanlineEffects` copies it over the live table.

Entry layout (both tables; ROM tables handed to `QueueScanlineEffectTable` use it too):

| Offset | Type | Meaning |
|---|---|---|
| `0x00` | `u16` | VCOUNT line the callback fires on (`0xFFFF` = unused) |
| `0x02` | `u16` | caller-defined (written by `QueueScanlineEffectEntry`) |
| `0x04` | `u32` | first payload word; the callback receives its address |
| `0x08` | `u32` | second payload word; the callback receives its address |
| `0x0C` | `void (*)(u32 *, u32 *)` | callback; a null pointer terminates the list |

`ScanlineEffectVCountCallback` (`0x08045318`) is installed with
`SetVCountCallback` and reached through `HandleVCountInterrupt` (`0x080262BC`,
which calls `g_pVBlankState->+8`). Each fire it calls the active entry's callback,
advances the index (wrapping to 0 when the next entry's callback is null), then
programs `DISPSTAT`'s VCOUNT-compare byte with the next entry's line. Lines
therefore need to be ascending; the battle tables at `0x08053B08` (e.g. `0x080539B8`:
lines 0, 88, 112, 160) end on line 160, the first vblank line, before the wrap.

| Name | Addr | Behavior |
|---|---|---|
| `InitScanlineEffects` | `0x08045094` | Called once from `AgbMain`: clears the index, `ClearScanlineEffectStaging`, queues the default table (`0x0806C2F0`, one entry with line 0 and `ScanlineEffectNop`), copies staging to live, installs the VCount callback, `StartScanlineEffects`. |
| `QueueScanlineEffectTable` | `0x080450D4` | `(entries, count)`: waits for the pending flag to clear (one vblank per spin), clears staging, copies `count * 0x10` bytes into it, sets the pending flag. |
| `QueueScanlineEffectEntry` | `0x08045210` | `(index, line, param, callback)`: waits for idle, then overwrites staging entry `index`'s line, `+2` word and callback and sets the pending flag. Its one caller (`UpdateDialogueBox`) passes callback `0x0801FC59`. |
| `CommitScanlineEffects` | `0x08045260` | Called from `HandleVBlankInterrupt`: if the pending flag is set, copies staging over the live table and clears the flag and the index. |
| `StartScanlineEffects` | `0x0804528C` | Resets the index and enables the VCount interrupt at entry 0's line (`EnableVCountInterrupt`, `0x080261F8`). |
| `StopScanlineEffects` | `0x080452A8` | Clears IE bit 2, acknowledges IF bit 2, clears `DISPSTAT` bit 5. |
| `ClearScanlineEffects` | `0x080452D4` | Queues the default table and waits one vblank. |
| `IsScanlineEffectQueueIdle` | `0x080452EC` | 1 when the pending flag is clear. |
| `GetScanlineEffectLine` | `0x08045304` | `(index)` -> live entry's line. |
| `ClearScanlineEffectStaging` | `0x08045374` | Sets every staging entry's line to `0xFFFF` and zeroes the rest. |

`0x0804A2C8` (`_call_via_r2`) is the `bx r2` veneer the callback dispatch uses.

## Users, PROVEN (call sites)

- `QueueScanlineEffectTable` + `StartScanlineEffects` (+ `IsScanlineEffectQueueIdle`
  spin): `InitializeLoadingScreen`, `InitBattleBackground_candidate`,
  `InitializeDialogue`, `InitializeLupinPotionCutscene`, `sub_0802D674`; the table
  alone from `sub_08008E88`, `sub_08012A00`, `sub_08012B40`, `sub_08018CF8`.
- Battle script op `0x80` (`ShowCannedDialogBlock`, handler `0x0801A208`) queues one
  of the ROM tables at `0x08053B08`; see
  [`../formats/battle_scripts.md`](../formats/battle_scripts.md).
- `ClearScanlineEffects`: `ExitLoadingScreen`, `ExitDialogue`, `ExitMinigameMenu`,
  `sub_0802D6B8`. `StopScanlineEffects`: the debug-menu, loading-screen, dialogue,
  Lupin-potion, overworld and Wizard Cracker Pop-It exit/init paths.

## UNCONFIRMED

What the individual callbacks draw (the one decoded table entry, line 159 with
callback `0x0801FC59`, busy-waits for HBlank via `DISPSTAT` and rewrites video
registers, so the mechanism reads as a per-scanline video-register effect) and the
role of the `+2` halfword. The name `ShowCannedDialogBlock` should be revisited:
its tables hold entries of this format.
