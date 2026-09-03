# Game mode stack

See [`../README.md`](../README.md) for the confidence-key legend.

`g_dwCurrentGameMode`/`g_dwPendingGameMode` (US `0x03003EF4`/`0x03003F18`)
drive a mode-stack dispatcher (`PushGameMode`/`PushGameMode_2`/`PushGameMode_3`,
`0x0802C7C4`/`0x0802C7E0`/`0x0802C800`) -- each mode is a value of the
`GameMode` enum (Ghidra data type, 4 bytes). Pushing a mode writes
`mode | 0x80` into `g_dwPendingGameMode` (the high bit marks it pending);
the main loop picks it up next frame. PROVEN: read directly from
`PushGameMode_3`'s disassembly (`str r4,[r5,#0]` where `r4 = mode | 0x80`,
`r5` a literal-pool load resolving to `0x03003F18`).

## Live debugging: force a mode transition

The per-frame dispatcher (`TickGameModeStack_candidate`, `0x0802C6B4`)
gates a transition on a single check
(`IsGameModeTransitionPending_candidate`, `0x0802C860`):
`g_dwCurrentGameMode != g_dwPendingGameMode`,
nothing else -- PROVEN by decompile, a sign-bit `(-(x)|x)>>31` idiom for
"not equal". **The `0x80` bit real code sets on every push is not
required** -- it just tags the write as consumed (cleared right after the
dispatcher fires) and plays no role in the trigger check. So writing the
plain mode value works, live-confirmed, and is simpler than reproducing
`mode | 0x80`:

```
w/1 0x03003F18 <mode>
```

**Compute any bitwise combination (e.g. if reproducing `mode | 0x80`
exactly) with an actual calculator, not by hand** (CLAUDE.md hard rule
4) -- a wrong hand computation of `mode | 0x80` lands on a different
mode's pending value entirely, not a malformed one, so a mistake here
fails silently rather than erroring.

Values for the debug-menu modes (`GameMode` enum, US ROM):

| Mode | `mode` |
|---|---|
| `DebugMenuMain` | `0x19` |
| `DebugMenuMapSelect` | `0x1F` |
| `DebugMenuLevelAndQuestSelect` | `0x20` |
| `DebugMenuSoundTest` | `0x21` |
| `DebugMenuCollectorCards` | `0x22` |
| `DebugMenuPortraits` | `0x23` |
| `DebugMenuCharacterSelect` | `0x2A` |

Full enum (71 values, `Startup`=1 through `CreditsAgain`=0x47) is in
`include/game_modes.h`, mirroring Ghidra's `GameMode` data type -- not
reproduced in full here since it covers every screen/cutscene in the
game, not just debug menus.

## Dispatch table

`g_pGameModeDispatchTable` (US `0x08065CBC`, extracted to
`src/data/game_mode_dispatch_table.c`), 72 entries (`GameMode` 0-0x47;
index 0 unused/reserved, all three fields point at `HandleGameModeNoneNoOp`,
matched in `src/game_modes/handle_game_mode_none_noop.c` -- a no-op,
single `bx lr`).
Each entry is 3 function pointers, `pInitFn`/`pUpdateFn`/`pDestroyFn`:
`pInitFn` runs once right after the mode variable updates to the new mode,
`pUpdateFn` every frame, `pDestroyFn` once on the *old* mode right before the
mode variable updates (see `save.md`'s "Owl Care Kit" section for the
dispatcher call sites this was cross-checked against). All 216 slots (185
distinct functions) are still raw incbin, named in `regions.us.txt` via
`thumb-func` rows and referenced from the table by address only -- not
decompiled.

`pDestroyFn`'s functions were previously misnamed `DrawXxx` in Ghidra (a
stale guess from before this dispatch timing was established) and have been
renamed `ExitXxx` to match; spot-checked `ExitStartup`, which calls the same
palette-teardown primitive `ExitBattle`'s cleanup path calls, not anything
drawing-related.

## Not yet located

- Whether `DebugMenuMain` is reachable/meaningful from every game state,
  or only from specific ones (e.g. title screen) -- untested.
- JP addresses for `g_dwPendingGameMode`/`g_dwCurrentGameMode`, and the JP
  address of `g_pGameModeDispatchTable`.
