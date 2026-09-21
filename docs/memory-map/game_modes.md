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

The per-frame dispatcher (`TickGameModeStack`, `0x0802C6B4`)
gates a transition on a single check
(`IsGameModeTransitionPending`, `0x0802C860`):
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
exactly) with an actual calculator, not by hand** (AGENTS.md hard rule
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

Full enum (71 values, `Startup`=1 through `ConfirmTradeScreen`=0x47) is in
`include/game_modes.h`, mirroring Ghidra's `GameMode` data type -- not
reproduced in full here since it covers every screen/cutscene in the
game, not just debug menus.

## Mode-transition shift

`TickGameModeStack` (`0x0802C6B4`, US, matched: `src/gamemode/tick_game_mode_stack.c`)
is the per-frame dispatcher. On a pending transition it shifts three
identical 0x24-byte `GameModeStackContext` blocks -- current
(`g_GameModeStackContext`, `0x03003EF4`), pending (`g_dwPendingGameMode`,
`0x03003F18`), previous (`g_PrevGameModeStackContext`, `0x03003F3C`) -- with two plain
struct assignments (`g_PrevGameModeStackContext = g_GameModeStackContext;
g_GameModeStackContext = g_dwPendingGameMode;`), confirmed to compile to the
real ROM's `ldmia`/`stmia` block copies. `g_dwTickCount` (`0x03003F60`,
right after the three blocks) increments once per call, before dispatch;
`UpdateObjectSpriteFrame` also reads/writes it as a per-tick generation
stamp for a shared VRAM tile allocation cache.

`GameModeStackContext`'s two scratch words (`dwModeScratchA` at
+0x14, `dwModeScratchB` at +0x20) are genuinely generic --
confirmed with real, unrelated per-mode uses: a confirm/cancel flag in
`OwlNameSelect` (0/1 on KEY_A/KEY_B), and a "just cancelled" marker in the
card-trade mode's own state machine (`CancelCardTradeOffer`). Not fixed
single-purpose fields, same as `dwModeState`/`dwModeTimer`/
`dwModeSubState`.

`TickGameModeStack` also pumps the link-cable comm packet
(`TickLinkCommIfActive_candidate`, `0x0803EF5C`) when a link session is
active (`g_dwGameModeFlags` bit `0x20`) -- see `link.md` for that subsystem.

`InitGameModeStack` (`0x0802C750`, matched: `src/gamemode/init_game_mode_stack.c`)
zeroes the current mode, seeds pending/previous from it, then pushes
`Startup` or `LanguageSelect` depending on `g_saveManager.header.bLanguageByte` bit `0x80`
(`flLanguageConfigured`, see `docs/formats/save.md`) -- language already
chosen skips straight to `Startup`.

Two small, previously-unlabeled functions sit between `InitGameModeStack`
and `PushGameMode` (found while bounding `InitGameModeStack`'s extent, not
yet matched): `GetCurrentGameMode_candidate` (`0x0802C7A8`, returns
`g_GameModeStackContext.dwCurrentGameMode`; no confirmed callers -- not
reached by any `bl` in the ROM) and `GetPendingGameMode_candidate`
(`0x0802C7B4`, returns `g_dwPendingGameMode.dwCurrentGameMode & ~0x80`;
called by `ExitCardTrade`/`ExitGameCubeLink`/`ExitInGameMenu`).

## Dispatch table

`g_pGameModeDispatchTable` (US `0x08065CBC`, extracted to
`src/gamemode/game_mode_dispatch_table.c`), 72 entries (`GameMode` 0-0x47;
index 0 unused/reserved, all three fields point at `HandleGameModeNoneNoOp`,
matched in `src/gamemode/handle_game_mode_none_noop.c` -- a no-op,
single `bx lr`).
Each entry is 3 function pointers, `pInitFn`/`pUpdateFn`/`pDestroyFn`:
`pInitFn` runs once right after the mode variable updates to the new mode,
`pUpdateFn` every frame, `pDestroyFn` once on the *old* mode right before the
mode variable updates (see `save.md`'s "Owl Care Kit" section for the
dispatcher call sites this was cross-checked against). All 216 slots (185
distinct functions) are still raw incbin, named in `regions.us.txt` via
`thumb-func` rows and referenced from the table by address only -- not
decompiled.

The three dispatchers (`DispatchGameModeInit`/`Update`/`Destroy`,
`0x0802C87C`/`0x0802C8A8`/`0x0802C8D0`, all matched in `src/gamemode/`)
index this table by `g_GameModeStackContext.dwCurrentGameMode`, call the
selected slot's function pointer if non-NULL, and are otherwise identical
except: `Init`/`Destroy` additionally call `ResetKeyInput` first, and
`Destroy` additionally requires `g_dwGameModeFlags` bit `0x1` clear.

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
