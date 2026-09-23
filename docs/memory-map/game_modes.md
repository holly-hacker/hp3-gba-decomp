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

`g_pGameModeDispatchTable` (US `0x08065CBC`, JP `0x08065C48`, extracted to
`src/gamemode/game_mode_dispatch_table.c`), 72 entries (`GameMode` 0-0x47;
index 0 unused/reserved, all three fields point at `HandleGameModeNoneNoOp`,
matched in `src/gamemode/handle_game_mode_none_noop.c` -- a no-op,
single `bx lr`).
Each entry is 3 function pointers, `pInitFn`/`pUpdateFn`/`pDestroyFn`:
`pInitFn` runs once right after the mode variable updates to the new mode,
`pUpdateFn` every frame, `pDestroyFn` once on the *old* mode right before the
mode variable updates (see `save.md`'s "Owl Care Kit" section for the
dispatcher call sites this was cross-checked against).

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

## Status/Equip (0x0C-0x0F)

PROVEN from US decompiles and ROM tables.

- `StatusEquipCharacterSelect` (0x0C) and
  `StatusEquipCharacterSelectLastCursor` (0x0D) share
  `UpdateStatusEquipCharacterSelect`. A pushes `g_StatusEquipNextMode`,
  B pushes `g_StatusEquipReturnMode`, both set by the caller:
  - Pause menu row 0 (`g_aInGameMenuEntries[0]`, text 0x530 "Status/Equip"):
    next `StatusEquipSlotSelect`, return `InGameMenu`/`InGameMenuFadeIn`.
  - `UpdateItemsItemSelect`, for items with `dwUnk20` bit 2: next
    `QuantitySelectScreen` (whose A leads to `ItemUseScreen`), return
    `ItemsItemSelect`. The header shows text 0x531 "Items" instead.

  0x0C places the cursor on Harry (or the first present member); 0x0D
  restores it to the last chosen member and is entered by B from 0x0E.
  The three slots show Hermione, Harry and Ron, left to right
  (`StatusEquipSlotToCharacter`/`StatusEquipCharacterToSlot`); left/right
  wrap and skip absent members. A stores the chosen `FighterType` (0 Harry,
  1 Hermione, 2 Ron; names at `0x0806944C`) in `g_dwStatusEquipCharacter`,
  which 0x0E, 0x0F and `ItemUseScreen` read.
- `StatusEquipSlotSelect` (0x0E): the chosen member's stats panel
  (`DrawStatusEquipStatsPanel`) and a 2x3 grid of equipment slots,
  `g_aStatusEquipSlots` (`0x0806B2FC`, 6 `StatusEquipSlot` entries of 16
  bytes: x/y (`s16` each), slot type (`u32`, 0-5), slot name text id
  (`0x5A0 + type`), then up/down/left/right neighbour indices). The slot
  items fade in over 8 frames. A goes to 0x0F when `sub_0803A678` accepts
  the slot (otherwise sound 3 plays), B to 0x0D.
- `StatusEquipItemSelect` (0x0F): lists items for the chosen slot type
  (text `0x3F7 + type`: Change Belt/Charm/Gloves/Boots/Hat/Cloak) with a
  Def/Agi/M.Def comparison (`DrawEquipItemStatComparison`); A equips,
  A or B returns to 0x0E. It overrides BG palette colors 4-6 while open
  and restores them on exit.

Screen state lives in `g_StatusEquipCharacterSelect`,
`g_StatusEquipSlotSelect` and `g_StatusEquipItemSelect`; each holds the
mode it pushes after its fade-out. Types are in `include/status_equip.h`;
the init/update/exit handlers are matched in
`src/gamemode/modes/status_equip/` for both versions.

JP handlers (PROVEN: taken from JP's dispatch table at `0x08065C48` and
built byte-identically from the US source; the Status/Equip RAM globals
sit +0x60 from US):
0x0C/0x0D update `0x080357A8`, init `0x08035D4C`/`0x08035D64`, exit
`0x08035DA8`; 0x0E `0x0803A50C`/`0x08039E2C`/`0x0803A584`; 0x0F
`0x080361F0`/`0x08036258`/`0x080368D4` (init/update/exit).

## Items (0x10-0x12)

PROVEN from US decompiles, ROM tables and dialog text.

- `ItemsSectionSelect` (0x10): pause menu row "Items" (text 0x531). A list
  menu (`g_ItemsSectionMenuDefinition`) whose rows pick a list filter from
  `g_aItemsSectionFilters` (`0x0806B1B4`: 0xA all non-equipment items,
  6 potions, 8 ingredients; see `docs/formats/items.md`). A goes to 0x11,
  B to `InGameMenuFadeIn`. The row is kept in `g_bItemsSectionCursor`.
- `ItemsItemSelect` (0x11): the filtered item list, with the description
  of the item under the cursor ("Restores @1 Stamina/Magic Points." or
  "You can't use this item now..."). An empty list shows text 0x667 and
  any of A/B returns to 0x10. A on a Stamina/Magic item (item field `+0x24`
  1 or 2) stores it in `g_dwItemUseItem`; items with `dwUnk20` bit 2 go
  through `StatusEquipCharacterSelect` and `QuantitySelectScreen` (which
  sets `g_dwItemUseQuantity`) first, others go straight to 0x12. Other
  items play sound 3.
- `ItemUseScreen` (0x12): applies the item to the member in
  `g_dwStatusEquipCharacter` and shows the result (text 0x400/0x401/0x403);
  A or B returns to 0x11.

Types are in `include/items_menu.h`; the handlers are matched in
`src/gamemode/modes/items/` for both versions. JP handlers sit +0x54 from
US (0x11 `0x080395D0`-`0x080397A4`, 0x10 `0x080398A8`-`0x080399C8`, 0x12
`0x080399C8`-`0x08039A68`), taken from JP's dispatch table; the RAM
globals sit +0x60 from US.

## Minigames (0x1B, 0x1C, 0x24, 0x2B, 0x2F, 0x33)

PROVEN from US decompiles; the state names in the headers are provisional.

| Mode | Screen state (US) | Header | High scores (`g_saveManager`) |
|---|---|---|---|
| 0x1B `WizardCrackerPopItMinigame` | `*g_pWizardCrackerPopIt` (`0x03005230`, allocated 0x1AC bytes) | `include/wizard_cracker_pop_it.h` | `adwWizardCrackerPopItHighScores` |
| 0x1C `DivinationTeaMinigame` | `g_DivinationTea` (`0x03005B28`) | `include/divination_tea.h` | none |
| 0x24 `UnusedServePumpkinJuiceMinigame` | `g_ServePumpkinJuice` (`0x03005238`) | `include/serve_pumpkin_juice.h` | none |
| 0x2B `HippogriffGlideMinigame` | `*g_pHippogriffGlide` (`0x03002088`, allocated 0x1F0 bytes) | `include/hippogriff_glide.h` | `adwHippogriffGlideHighScores` |
| 0x2F `RiddikulusMinigame` | `g_Riddikulus` (`0x03002048`) | `include/riddikulus.h` | `adwRiddikulusHighScores` |
| 0x33 `HarryVsDementorsMinigame` | `g_HarryVsDementors` (`0x03002E18`) | `include/harry_vs_dementors.h` | none |

- Each update handler is a `switch` on `dwModeState`; the handlers only
  drive the state machine and call the screen's own helpers, which are not
  decompiled yet (`sub_` names in the headers).
- The three-entry high score arrays are indexed by the difficulty, which
  the minigame menu passes in `dwCurrentGameModeArg3`, and sit at
  `SaveManager+0x10`/`+0x1C`/`+0x28` (`docs/formats/save.md`). Wizard
  Cracker Pop-it raises its entry in its results state and when a round is
  won, Riddikulus on A/Start in its results state, Hippogriff Glide in its
  finish state.
- Riddikulus and Harry vs Dementors share a results/pause menu shape:
  `dwModeScratchB` (the word at `0x03003F14`, which Riddikulus and Wizard
  Cracker Pop-it name separately as `g_dwListMenuSelection`) is the
  selected row, advanced by `StepWrappedSelectionVertical_candidate`; A
  either restarts the minigame with `PushGameMode_3(<mode>, 6, arg2, arg3)`
  or calls the screen's exit helper.
- `UnusedServePumpkinJuiceMinigame` has handlers in the dispatch table but
  no known pusher; its menu rows leave through
  `PushGameMode_2(MinigameDifficultySelect, 6, arg2)`.
- `DivinationTeaMinigame` writes BG2's affine parameters directly, drives
  16 leaf objects through `SetObjectAffineTransform` (scale words have 8
  fractional bits) and shows a random fortune: dialog text `0xA5F` plus
  `Mt19937RandRange(0, 0x5A)`. Its final state pushes `MinigameMenu` with cursor entry 3.

Handlers are matched in `src/gamemode/modes/minigame/<minigame>/` for both versions.
JP handlers (init/update/exit, from JP's dispatch table): 0x1B
`0x080323F8`/`0x08032578`/`0x080338E8`, 0x1C
`0x08041954`/`0x08041AC8`/`0x080422A4`, 0x24
`0x08033DE8`/`0x08033F24`/`0x08035284`, 0x33
`0x0801E170`/`0x0801E27C`/`0x0801EE18`; 0x2B and 0x2F sit at the US
addresses. The screen state addresses match US except Wizard Cracker
Pop-it (`0x03005290`), Divination Tea (`0x03005B88`) and Serve Pumpkin
Juice (`0x03005298`).

## Not yet located

- Whether `DebugMenuMain` is reachable/meaningful from every game state,
  or only from specific ones (e.g. title screen) -- untested.
- JP addresses for `g_dwPendingGameMode`/`g_dwCurrentGameMode`.
