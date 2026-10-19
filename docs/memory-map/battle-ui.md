# Battle menus and messages -- memory map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

This document covers the battle system's *presentation* layer: the menu
state machine and every screen's confirm handler, the message/dialog
dispatcher, the item catalog those menus index, and the Special Move
content each character's menu reaches. The mechanics those menus
eventually drive -- `BattleFighter`, the damage formulas, status
effects, spell tables -- are in [`battle.md`](battle.md).

The two layers are genuinely decoupled: **no menu confirm handler calls
the effect-trigger function (`FUN_08018b70`) directly.** Every screen
writes a handful of `BattleFighter` fields (`bSpellId`, `bSpellLevel`,
`bSelectedActionIndex`, `bPendingActionKind_candidate`, `bSlotParam`)
and closes the menu; the effects fire afterwards, in the actor-tick
execution layer [`battle.md`](battle.md) documents.

## The battle menu itself -- PROVEN

Found by walking backward from the top-level menu label table (see below),
not from `GetDialogText`'s callers directly (170+ call sites, mostly
unrelated dialog text elsewhere in the ROM -- not a practical starting
point on its own). The real entry point was a byte-pattern search for the
raw bytes of `0x8f0` (`2288`, `Cast Spell`'s string id) as 32-bit literal
data, which landed on a 7-entry table at `0x0804d808` referenced from
`DrawBattleMenuText` -- the menu's own label-drawing function.

### Menu state, `FightState` fields -- PROVEN

Matched C: `src/combat_dialog/`.

- **`bMenuScreen`** (`+0x1070`, `BattleMenuScreen`): the open screen. `1` top
  menu, `2` spell list, `4` Special Moves, `5` spell cast levels, `6` enemy
  target, `7` items, `8` ally target, `9` pending fighter. `0`, `10` and bit
  `0x80` mean no input is taken.
- **`bMenuCursor`** (`+0x147C`): the highlighted row, or the target slot on
  screens `6`, `8` and `9`.
- **`bSpellMenuCursor`** (`+0x147D`): the spell-list row that opened screen `5`.
- **`nTargetFlashEffect`** (`+0x1484`): palette effect flashing the targeted
  fighter's sprite (`FlashEnemyTarget`, `FlashAllyTarget`,
  `FlashPendingFighter`), ended by the `Stop*Flash` functions.

Each `Open*Menu` function sets `bMenuScreen`, redraws the menu frame and the
fighter's stats panel, and shows one icon per row through
`SetBattleMenuIconState` (grayed rows are semi-transparent). After every cursor
move `DrawBattleMenuText` prints the row's label, for a cast level also its name
and cost.

### Top-level menu, PROVEN

**`0x0804d808`**, a 7-entry `int32[7]` table of dialog-text ids, read as
`table[bMenuCursor]` by `DrawBattleMenuText` on the top menu:

```
[0x8f0, 0x8f1, 0x960, 0x8f2, 0x8f3, 0x8f4, 0x8f5]
= [2288, 2289, 2400, 2290, 2291, 2292, 2293]
= [Cast Spell, Special Move, Informus, Use Item, Flee, Folio Bruti, Help]
```

This directly settles where `Informus` (string id `2400`, not adjacent to
the `2288`-`2293` block in the *string table*) actually sits in the *menu
order*: index `2`, between `Special Move` and `Use Item` -- exactly the
order the user-facing glossary lists it in. All 7 items the user asked
about are accounted for by this one table.

**`OpenBattleTopMenu`** opens this
screen for a given fighter: sets `bMenuScreen=1`, builds a local 7-entry
enabled/grayed array (all `1` by default), then:

- grays index `1` (`Special Move`) if the active fighter is Hermione with
  `dwHermioneSpecialUsed != 0` or Ron with `dwRonSpecialUsed != 0` -- the
  per-battle "already used this Special Move" flags, set by
  `DispatchPendingAction`.
- grays index `2` (`Informus`) **and** index `4` (`Flee`) together, in the
  same branch, when `DAT_03003f24 == 0xff` -- matching the user's
  "Informus/Flee grayed out for bosses" fact exactly; `DAT_03003f24` is
  the natural "is this a boss fight" flag/index candidate (not
  independently named further here).

**`ConfirmBattleTopMenu`** (`0x08011bec`) is the confirm (A-button) handler for
this screen, `switch(bMenuCursor)` with 7 cases matching the table above
1:1:

- **case 0, Cast Spell**: `bMenuScreen = 2` (spell-list screen), then
  builds the list via `SetBattleMenuIconState(1, i, fighterType, 1)` for
  `i` in `[0, pFighter->bUnk_0x0F)` -- **`bUnk_0x0F` is the fighter's
  known-spell count**, directly confirming "only unlocked spells for that
  character" from the task description.
- **case 1, Special Move**: if the active fighter is Harry, saves the
  current mode-stack context and pushes game mode `0x26` via
  `FUN_0802c7e0(0x26, 1, 0)` -- **this is the Folio Universitas**,
  matching `DAT_03003f3c == 0x26` already read by `ResumeBattleAfterSubmode_candidate` earlier
  in [`battle.md`](battle.md) (that function consumes the *result* of a completed card
  selection, not the menu itself -- the two findings now connect).
  Otherwise (Hermione/Ron) calls **`OpenSpecialMoveMenu`** (see below) -- one
  shared 3-item-list screen for both, not per-character screens.
- **case 2, Informus**: gated by `DAT_03003f00 != 0xff` (a second,
  independent boss-style check from the graying check above -- same
  "boss" concept, different flag/slot). Sets the active fighter's
  `bSelectedActionIndex=0`, **`bSpellId=1`** (`Informus`'s own real
  `SpellId`, see [`battle.md`](battle.md)'s `bSpellId` writeup -- not borrowed from
  `Spongify`), `bPendingActionKind=4`, `bSpellLevel=0`, then `bMenuScreen=6`
  (the same target-select screen spellcasting uses). `bPendingActionKind` is
  `BattleFighter+0x3B`, i.e. **`bPendingActionKind_candidate`** itself
  (`None`=`0`/`UsePotion`=`1`/`SpecialMove`=`2`/`Flee`=`3`/`Informus`=`4`)
  -- the same field `DispatchPendingAction`'s top-level switch reads --
  so `bPendingActionKind=4` is simply this menu tagging the pending action as
  `Informus`, exactly like `Flee`/`UsePotion`/`SpecialMove` each tag their
  own screens; a regular `Cast Spell` selection leaves it at `None` (`0`)
  instead (see `bMenuScreen==2` above). There is no `Spongify`-borrowing
  or cast-disambiguation happening here at all -- `Informus` is a
  first-class pending-action kind with its own real `SpellId`.
- **case 3, Use Item**: `bMenuScreen = 7` (item-list screen), calls
  `OpenItemMenu` to build the list.
- **case 4, Flee**: gated by `DAT_03003f24 != 0xff` (the same flag
  `OpenBattleTopMenu` already used to gray this entry -- re-checked here
  too), sets `bMenuScreen=0` (closes the menu) and `bPendingActionKind=3`.
- **case 5, Folio Bruti**: calls `FUN_0802c7c4(0x2d)` -- a mode-push,
  presumably to the Folio Bruti screen (not walked further here; see
  [`../formats/folio_bruti.md`](../formats/folio_bruti.md)).
- **case 6, Help**: saves mode-stack context and pushes game mode `0x44`
  via `FUN_0802c800(0x44, ...)` -- matches `DAT_03003f3c == 0x44`, the
  other mode value `ResumeBattleAfterSubmode_candidate` branches on, consistent with "opens a
  menu similar to the pause menu" from the user's description (not
  walked further).

Cursor movement and A/B dispatch both live in **`TickBattleMenuInput`**:
Right/Left (`g_wKeysPressed`, see [`input.md`](input.md)) step `bMenuCursor`,
wrapped by `WrapBattleMenuCursor`; the target screens move between occupied
fighter slots instead, the ally slots in reverse. A and B call the `bMenuScreen`
entries of `g_apfnBattleMenuConfirmHandlers` (`0x0804E2EC`) and
`g_apfnBattleMenuCancelHandlers` (`0x0804E318`) with the fighter's type and
record.

### The rest of the menu tree, PROVEN, and where the effect calls actually live

Walking every remaining `bMenuScreen` confirm handler completes the
picture -- and the headline result is structural: **none of the menu's
own confirm handlers call the effect-trigger function
(`FUN_08018b70`) directly.** Every screen in this tree does the same
thing: write a handful of `BattleFighter` fields (`bSpellId`,
`bSpellLevel`, `bSelectedActionIndex`, `bPendingActionKind`, `bSlotParam`) and
set `bMenuScreen = 0` to close the menu. The actual effect calls all
happen afterward, in the actor-tick execution layer
[`battle.md`](battle.md) covers (`TickPlayerActionState`'s
case `0x1a` =
`HandleScriptedDamageEvent_candidate`, and its `0x40000`/`0x8000`
`Actor+0xc` flag branches) -- the menu and the effect system are fully
decoupled through these struct fields, confirming the split this
document's opening notes (menu-construction vs. action-execution are
genuinely two separate layers, not just two ends of one function).

- **`bMenuScreen==2`** (`ConfirmSpellChoiceMenu`, confirm handler for the
  per-character spell list opened by `Cast Spell`): `bSpellId =
  g_abSpellIdByCursor[fighterType*7 + cursor]` -- **`g_abSpellIdByCursor`
  (`0x0804e084`) is a per-character cursor-position -> real `SpellId`
  remap table** (already
  independently referenced by `DrawBattleMenuText`'s label-draw code for this
  same screen), needed because not every character's spell list shows
  the same `SpellId`s in the same menu order/count -- Harry's row is
  `[0,2,4,6,3,5,0]`, Ron's is `[0,2,4,6,9,5,0]`, and **Hermione's row,
  `[0,2,4,8,6,7,5]`, is the only one containing `8`** (cursor `3`): this
  is the actual `Fumos`-is-Hermione-only mechanism, confirmed at the
  menu-selection level rather than inferred from spell content alone.
  Ron's row is the only one containing `9` (cursor `4`) -- this is the
  actual `Spongify`-is-Ron-only mechanism (see the `bSpellId` writeup
  in [`battle.md`](battle.md)), matching `data/text/en_us.json` string `937`: "Harry receives
  Diffindo, Ron receives Spongify, and Hermione receives Glacius!".
  `bSpellLevel=0`, `bPendingActionKind_candidate=None` (`bPendingActionKind=0`). Then
  `OpenSpellTierMenu(fighterIdx, cursor)` opens screen `5`.
- **`bMenuScreen==5`** (`ConfirmSpellTierMenu`, spell cast-level list --
  Uno/Duo/Tria): confirms the **spell cast-level list from the task
  description** and gates it on affordability --
  `fighter.wSp < g_awSpellMpCost[spellId*3+cursor]` beeps/refuses (SP,
  not MP, despite the field name -- consistent with `ShowBattleMessage`'s
  `SpCost`/`MpCost` case split in the message table below). Also refuses
  casting `Spongify` (`bSpellId==1`) while `DAT_03003f24==0xff` (the same
  boss-flag candidate used to gray `Informus`/`Flee`) -- **a boss fight
  blocks Spongify specifically**, a new, concrete behavioral fact. Sets
  `bSpellLevel = cursor`; most spell/level combinations proceed to a
  target-select screen (`bMenuScreen=6`), except a few that execute
  immediately with `bSelectedActionIndex=0xfe` (self/no-target): `Fumos`
  (`bSpellId==8`) at level-1 (`Duo`, its party-wide cast, effect id `32`
  -- see [`battle.md`](battle.md)'s `Hidden` status bullet), `bSpellId==6`
  (`PetrificusTotalus`) + level-1, and (generically) any spell's level-2
  (`Tria`) cast **except `Glacius`** (`bSpellId==4`) -- i.e. by default a
  `Tria` cast doesn't need a target, with `Glacius` special-cased back
  into needing one. Not fully explained; flagged rather than
  over-interpreted.
- **`bMenuScreen==6`** (`ConfirmEnemyTargetMenu`, the enemy target-select
  confirm): after a vsync wait and some UI cleanup calls, simply writes
  `bSelectedActionIndex = cursor` and `bMenuScreen = 0`. Reads
  `aEnemySlotTurnOrderIndex` elsewhere in the target-select code in [`battle.md`](battle.md)
  (`g_pFightState->aEnemySlotTurnOrderIndex`, an array already used as an
  enemy-roster-index list by `ResolvePlayerAttack`'s callers) --
  **this screen targets enemies.** Used by: `Informus`, Ron's `Stink
  Pellet`/`Wizard Cracker`, the spell target-select path above, and
  Hermione's non-self lectures.
- **`bMenuScreen==7`** (`ConfirmItemMenu`, item-list confirm): checks
  `IsBattleItemSlotUsable(cursor)` (owns that potion -- refuses with a beep if
  not), then `bPendingActionKind=1`, `bSpellLevel = cursor + 0x38` (matches
  `DrawBattleMenuText`'s item-name text lookup, `GetRewardNameStringId_candidate(cursor+0x38)`) --
  **items are addressed by the same `bSpellLevel` field spell levels
  use, offset by `0x38`** into `g_pItemTable` (the item database
  below). Then calls `OpenAllyTargetMenu` (below) to
  pick a target.
- **`OpenAllyTargetMenu`** (`0x080107bc`), the shared **ally**-target-select
  *opener*: sets `bMenuScreen = 8` and reads `aAllySlotTurnOrderIndex` (a
  different array from state 6's `aEnemySlotTurnOrderIndex`) for its list --
  **`bMenuScreen==8` targets allies, not enemies.** Called from three
  places in this tree: `Use Item` (above), Hermione's non-"Proper Wand
  Technique" lectures (`Be More Careful`, `Good Study Habits` --
  consistent with them needing an ally target rather than an enemy), and
  the `bSpellId==8` special case inside the spell-level confirm above.
- **`bMenuScreen==8`** (`ConfirmAllyTargetMenu`, the ally target-select
  confirm): same shape as state 6's confirm -- vsync wait, writes
  `bSelectedActionIndex = cursor`, `bMenuScreen = 0` -- plus, if
  `bPendingActionKind==1` (the `Use Item` marker set above), calls
  `RemoveItems(itemIndex, 1)`, consuming the used item.

`Use Item`'s actual effect resolution happens later, in
`TickPlayerActionState`'s `Actor+0x60` sub-state `2`
(`FUN_08015f50`, `0x08015f50`): it only formats and shows the
already-computed damage/heal number (`DAT_0300274a`) via
`ShowBattleMessage`/`ShowFloatingDamageNumber` -- **it does not itself call
`FUN_08018b70` or compute an item's effect**, so an item's actual
gameplay effect (heal amount, stat boost, etc.) is set by something else
entirely, not walked here. This lines up with `g_pItemTable`'s
`dwType`/`dwParam` fields still being undecoded (noted above) -- item
effects plausibly come from there rather than from the
`g_apEffectScripts_candidate`/opcode-`0x97` system spells and Special
Moves use.

### Special Move submenu (Hermione's 3 Lectures / Ron's 3 Special Moves), PROVEN

**`OpenSpecialMoveMenu`** (`0x080105d8`) is the shared opener for both
characters' 3-item Special Move list: sets `bMenuScreen=4`, builds
exactly 3 entries via `SetBattleMenuIconState(3, i, fighterType, 1)` for `i` in
`0..2`. `DrawBattleMenuText`'s `bMenuScreen==4` case picks the label text base
by fighter type -- `fighterType==Hermione`: `textId = cursor + 0x8fa`
(`2298`-`2300`, already known to be `Be More Careful`/`Good Study
Habits`/`Proper Wand Technique`'s *string* ids in that order, per the
`g_abHermioneLectureEffectId_candidate` table in [`battle.md`](battle.md));
else (Ron): `textId = cursor + 0x8fd` (`2301`-`2303`, i.e. **cursor 0 =
Stink Pellet, cursor 1 = Wizard Cracker, cursor 2 = Stink Pellet 2**,
exactly the string-id order already on record).

**`ConfirmSpecialMoveMenu`** (`0x08011eb8`), this screen's confirm handler:

```c
BattleFighter *f = ...;
f->bSpellId = bMenuCursor;   // the selected list index, 0-2
f->bPendingActionKind_candidate = SpecialMove;   // bPendingActionKind = 2
if (fighterType == Hermione) {
    if (f->bSpellId != 1)          // not "Proper Wand Technique"
        goto target_select;         // OpenAllyTargetMenu
} else /* Ron */ {
    if (f->bSpellId != 2)          // not "Stink Pellet 2"
        goto target_select;         // bMenuScreen = 6, same screen Informus uses
}
// self-cast, no target needed:
f->bSelectedActionIndex = 0xfe;
bMenuScreen = 0;                   // close menu, execute immediately
```

So **Ron's `bSpellId` is set directly from the menu cursor (0/1/2)**, the
same field spells use, and **cursor index 2 (`Stink Pellet 2`) is the one
self-cast/no-target move** -- `Stink Pellet`(0) and `Wizard Cracker`(1)
both require picking a target first.

### Ron's Special Move effect ids, resolved: `44`/`46`/`45`

`HandleScriptedDamageEvent_candidate`'s separate `Actor+0xc` bit-`0x8000`
branch (already documented above as reading `DAT_0805150a[bSpellId]`
"unconditional of fighter type") is the actual trigger: since the menu
above proves `bSpellId` is set to the selected Special-Move cursor index
(0-2) for Ron exactly as it is for Hermione's lectures, and
`DAT_0805150a`'s entries `3`-`5` are already independently proven
identical to `g_abHermioneLectureEffectId_candidate` (same array, two
access paths), entries `0`-`2` are backed by the same mechanism that
resolves Hermione's:

```
DAT_0805150a = [44, 46, 45, 49, 51, 50, 41]
                0    1   2  <- Ron, indexed by his menu cursor (bSpellId)
```

i.e. **`Stink Pellet` = effect id `44`, `Wizard Cracker` = effect id
`46`, `Stink Pellet 2` = effect id `45`**.

Cross-checked against the actual extracted script content
(`src/combat_fx/effect_scripts/effect44.h`/`effect45.h`/`effect46.h`):

- **Effect `44`**: a single unconditional `StatusEffect 17 0 0`
  (opcode `0x97` case `0x11`, "Paralyzed", the *unconditional*-apply
  variant per [`battle.md`](battle.md)'s paralysis section) after a throw-style
  animation -- matches a single-target "throws a stink pellet, paralyzes
  them" move, consistent with `Stink Pellet` needing a chosen target.
- **Effect `45`**: branches on a script-local parameter
  (`GotoIfLocalANotEqual 0 50`) between the same simple throw-and-
  paralyze sequence (label `50`, structurally identical to effect `44`)
  and an extended sequence applying `StatusEffect 17 0 0` **three times**
  in a loop -- consistent with `Stink Pellet 2` being an
  enhanced/multi-target version of the same paralysis effect, and with it
  being the one move that skips target selection (the multi-apply branch
  presumably walks all enemies itself, script-side).
- **Effect `46`**: fires only one `StatusEffect`, using **case `0x1B`
  (`27`), `ForceItemDrop`** -- see the "`StatusEffect` sub-cases, full
  case-by-case writeup" section below: it ORs bit `0x04` into
  `FightState->bBonusRewardFlags`, the exact same byte/family `ExtraExpBonus`
  (case `2`, bit `0x01`) and `GrantExtraXp` (case `3`, bit `0x02`) use.
  Mechanically distinct from both Stink Pellet variants (which both use
  the paralysis case `0x11`), confirming `Wizard Cracker` as a distinct,
  non-paralysis effect -- exactly the kind of "not paralysis" outlier
  the ordering evidence predicted. `Wizard Cracker`'s own move
  description text (`data/text/en_us.json` string ids `1725`/`2615`)
  states its effect as making the target creature drop an item; what
  reads `FightState->bBonusRewardFlags`'s bit `0x04` to grant that item is not
  traced.

Confidence: the menu-order/mechanism chain above (7-item table ->
confirm dispatch -> Special Move submenu -> `bSpellId` -> `0x8000`-branch
table read) is **PROVEN**; the specific `44`/`45`/`46` <-> move-name
assignment is **STRUCTURAL MATCH**, corroborated by both position
(matches the string-id order exactly) and content (the mechanically odd
one out, effect `46`, lands on `Wizard Cracker`, the mechanically odd one
out by gameplay behavior) -- not yet a live/dynamic confirmation the way
`ResolveEnemyAttack` got one.

### The top-level battle menu, PROVEN via `data/text/en_us.json`

Decoding the dialog string table directly (see
[`../formats/text.md`](../formats/text.md))
finds the real, un-truncated top-level battle menu labels as consecutive
string ids `2288`-`2293`: **`Cast Spell`, `Special Move`, `Use Item`,
`Flee`, `Folio Bruti`, `Help`**, with `Informus` (string id `2400`, also
`2755`) a separate top-level entry not adjacent to this block.
`Informus` is a first-class `SpellId` (`1`): string `2400` is exactly
what its own `spellId + 0x95F` name formula produces. Its trigger path
and its `BumpMonsterDocLevel` effect script are traced in [`battle.md`](battle.md)'s
`bSpellId` and `DispatchPendingAction` sections.
String ids
`2298`-`2300` (`Be More Careful`, `Good Study Habits`, `Proper Wand
Technique`) exactly match Hermione's three named lecture scripts
word-for-word, independently confirming that identification;
`2301`-`2303` (`Stink Pellet`, `Wizard Cracker`, `Stink Pellet 2`) are
Ron's three Special Move item names -- see above for their unconfirmed
effect-id mapping.

## Attack/action animation-state dispatchers

The two functions that actually drive a fighter's turn frame-by-frame
once [`battle.md`](battle.md)'s damage formulas are ready to fire. Both
are registered as a fighter's sprite `Actor->pfnTick` callback at init
(see battle.md's "The NPC-vs-PC split") and share one structural idiom: a
per-fighter-`Actor` state byte (`Actor+0x8D`) drives a large jump table
of case-bodies, each of which branches into a shared tail
(`bl`-as-branch, not `bx lr`) instead of returning normally.

### `TickFighterAttackAnimState_candidate` (`0x08015608`) -- enemy side

**PROVEN and fully walked**: all 27 case bodies trace to genuine
termination, matching `gbadisasm`'s own single-function span
(`0x08015608`-`0x08015F4F`, confirmed against `build/us/full_disasm.s`;
no `thumb_func_start` in between). The shared epilogue at `0x08015F16`
decompiles cleanly once its `bl 0x08015F16` call sites and the epilogue's
own `pop {r0}; bx r0` (`0x08015F24`) get Ghidra instruction-level flow
overrides (`Call-Return`/`Return`) -- Ghidra can't infer these are
non-returning on its own since the epilogue manually pops the *caller's*
return address instead of using `pop {..., pc}`/`bx lr`.

Case `0` (`0x080156B4`) leads into the code that calls `ResolveEnemyAttack`
(see battle.md) at two symmetric call sites (`0x08015B5C`/`0x08015BE0`,
one per branch of a `MonsterTable.special_effect_chance == 100` check).

Three callees, all `_candidate` (structurally strong, not proven
identities):

- **`ShowBattleMessage`** (`0x08010864`) -- prints a battle message by
  `BattleMessageCode`; case 6 shows the queued faint messages, case 5 the
  attack result (see the tables below).
- **`ShowDamageNumber_candidate`** (`0x08017B5C`) -- stores a damage
  value onto the target's sprite `Actor+0x62` and triggers a state
  change via `SetActorActionState`.
- **`SetActorActionState`** (`0x08001E7C`) -- writes directly to
  `Actor.bActionState` (`+0x8D`, the byte this dispatcher switches on)
  and sets the `bActionFlags` bit-`0x01` flag several case bodies check.
  This is a generic per-`Actor` setter, not battle-specific -- see
  `docs/formats/rooms.md` and `docs/formats/room_scripts.md` for its
  non-battle uses.

**The "Tick" call chain is PROVEN:**
`InitMonsterBattleActor` (`0x08014C88`) writes this function's address
into `Actor+0x98` (a callback-registration slot, not a direct call).
**`TickActor`** (`0x08001FD8`) is a per-actor per-update-pass
function: it reads `Actor+0x98`, and if non-null (and a gating check,
`IsActorTickAllowed`, passes), calls libgcc's **`_call_via_r1`**
(`0x0804A2C4`, see `../compiler.md`) to invoke it. **`TickActorList`**
(`0x08000918`) walks the linked list of all active actors, calling
`TickActor` once per actor per call. So the chain is
`TickActorList` -> (per actor) `TickActor` ->
`_call_via_r1` -> `TickFighterAttackAnimState_candidate`, a
generic per-actor-per-frame callback dispatch -- "AttackAnimState" is
arguably too narrow given case `0x1a`'s broader turn/action-execution
content (target selection, `ResolveEnemyAttack`, message/reward
dispatch), not renamed further.

**`IsActorTickAllowed`** (the `TickActor` gate) returns true iff
`g_GameModeStackContext.dwCurrentGameMode` (`0x03003EF4`) `!= Dialog`
(`0x18`) AND it equals `g_dwPendingGameMode` (`0x03003F18`) -- "no mode
transition in flight, and not in Dialog mode". See
[`game_modes.md`](game_modes.md) for the full `GameMode` enum.

**`FightState` fields**, from decompiling this dispatcher and
`ShowBattleMessage`:

- `+0x147E` -> `bActionDelayCounter_candidate` (u8): decremented once per
  tick call (bits `0x20`/`0x40` of a per-fighter status byte each drive
  one decrement path), gates further action once it hits 0. Set to
  5/10/20 depending on branch -- frames-remaining delay before an
  action/animation actually fires.
- `+0x14AC`..`+0x14C4` -> `aFaintMessages_candidate`, a 6-entry
  `FaintMessageEntry_candidate[6]` array (`{u16 wDamage; u8 bEffectId; u8
  bFlag;}`, 4 bytes/entry -- the count falls out exactly from
  `(0x14C4 - 0x14AC) / 4`). One entry per queued fainted-fighter message.
- `+0x14C4` -> `bFaintMessageCount_candidate`: an incrementing
  write-cursor/count into `aFaintMessages_candidate`. The `== 0` gate in
  `ApplyDamageToEnemyFighter` (battle.md) means "no messages queued yet".

Found by walking the live call stack (mGBA gdb backtrace) up from
`ResolveEnemyAttack`; a sibling function, `UpdateMonsterScreenShake`
(`0x08015574`), called from within this dispatcher, mirrors the battle
screen shake on the monster (and the shadow of monsters 45-47) by flipping
it horizontally while `bScreenShakeTimer_candidate` runs. Deeper call-stack
frames above this dispatcher (through `0x08001FDA`, `0x0800091A`, `0x0802C822`, `0x0802C6B6`, into
`main` at `0x08029690`) are low-address, high-xref generic engine
dispatch, not investigated further.

### `TickPlayerActionState` (`0x0801602C`) -- player/Buckbeak side

Matched byte-exact by `src/combat_fighter/tick_player_action_state.c`
(`0x0801602C`-`0x08017B5C`): reads `Actor+0x8D`, dispatches a 27-entry
`switch` over the table at `0x08016090` (case labels in source order `0`,
`0xf`, `2`, `0x1a`, `0x15`, `4`, `1`, `5`, matching agbcc's
source-order emission), and every case tail-branches into the shared
epilogue at `0x08017B42` via `bl`-as-branch.

Read directly from ROM rather than inferred from decompiler output,
every entry resolves to a genuinely separate, cleanly-bounded function:

| Case | Address | Function |
|---|---|---|
| `0` | `0x080160FC` | `PlayActionWindupFlash` -- queues a palette-flash cue via `FUN_0800d264` (the same palette-refresh/fade queue used to undo poison discoloration), keyed by an anim-table entry and `Actor+0xd5`'s high nibble, plus an anim-data-table switch via `SetPlayerActorAnim` (`0x08015484`) -- the windup flash before the swing/cast animation starts |
| `1` | `0x08017A7C` | `PlayFighterImpactSound` -- per-fighter-type sound (`Actor+8`) plus a shared impact sound, the moment the attack/spell visually connects |
| `2` | `0x080161A2` | `ApplyDamageNumberAnimState` -- commits a damage number previously staged at `Actor+0x62` by `ShowDamageNumber_candidate`: sound, a HUD refresh, then (once flag `0x40000` is set) resets the anim state and applies the damage via `ApplyDamageToAllyFighter` |
| `3`, `6`-`14`, `16`-`20`, `22`-`25` | `0x08017B42` | `TickPlayerActionStateNoOp` -- shared no-op default, also every other case's own tail branch target |
| `4` | `0x080177D8` | `ApplyStatusRestoreItemEffect` -- resolves a restorative-item/status-cure effect: `GetPotionEffect(bSpellLevel)` selects among MP restore, SP restore, a cure call, or lifting `Paralyzed`, each with its own `TriggerBattleEffect` id and cost/message |
| `5` | `0x08017ADE` | `ReturnFighterToPosition` -- post-action wait/return-to-formation state: flips the sprite and arms a 30-frame counter on entry, then on expiry clears `bSelectedActionIndex`, un-flips, and resets the anim state |
| `15` (`0xF`) | `0x0801618A` | `WaitForMoveThenApplyDamageNumber` -- gated on `Actor+0x3c`/`+0x40` both being zero (the velocity fields a `MoveTo` zeroes on completion, per [`../formats/battle_scripts.md`](../formats/battle_scripts.md)) -- waits for the fighter's current move to finish, then falls straight through into `ApplyDamageNumberAnimState`'s body (case `2`) with no branch in between |
| `21` (`0x15`) | `0x08016E64` | `HandleScriptedDamageEvent_candidate` (spans `0x08016E64`-`0x0801732C`, one function despite the address gap -- the shared-epilogue false-split pattern documented elsewhere in this codebase). Its *tail* (`Actor+0x60` status byte, 5 sub-states) dispatches fixed-damage crit/faint-sequence handling (scripted/special-event damage, no RNG, no `Mt19937RandRange` call anywhere in this dispatcher's range). Its *head* (`Actor+0xc` flag bits `0x40000`/`0x8000`) is the Special Move trigger -- see below |
| `26` (`0x1A`) | `0x080161FE` | `ExecutePlayerAttackSequence` -- the player-side turn resolver, see [`battle.md`](battle.md)'s consolidated pseudocode |

`Actor+0x60`, referred to as `bAttackOutcomeState` in the case-0x15
(`HandleScriptedDamageEvent_candidate`) matching source, is the low byte of
`wScriptPC` (see [`../formats/battle_scripts.md`](../formats/battle_scripts.md)'s
"The interpreter" section) -- a real storage-reuse overlap, not two
conflicting offset claims: the byte holds the actor's script bytecode
position while a behavior script is running, then gets reused as a small
attack-outcome state counter (values `0`-`6`) once native code takes over
for that tick. `TickPlayerActionState` never reads the high byte
(`Actor+0x61`), consistent with treating it as a byte-sized state value
rather than the full `wScriptPC` word.

Same pattern one field over: case `2` (`ApplyDamageNumberAnimState`) reads
and writes a `u16` `wStagedDamage` at `Actor+0x62` (`ldrh`/`strh`,
real-bytes confirmed), which is the low byte of the script interpreter's
`bScriptEffectId` (`Actor+0x62`, 1 byte) plus the low byte of
`bScriptLocalA` (`Actor+0x63`, 1 byte) taken together -- the whole
`0x60`-`0x64` span is native tick code's post-script scratch area, reused
byte-for-byte with different types/meanings once a script for that actor
finishes running.

Only `TickPlayerActionState` (`0x0801602C`) and
`TickPlayerActionStateNoOp` (`0x08017B42`) are named in `functions.us.cfg`
-- the other eight are reached exclusively through the raw `.4byte` jump
table at `0x08016090`, and gbadisasm doesn't rewrite a table's pointer
operands to a target's symbolic name when that target gets one in the
config, so naming any of them there breaks `just disasm-compare` with
`undefined reference to '_0x...'` (the table literal still emits the old
bare-address label, which no longer exists once the target is named).
Their names above are real and citable, just not yet synced into
`functions.us.cfg`.

All nine target functions sit back-to-back in ROM
(`0x080160fc`-`0x08017b51`, one ~28-byte gap before
`HandleScriptedDamageEvent_candidate` aside) and each branches into the
shared tail `TickPlayerActionStateNoOp` rather than using `bx lr`. Case
`2` and case `0xF` share one body outright: `0x080161a1` (the last byte
of `WaitForMoveThenApplyDamageNumber`) falls straight into `0x080161a2`
(`ApplyDamageNumberAnimState`'s first byte).

The dispatch itself (`0x08016082`-`0x0801608A`) is a real `mov pc, r0`
jump table, not a `bl` call -- so none of the case targets get their own
stack frame or register set; they all run inside the one frame
`TickPlayerActionState`'s own prologue (`0x0801602C`-`0x08016038`)
allocates: `push {r4-r7,lr}` + spilled `r8`/`sb`/`sl` + `sub sp, #0x10`,
with its incoming `Actor*` parameter moved into `r7` right there and
never reloaded. Every local Ghidra reports as `unaff_r7` or
`in_stack_00000008`/`in_stack_0000000c` when a case address (e.g.
`0x080161FE`) is decompiled on its own is really `r7`/`sp+8`/`sp+0xc`
from that same shared frame -- Ghidra just can't see the connection
because each case target is a separate `Function` in its database.
Ghidra's own switch-table recovery (`Decompiler Switch Analysis`) does
resolve the `mov pc, r0` dispatch correctly when decompiling from the
true entry point `0x0801602C` directly, producing one clean `switch`
covering every case with no `unaff_r7`/`in_stack_*` noise -- prefer
that over decompiling an individual case address when reading this
dispatcher in Ghidra.

`ExecutePlayerAttackSequence` (case `0x1A`) is confirmed as its own real
function, not a fragment: a data xref from `0x080160F8` (a slot in the
same jump table) lands directly on it.

#### Special Move dispatch (`HandleScriptedDamageEvent_candidate`'s head)

The `0x40000`-flag branch is what actually fires a character's Special
Move script: for Harry, it reads `(&g_abHarryCardEffectId)[DAT_03003f44]`
(the currently-selected Folio Universitas card slot) and calls
`FUN_08018b70` on it -- "Special Move" opens the Folio Universitas for
Harry. For Hermione, it reads
`(&g_abHermioneLectureEffectId_candidate)[bSpellId]` (her lecture
selection, stored in the same `bSpellId` field spells use) and does the
same. For Ron/Buckbeak, this branch just calls `SetPlayerActorAnim(unaff_r7,0)` (`0x08015484`)
and returns -- no `g_ab*EffectId`-style table lookup happens here at all.

A separate, unconditional-of-fighter-type `0x8000`-flag branch reads
`DAT_0805150a[bSpellId]` (`0x0805150a`, `[44, 46, 45, 49, 51, 50, 41]`) --
entries `3`-`5` are the exact same bytes as
`g_abHermioneLectureEffectId_candidate`'s 3 values, read through a
differently-based pointer; entries `0`-`2` are Ron's own 3 Special Move
effect ids, resolved in "Ron's Special Move effect ids" above
(`44`=`Stink Pellet`, `46`=`Wizard Cracker`, `45`=`Stink Pellet 2`).

The jump table's per-case `PTR_FUN_08016090` addresses above are read
directly from ROM, not decompiler-inferred, and every entry lands on a
genuinely separate, cleanly-bounded function -- none of these are Ghidra
mis-boundaries.

## Special Move and card content

### Harry's 16 Folio Universitas cards, PROVEN

Found via the game's own **Card Combo Glossary** text
(`data/text/en_us.json`, decoded per
[`../formats/text.md`](../formats/text.md)): string ids
`1144`-`1159` are a 16-entry list of card-combo *names*, immediately
followed by a matching 16-entry list of short *descriptions* at
`1160`-`1175` -- both lists line up positionally, 1:1, with
`g_abHarryCardEffectId`'s 16 real table entries (read directly
from ROM at `0x080514c8`):

| Index | Effect id | Card name | Description (in-game) |
|---|---|---|---|
| 0 | 15 | `Horklump Spores` | Horklump spores appear and blast opponent with pollen. |
| 1 | 5 | `Tempest Jinx` | Causes a gust of wind to blow one opponent off-screen. |
| 2 | 10 | `Cracker Jinx` | Causes Wizard Crackers to go off and give heavy damage to all opponents and some damage to player's party. |
| 3 | 42 | `Poison Antidote` | Removes any poison affecting a party member. |
| 4 | 52 | `Remove Jinx` | Removes any jinx affecting a party member. |
| 5 | 18 | `Poison Immunity` | Gives all party members immunity to poison for one magical encounter. |
| 6 | 37 | `Revive` | Revive an unconscious member of your party. |
| 7 | 35 | `Girding All` | Increases all party members' physical defense. |
| 8 | 53 | `Reparifors` | Cancels any magical ailments affecting the party. |
| 9 | 48 | `Replenish MP` | Sets a party member's Magic Points (MP) to maximum. |
| 10 | 40 | `Replenish SP` | Sets all party members' Stamina Points (SP) to maximum. |
| 11 | 14 | `Extra EXP` | Gain bonus Experience (EXP) Points after successfully completing a magical encounter. |
| 12 | 41 | `Bludgers` | Causes Bludgers to rain down on opponent for low damage. |
| 13 | 47 | `Snitch` | Snitch flies around opponent's head, distracting them. Opponent loses a turn. |
| 14 | 39 | `Sonorous Charm` | Creates a magnified roar that disrupts all in its path. |
| 15 | 43 | `Ultimate MP` | Selected party member gains all spell abilities. |

Confidence: **PROVEN** for the index<->effect-id<->name correspondence
as a whole -- three of these (index `5`/`Poison Immunity`, index
`11`/`Extra EXP`, index `13`/`Snitch`) were already independently
confirmed in [`battle.md`](battle.md) through opcode-content tracing alone, *before*
the glossary text was consulted, and all three land on the exact same
slot the glossary gives them; that three-way agreement is what makes
the positional correspondence trustworthy for the other 13 cards too,
not just an assumption. Each script's content was additionally spot-
checked against its description (e.g. `Poison Antidote`/`Remove Jinx`
both call the not-yet-named opcode `0x97` cases `0xF`/`0x14`
respectively on a single target, matching "a party member" in both
descriptions; `Reparifors` calls case `0x14` three times, matching
"the party" plural). The one exception is **`Girding All`** (index `7`),
whose script has no `StatusEffect` opcode at all -- see the `DefenseBoost`
bit writeup in [`battle.md`](battle.md); its mapping to effect id `35` is solid (by position
and elimination) but its actual defense-boost mechanism is not.

All 16 are now named in `src/combat_fx/effect_scripts/` as
`SpecialHarry<CardName>` (matching the `SpecialHermione*`/`SpecialRon*`
convention already used for the other two characters' Special Moves),
e.g. `SpecialHarryHorklumpSpores`, `SpecialHarrySnitch`,
`SpecialHarryUltimateMp`. See `../formats/battle_scripts.md`'s Future
Work section (now marked done) for the prior open questions this
resolved.

**How the effect-id -> script trace works**, for reproducing/extending
this: `FUN_08018b70(effectId, ...)` (the anim/effect trigger already
documented above) calls `FUN_08018be0(effectId, ...)`, which spawns a
new `Actor` and sets `Actor+0x62 = effectId` and `Actor+0x98` to a
generic dispatcher (`0x08018cc1`); `TickActor` then
interprets that actor's script every tick via `FUN_08018cf8`
(`0x08018cf8`), which looks up the script buffer as
`g_apEffectScripts_candidate[Actor+0x62]` --
`g_apEffectScripts_candidate` (`0x0805b978`) is an array of 60+ script
pointers (at least `0`-`59` populated), one per effect id. Each opcode's
length is looked up in a 256-entry table at `0x08054f34`
(`instruction length = table[opcode] + 1` bytes, including the opcode
byte itself); walking a script from its pointer with that table finds
every opcode `0x97` instance and its case (sub-case) byte. Spell/card
effect-id tables (`g_abSpellEffectId_candidate` for the 10 real `SpellId`
values,
`g_abHermioneLectureEffectId_candidate` for Hermione's 3 moves,
`g_abHarryCardEffectId` for Harry's 16 cards) then map a
specific spell/card to one of those effect ids.

Note: opcode `0x97`'s case numbering above is the *inner* switch's case
index (the effect-type byte read from the script), distinct from
`FUN_08018cf8`'s own outer opcode number (`0x97`) that selects this
whole sub-table.

## Messages, dialog text, and the item catalog

### The item catalog the Use Item menu indexes

`g_pItemTable` (`0x08060EE4`) is the game's **general** item/equipment
catalog, not a battle-specific one: 79 real entries covering belts,
gloves, boots, caps, robes, potions, ingredients and key items, of which
the battle Use Item menu reaches only the 6-entry potions run. That is
why the menu's confirm handler offsets by `0x38` (56, the first potion
index) rather than indexing from zero.

The table's address, record layout, category values and extraction
pipeline are documented in
[`../formats/save.md`](../formats/save.md)'s "Item quantities and
equipment", which owns them -- the same item ids index the save
format's `itemQuantities` and `equippedItems`.

### `ShowBattleMessage` -- case -> dialog text table

Matched C: `src/combat_dialog/show_battle_message.c`. Each line goes through
`DrawBattleMessageLine` (inlined; `DrawTextLines`, see
[`../formats/text.md`](../formats/text.md)) at one of four text rows
(`BATTLE_TEXT_ROW0_Y`-`ROW3_Y`), on the right half (centred at x `0xA0`) or the
left (x `0x58`). Text is from `data/text/en_us.json`.

| `code` | Text ID | Text |
|---|---|---|
| 0 | `0x904`, with jingle `0x1A` | "The spell levels-up!" |
| 1 | `0x902` | "Your escape has been blocked." |
| 2 | `fighterType + 0x970`, then the move: Harry `value + 0x478`, Hermione `value + 0x8FA`, Ron `value + 0x8FD` | e.g. "Harry performs a Special Move:" |
| 3 | Harry: `g_adwSpecialMoveResultTextIds[value]`, for moves `3` and `15` plus the targeted ally's `FighterType`, for move `6` `g_adwReviveTextIds[pending fighter's type]`; Hermione `value + 0xA39`; Ron `value + 0xA36` | Special Move result, e.g. "Wow! Harry learned all possible spells!" |
| 4 | `g_adwFighterActionTextIds[fighterType]` (party) or `[rosterIndex + 4]` (enemy), then for a party spell `spellId + 0x95F`, or `0x8F6` with the spell (`@1`) and cast level (`bSpellLevel + 0x969`, `@2`) for spells with levels; nothing more for Buckbeak or an enemy | "Harry casts a spell:" / "The ruby fire crab attacks!" |
| 5 | attack result, by `param` -- see the table below | "Critical hit!", "@1 damage.", miss/poison/paralysis lines |
| 6 | pops `aFaintMessages_candidate` until empty: `@1` from `bEffectId` (`<= 2`: `0x8EC + id`; `3`: `0xA3D`; else `0x49E + id`) in `0x997`, "Critical hit!" above 999, then `0xA1B` when `bFlag` is `1`, else the damage in `0x997`; 30 frames per message, then `CheckBattleVictory` | who fainted the target, with what, and the damage |
| 7 | `fighterType + 0x973`, then `value + 0x604` | e.g. "Harry uses a potion:" |
| 8 | by item `value`: Wiggenweld (`0x38`/`0x39`) `targetType + 0x98D`; Pepperup (`0x3A`/`0x3B`) `0xA27`; antidote (`0x3C`) `targetType + 0x985`; anti-paralysis (`0x3D`) `targetType + 0x981` | "Harry's SP are replenished." / "Your Magic Points are refilled." / "Harry feels better!" / "Harry can move again!" |
| 9 | `0x998` | "@1 SP" |
| 10 | `0x999` | "@1 MP" |
| 11 | `0xA1E` | "You are victorious!" |
| 12 | `0xA1D` | "You've been defeated." |
| 13 | `g_adwFighterCantMoveTextIds[fighterType]`, enemy `0xA1C` | "Harry can't move." / "The opponent can't move!" |
| 14 | `fighterType + 0x981`, enemy `0xA20` | "Harry can move again!" / "The opponent can move again!" |
| 15 | `0xA3C` | "The opponent's attacks are weakened." |
| 16 | `pFighters[param].bFighterType + 0x991`, on that fighter's own row | e.g. "Harry is hidden from view!" |
| 17 | `0xA3E` | "The opponent is immune to paralysis!" |

`AttackResult` (5) first prints "Critical hit!" (`0x995`) when `value` exceeds
999, then:

| `param` | Text ID | Text |
|---|---|---|
| `0` | `0x997`, `@1` = `value`, less 999 past a critical hit | "@1 damage." |
| `1` | `0x996`, or `0xA1B` when the active fighter is an enemy | "The spell misses." / "The attack misses." |
| `2` | `g_adwFighterFaintTextIds` of fighter `value` (`FighterType`, or `rosterIndex + 4` for an enemy) | the fainted fighter |
| `3` | `0x976 + targetType` | "Harry is poisoned." |
| `4` | `0x97A + targetType` (enemy attacker), else `0xA1F` | "Harry is paralyzed." / "The opponent is paralyzed!" |

### Functions called from `ShowBattleMessage`

- **`PlayJingle`** (`0x0803FF70`) -- called by
  `SpellLevelUp` (id `0x1a`). Looks up the module pointer at
  `g_apMusicModules[moduleId]` and plays it as a jingle,
  `krapPlay(module, KRAP_MODE_JINGLE, 0)` (see `krawall.md`).
- **`PrepareBattleMessageDisplay_candidate`** (`0x08012FD4`) -- clears the
  message box, resets `dwTextTileCursor` and hides the seven battle menu icons
  (**`g_apBattleMenuIconActors`**, `0x03002668`) via **`HideBattleMenuIcon`**
  (`0x08012CB4`).
- `0x0804A2C4` (**`_call_via_r1`**) is one of libgcc's `_call_via_rX`
  stubs (`0x0804A2C0`-`0x0804A2FC`, one `bx rN` per register -- Thumb
  has no `blx reg`; see `../compiler.md`). Reached from `TickActor`'s
  callback dispatch.
