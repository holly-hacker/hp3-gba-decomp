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
and closes the menu; the effects fire afterwards, in the object-tick
execution layer [`battle.md`](battle.md) documents.

## The battle menu itself -- PROVEN

Found by walking backward from the top-level menu label table (see below),
not from `GetDialogText`'s callers directly (170+ call sites, mostly
unrelated dialog text elsewhere in the ROM -- not a practical starting
point on its own). The real entry point was a byte-pattern search for the
raw bytes of `0x8f0` (`2288`, `Cast Spell`'s string id) as 32-bit literal
data, which landed on a 7-entry table at `0x0804d808` referenced from
`FUN_08011520` -- the menu's own label-drawing function.

### Menu/UI state machine, `FightState` fields

- **`field_0x1070`** (u8): which menu *screen* is currently active. Values
  found: `1` = top-level 7-item menu, `2` = per-character spell list
  (`Cast Spell`), `4` = 3-item Special Move/Lecture list (Hermione's 3
  lectures and Ron's 3 moves share this one screen), `5` = spell
  cast-level list (Uno/Duo/Tria, inferred from `FUN_080101d0`'s case 5
  reading `pBVar6->aSpellEffectiveness[bSpellId-0x24]` as an item count,
  not walked further), `6` = target-select/confirm screen, `7` = item
  list, `8`/`9` = further submenus (not walked). `0` = no menu open.
- **`field_0x147c`** (u8): the current menu cursor index within whichever
  screen `field_0x1070` selects.
- Both consumed by **`FUN_08011520`** (`0x08011520`), called after every
  cursor move: draws the currently-highlighted entry's label (and, for
  the spell-level screen, its MP cost) via `GetDialogText`/`DrawTextLines`
  -- this is the menu's own label-draw routine, not a generic dialog
  drawer.

### Top-level menu, PROVEN

**`0x0804d808`**, a 7-entry `int32[7]` table of dialog-text ids, read as
`table[field_0x147c]` by `FUN_08011520`'s `field_0x1070==1` case:

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

**`FUN_080104a0`** (`OpenBattleMenu_candidate`, `0x080104a0`) opens this
screen for a given fighter: sets `field_0x1070=1`, builds a local 7-entry
enabled/grayed array (all `1` by default), then:

- grays index `1` (`Special Move`) if the active fighter is Hermione with
  `field_0x148c==0` or Ron with `field_0x1488==0` -- these two fields are
  the natural "lectures known" / "special moves known" counts (not
  independently confirmed by name, but exactly gate the one menu item
  that needs at least one unlocked move to be usable).
- grays index `2` (`Informus`) **and** index `4` (`Flee`) together, in the
  same branch, when `DAT_03003f24 == 0xff` -- matching the user's
  "Informus/Flee grayed out for bosses" fact exactly; `DAT_03003f24` is
  the natural "is this a boss fight" flag/index candidate (not
  independently named further here).

**`FUN_08011bec`** (`0x08011bec`) is the confirm (A-button) handler for
this screen, `switch(field_0x147c)` with 7 cases matching the table above
1:1:

- **case 0, Cast Spell**: `field_0x1070 = 2` (spell-list screen), then
  builds the list via `FUN_08011abc(1, i, fighterType, 1)` for
  `i` in `[0, pFighter->bUnk_0x0F)` -- **`bUnk_0x0F` is the fighter's
  known-spell count**, directly confirming "only unlocked spells for that
  character" from the task description.
- **case 1, Special Move**: if the active fighter is Harry, saves the
  current mode-stack context and pushes game mode `0x26` via
  `FUN_0802c7e0(0x26, 1, 0)` -- **this is the Folio Universitas**,
  matching `DAT_03003f3c == 0x26` already read by `FUN_0800f5f0` earlier
  in [`battle.md`](battle.md) (that function consumes the *result* of a completed card
  selection, not the menu itself -- the two findings now connect).
  Otherwise (Hermione/Ron) calls **`FUN_080105d8`** (see below) -- one
  shared 3-item-list screen for both, not per-character screens.
- **case 2, Informus**: gated by `DAT_03003f00 != 0xff` (a second,
  independent boss-style check from the graying check above -- same
  "boss" concept, different flag/slot). Sets the active fighter's
  `bSelectedActionIndex=0`, **`bSpellId=1`** (`Informus`'s own real
  `SpellId`, see [`battle.md`](battle.md)'s `bSpellId` writeup -- not borrowed from
  `Spongify`), `field_0x3b=4`, `bSpellLevel=0`, then `field_0x1070=6`
  (the same target-select screen spellcasting uses). `field_0x3b` is
  `BattleFighter+0x3B`, i.e. **`bPendingActionKind_candidate`** itself
  (`None`=`0`/`UseItem`=`1`/`SpecialMove`=`2`/`Flee`=`3`/`Informus`=`4`)
  -- the same field `DispatchPendingAction`'s top-level switch reads --
  so `field_0x3b=4` is simply this menu tagging the pending action as
  `Informus`, exactly like `Flee`/`UseItem`/`SpecialMove` each tag their
  own screens; a regular `Cast Spell` selection leaves it at `None` (`0`)
  instead (see `field_0x1070==2` above). There is no `Spongify`-borrowing
  or cast-disambiguation happening here at all -- `Informus` is a
  first-class pending-action kind with its own real `SpellId`.
- **case 3, Use Item**: `field_0x1070 = 7` (item-list screen), calls
  `FUN_08010660` to build the list.
- **case 4, Flee**: gated by `DAT_03003f24 != 0xff` (the same flag
  `FUN_080104a0` already used to gray this entry -- re-checked here
  too), sets `field_0x1070=0` (closes the menu) and `field_0x3b=3`.
- **case 5, Folio Bruti**: calls `FUN_0802c7c4(0x2d)` -- a mode-push,
  presumably to the Folio Bruti screen (not walked further here; see
  [`../formats/folio_bruti.md`](../formats/folio_bruti.md)).
- **case 6, Help**: saves mode-stack context and pushes game mode `0x44`
  via `FUN_0802c800(0x44, ...)` -- matches `DAT_03003f3c == 0x44`, the
  other mode value `FUN_0800f5f0` branches on, consistent with "opens a
  menu similar to the pause menu" from the user's description (not
  walked further).

Cursor movement and A/B dispatch both live in **`FUN_080101d0`**
(`0x080101d0`): reads a button-state bitmask `DAT_030034f0` (`0x10`=Down,
`0x20`=Up move the cursor by +-1 with wraparound via `FUN_08012e38`;
`0x01`=A/confirm, `0x02`=B/cancel dispatch through two 11-entry function-
pointer tables indexed by `field_0x1070`: confirm table at `0x0804e2ec`,
cancel table at `0x0804e318`). `field_0x1070`'s per-screen confirm
handlers: `1`->`0x08011bec` (above), `2`->`0x08012e54`, `4`->`0x08011eb8`
(below), `5`->`0x08011fa0`, `6`->`0x080120ec`, `7`->`0x08012eac`,
`8`->`0x08012178`, `9`->`0x0801320c` (all now walked below except `9`,
which has no function defined at that address at all -- `field_0x1070`
is never observed being set to `9` anywhere in this whole tree, so this
slot looks unreachable/dead from battle, not a tracing gap).

### The rest of the menu tree, PROVEN, and where the effect calls actually live

Walking every remaining `field_0x1070` confirm handler completes the
picture -- and the headline result is structural: **none of the menu's
own confirm handlers call the effect-trigger function
(`FUN_08018b70`) directly.** Every screen in this tree does the same
thing: write a handful of `BattleFighter` fields (`bSpellId`,
`bSpellLevel`, `bSelectedActionIndex`, `field_0x3b`, `bSlotParam`) and
set `field_0x1070 = 0` to close the menu. The actual effect calls all
happen afterward, in the object-tick execution layer
[`battle.md`](battle.md) covers (`TickPlayerActionState_candidate`'s
case `0x1a` =
`HandleScriptedDamageEvent_candidate`, and its `0x40000`/`0x8000`
`Object+0xc` flag branches) -- the menu and the effect system are fully
decoupled through these struct fields, confirming the split this
document's opening notes (menu-construction vs. action-execution are
genuinely two separate layers, not just two ends of one function).

- **`field_0x1070==2`** (`FUN_08012e54`, confirm handler for the
  per-character spell list opened by `Cast Spell`): `bSpellId =
  g_abSpellIdByCursor[fighterType*7 + cursor]` -- **`g_abSpellIdByCursor`
  (`0x0804e084`) is a per-character cursor-position -> real `SpellId`
  remap table** (already
  independently referenced by `FUN_08011520`'s label-draw code for this
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
  `bSpellLevel=0`, `bPendingActionKind_candidate=None` (`field_0x3b=0`). Then
  `FUN_080106ec(fighterIdx, cursor)` builds the next screen's list before
  an (unrecovered, but structurally `field_0x1070=5`) jump.
- **`field_0x1070==5`** (`FUN_08011fa0`, spell cast-level list --
  Uno/Duo/Tria): confirms the **spell cast-level list from the task
  description** and gates it on affordability --
  `fighter.wSp < g_awSpellMpCost[spellId*3+cursor]` beeps/refuses (SP,
  not MP, despite the field name -- consistent with `ShowBattleMessage`'s
  `SpCost`/`MpCost` case split in the message table below). Also refuses
  casting `Spongify` (`bSpellId==1`) while `DAT_03003f24==0xff` (the same
  boss-flag candidate used to gray `Informus`/`Flee`) -- **a boss fight
  blocks Spongify specifically**, a new, concrete behavioral fact. Sets
  `bSpellLevel = cursor`; most spell/level combinations proceed to a
  target-select screen (`field_0x1070=6`), except a few that execute
  immediately with `bSelectedActionIndex=0xfe` (self/no-target): `Fumos`
  (`bSpellId==8`) at level-1 (`Duo`, its party-wide cast, effect id `32`
  -- see [`battle.md`](battle.md)'s `Hidden` status bullet), `bSpellId==6`
  (`PetrificusTotalus`) + level-1, and (generically) any spell's level-2
  (`Tria`) cast **except `Glacius`** (`bSpellId==4`) -- i.e. by default a
  `Tria` cast doesn't need a target, with `Glacius` special-cased back
  into needing one. Not fully explained; flagged rather than
  over-interpreted.
- **`field_0x1070==6`** (`FUN_080120ec`, the enemy target-select
  confirm): after a vsync wait and some UI cleanup calls, simply writes
  `bSelectedActionIndex = cursor` and `field_0x1070 = 0`. Reads
  `field_0x1059` elsewhere in the target-select code in [`battle.md`](battle.md)
  (`g_pFightState->field_0x1059`, an array already used as an
  enemy-roster-index list by `ResolveSpellAttack`'s callers) --
  **this screen targets enemies.** Used by: `Informus`, Ron's `Stink
  Pellet`/`Wizard Cracker`, the spell target-select path above, and
  Hermione's non-self lectures.
- **`field_0x1070==7`** (`FUN_08012eac`, item-list confirm): checks
  `FUN_08026f34(cursor)` (item usable/available -- refuses with a beep if
  not), then `field_0x3b=1`, `bSpellLevel = cursor + 0x38` (matches
  `FUN_08011520`'s item-name text lookup, `FUN_08026b8c(cursor+0x38)`) --
  **items are addressed by the same `bSpellLevel` field spell levels
  use, offset by `0x38`** into `g_pBattleItemTable` (the item database
  below). Then calls `FUN_080107bc` (below) to
  pick a target.
- **`FUN_080107bc`** (`0x080107bc`), the shared **ally**-target-select
  *opener*: sets `field_0x1070 = 8` and reads `field_0x105d` (a
  different array from state 6's `field_0x1059`) for its list --
  **`field_0x1070==8` targets allies, not enemies.** Called from three
  places in this tree: `Use Item` (above), Hermione's non-"Proper Wand
  Technique" lectures (`Be More Careful`, `Good Study Habits` --
  consistent with them needing an ally target rather than an enemy), and
  the `bSpellId==8` special case inside the spell-level confirm above.
- **`field_0x1070==8`** (`FUN_08012178`, the ally target-select
  confirm): same shape as state 6's confirm -- vsync wait, writes
  `bSelectedActionIndex = cursor`, `field_0x1070 = 0` -- plus, if
  `field_0x3b==1` (the `Use Item` marker set above), calls
  `FUN_08026e2c(itemIndex, 1)` (presumably consumes/decrements the used
  item; not traced further).

`Use Item`'s actual effect resolution happens later, in
`TickPlayerActionState_candidate`'s `Object+0x60` sub-state `2`
(`FUN_08015f50`, `0x08015f50`): it only formats and shows the
already-computed damage/heal number (`DAT_0300274a`) via
`ShowBattleMessage`/`ShowFloatingDamageNumber_candidate` -- **it does not itself call
`FUN_08018b70` or compute an item's effect**, so an item's actual
gameplay effect (heal amount, stat boost, etc.) is set by something else
entirely, not walked here. This lines up with `g_pBattleItemTable`'s
`dwType`/`dwParam` fields still being undecoded (noted above) -- item
effects plausibly come from there rather than from the
`g_apEffectScripts_candidate`/opcode-`0x97` system spells and Special
Moves use.

### Special Move submenu (Hermione's 3 Lectures / Ron's 3 Special Moves), PROVEN

**`FUN_080105d8`** (`0x080105d8`) is the shared opener for both
characters' 3-item Special Move list: sets `field_0x1070=4`, builds
exactly 3 entries via `FUN_08011abc(3, i, fighterType, 1)` for `i` in
`0..2`. `FUN_08011520`'s `field_0x1070==4` case picks the label text base
by fighter type -- `fighterType==Hermione`: `textId = cursor + 0x8fa`
(`2298`-`2300`, already known to be `Be More Careful`/`Good Study
Habits`/`Proper Wand Technique`'s *string* ids in that order, per the
`g_abHermioneLectureEffectId_candidate` table in [`battle.md`](battle.md));
else (Ron): `textId = cursor + 0x8fd` (`2301`-`2303`, i.e. **cursor 0 =
Stink Pellet, cursor 1 = Wizard Cracker, cursor 2 = Stink Pellet 2**,
exactly the string-id order already on record).

**`FUN_08011eb8`** (`0x08011eb8`), this screen's confirm handler:

```c
BattleFighter *f = ...;
f->bSpellId = field_0x147c;   // the selected list index, 0-2
f->bPendingActionKind_candidate = SpecialMove;   // field_0x3b = 2
if (fighterType == Hermione) {
    if (f->bSpellId != 1)          // not "Proper Wand Technique"
        goto target_select;         // FUN_080107bc
} else /* Ron */ {
    if (f->bSpellId != 2)          // not "Stink Pellet 2"
        goto target_select;         // field_0x1070 = 6, same screen Informus uses
}
// self-cast, no target needed:
f->bSelectedActionIndex = 0xfe;
field_0x1070 = 0;                   // close menu, execute immediately
```

So **Ron's `bSpellId` is set directly from the menu cursor (0/1/2)**, the
same field spells use, and **cursor index 2 (`Stink Pellet 2`) is the one
self-cast/no-target move** -- `Stink Pellet`(0) and `Wizard Cracker`(1)
both require picking a target first.

### Ron's Special Move effect ids, resolved: `44`/`46`/`45`

`HandleScriptedDamageEvent_candidate`'s separate `Object+0xc` bit-`0x8000`
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
(`data/scripts/Effect44.txt`/`Effect45.txt`/`Effect46.txt`, currently
named `Effect44`/`45`/`46` in `tools/objscript/script_names.json`):

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
  `FightState+0x1480`, the exact same byte/family `ExtraExpBonus`
  (case `2`, bit `0x01`) and `GrantExtraXp` (case `3`, bit `0x02`) use.
  Mechanically distinct from both Stink Pellet variants (which both use
  the paralysis case `0x11`), confirming `Wizard Cracker` as a distinct,
  non-paralysis effect -- exactly the kind of "not paralysis" outlier
  the ordering evidence predicted. `Wizard Cracker`'s own move
  description text (`data/text/en_us.json` string ids `1725`/`2615`)
  states its effect as making the target creature drop an item; what
  reads `FightState+0x1480`'s bit `0x04` to grant that item is not
  traced.

Confidence: the menu-order/mechanism chain above (7-item table ->
confirm dispatch -> Special Move submenu -> `bSpellId` -> `0x8000`-branch
table read) is **PROVEN**; the specific `44`/`45`/`46` <-> move-name
assignment is **STRUCTURAL MATCH**, corroborated by both position
(matches the string-id order exactly) and content (the mechanically odd
one out, effect `46`, lands on `Wizard Cracker`, the mechanically odd one
out by gameplay behavior) -- not yet a live/dynamic confirmation the way
`ResolveMeleeAttack` got one.

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

All 16 are now named in `tools/objscript/script_names.json` as
`SpecialHarry<CardName>` (matching the `SpecialHermione*`/`SpecialRon*`
convention already used for the other two characters' Special Moves),
e.g. `SpecialHarryHorklumpSpores`, `SpecialHarrySnitch`,
`SpecialHarryUltimateMp`. See `../formats/object_script.md`'s Future
Work section (now marked done) for the prior open questions this
resolved.

**How the effect-id -> script trace works**, for reproducing/extending
this: `FUN_08018b70(effectId, ...)` (the anim/effect trigger already
documented above) calls `FUN_08018be0(effectId, ...)`, which spawns a
new `Object` and sets `Object+0x62 = effectId` and `Object+0x98` to a
generic dispatcher (`0x08018cc1`); `TickObject_candidate` then
interprets that object's script every tick via `FUN_08018cf8`
(`0x08018cf8`), which looks up the script buffer as
`g_apEffectScripts_candidate[Object+0x62]` --
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

### Battle item/equipment database -- `g_pBattleItemTable` (`0x08060EE4`)

`BattleItemEntry_candidate[132]`, stride `0x34`. Covers the game's full
equipment catalog (belts, gloves, boots, hats/caps, robes/cloaks,
potions) plus key items (Firebolt, Hedwig, Time-Turner, Trevor,
Scabbers, Crookshanks, The Monster Book of Monsters). See
[`../formats/save.md`](../formats/save.md) for the record layout, the
per-category string-id bases, and the item-id/quantity-array
correspondence.

**79 entries (`0`-`78`) are real**; index `79` is a dummy (its
`nNameTextId` is `0` and its three sprite pointers are byte-identical
clones of index `62`'s), and `80`-`131` are all zero. Both bounds are
real checks in code: `FUN_08026F48` walks `0`-`78` (`cmp r1, #0x4e`),
while `FUN_08026E58` walks the full `0`-`131` allocation (`cmp r3,
#0x83`) -- which matches `g_abItemQuantities`' own 132 slots before
`g_abEquippedItemIds` begins.

Every accessor in the `0x08026754`-`0x08026F7E` cluster addresses this
table as `0x08060EE4 + index*0x34 + fieldOffset`, selecting a field with
an immediate add rather than a typed struct access -- e.g.
`FUN_08026B8C` reads `+0x00` (`nNameTextId`), `FUN_08026CDC` reads
`+0x24` (`nType`) and `FUN_08026CF0` reads `+0x28` (`nParam`).

**Two nearby addresses are field pointers, not the table base**, and are
easy to mistake for it: `0x08060ED4` is `base - 0x10`, and `0x08060F08`
is `base + 0x24` (`&table[0].nType`), the literal `sub_08026870`'s
equipment-stat loop loads at `0x080268DC` -- with `0x08060F14`
(`base + 0x30`) used the same way right beside it.

### `ShowBattleMessage` -- case -> dialog text table

Text pulled from `data/text/en_us.json` by string ID.
`GetDialogText` (`0x080425E4`) returns a decompressed-text pointer (or
0 on failure); prototype `void *GetDialogText(int textId)`. Every call
site checked (24 across the ROM) is a genuine `bl`, not a tail-branch.

Several logical cases compile to more than one physical call site
(tail-duplication, up to 5 for case 6) -- every one of the 25 physical
`GetDialogText` call sites is individually annotated in Ghidra
(decompiler PRE_COMMENTs, visible inline in the decompile). Case
boundaries are read directly from the switch's real 18-entry jump table
(`0x080108D4`), which does not match the decompiler's own case-label
order.

| `messageCode` | Text ID | Text |
|---|---|---|
| 0 | `0x904` (static) | "The spell levels-up!" |
| 1 | `0x902` (static) | "Your escape has been blocked." |
| 2 | `fighterType*4 + 0x970` (dynamic) | e.g. "Harry performs a Special Move:" |
| 4 | `DAT_0804e344[fighterType]` (hero, indices 0-3) or `DAT_0804e344[rosterIndex+4]` (enemy, indices 4+) -- both branches read the SAME table, confirmed by reading the pool pointers at both call sites | hero: "Harry casts a spell:" / "Hermione casts a spell:" / "Ron casts a spell:" / "Buckbeak attacks!" (indices 0-3). enemy (sampled indices 4-7): "The ruby fire crab attacks!" / "The emerald fire crab attacks!" / "The sapphire fire crab attacks!" / "The Cornish pixie attacks!". A third call site (`0x08010c92`) passes the fighter struct pointer itself as the textId -- almost certainly dead/unreachable code, not resolved |
| 5 | attack-result text; sub-dispatched on `param2` -- see the table below | "Critical hit!", "@1 damage.", miss/poison/paralysis lines |
| 6 | fainted-message queue pop (`aFaintMessages_candidate[--bFaintMessageCount_candidate]`): `bEffectId<3` -> `0x8ec+bEffectId`; `==3` -> `0xa3d`; else -> `0x49e+bEffectId`; then unconditionally a damage-amount message, plus a miss-message variant | "Harry"/"Hermione"/"Ron" or "Buckbeak" (who fainted the target), then spell name e.g. "Diffindo"/"Glacius" (what fainted them), then "@1 damage." (two call sites, same text) or "The attack misses." |
| 7 | `fighterType + 0x973` (dynamic) | e.g. "Harry uses a potion:" |
| 8 | inner `switch(arg2)`: `0x38`/`0x39` -> `fighterType + 0x98d`; `0x3a`/`0x3b` -> `0xa27`; `0x3c` -> `fighterType + 0x985`; `0x3d` -> `fighterType + 0x981` | "Harry's SP are replenished." / "Your Magic Points are refilled." or "The party is revived!" / "Harry feels better!" / "Harry can move again!" (per fighterType) |
| 9 | `0x998` (static) | "@1 SP" |
| 10 | `0x999` (static) | "@1 MP" |
| 0xb | `0xa1e` (static) | "You are victorious!" |
| 0xc | `0xa1d` (static) | "You've been defeated." |
| 0xd | `fighterType==0xff` ? `0xa1c` : `DAT_0804e5ec[fighterType]` | "The opponent can't move!" (enemy), or "Harry"/"Hermione"/"Ron"/"Buckbeak can't move." (hero, per `FighterType`) |
| 0xe | `fighterType==0xff` ? `0xa20` : `fighterType + 0x981` | "The opponent can move again!" (enemy), or "Harry"/etc. "can move again!" (hero) |
| 0xf | `0xa3c` (static) | "The opponent's attacks are weakened." |
| 0x10 | `pFighters[arg3].fighterType + 0x991` (dynamic) | e.g. "Harry is hidden from view!" |
| 0x11 | `0xa3e` (static) | "The opponent is immune to paralysis!" |
| default | keyed on the *acting* fighter's `bFighterType`: `1` (Hermione) -> `arg2 + 0xa39`; `2` (Ron) -> `arg2 + 0xa36`; `0` (Harry) -> several sub-branches (`arg2==3`/`6`/`0xf` index different tables, e.g. `0xf` -> `... + 0xa2d`); else -> `0` | Hermione/Ron/Harry special-move descriptions, e.g. "Wow! Harry learned all possible spells!" |

Case 5 is the busiest of these and carries its own inner dispatch. Each
variant is rendered through `DrawTextLines_candidate` (`0x08020F44`, the
multi-line text-box drawer, see
[`../formats/text.md`](../formats/text.md)):

| Condition | Text ID | Text |
|---|---|---|
| `param1 > 999` | `0x995` (static) | "Critical hit!" |
| `param2 == 0` | `0x997` | "@1 damage." -- value is `param1`, or `param1 - 999` past the sentinel |
| `param2 == 1` | `0x996` (hero) / `0xa1b` (enemy) | "The spell misses." / "The attack misses." |
| `param2 == 2` | `DAT_0804e468[fighterType or rosterIndex+4]` | the target's name |
| `param2 == 3` | `0x976 + targetFighterType` | "Harry is poisoned." |
| `param2 == 4` | `0x97a + targetFighterType` (enemy attacker) / `0xa1f` | "Harry is paralyzed." / "The opponent is paralyzed!" |

### `messageCode` -- enum, `BattleMessageCode`

Applied to `ShowBattleMessage`'s first parameter, named from
the case table below: `SpellLevelUp=0, EscapeBlocked=1,
SpecialMoveAnnounce=2, SpecialAbilityText=3, ActionAnnounce=4,
CriticalHit=5, FaintResult=6, ItemUseAnnounce=7, StatusRestore=8,
SpCost=9, MpCost=10, Victory=11, Defeat=12, CantMove=13,
CanMoveAgain=14, AttackWeakened=15, Hidden=16, ImmuneToParalysis=17`.
`SpecialAbilityText` (3) doesn't get its own visible `case` label in the
decompile -- it shares a body with the switch's trailing default block,
a decompiler-view limitation, not a boundary error (confirmed correct
via the real jump table, see below).

### Functions called from `ShowBattleMessage`, partially identified

- **`PlaySoundEffect_candidate`** (`0x0803FF70`) -- called by
  `SpellLevelUp` (id `0x1a`). Looks up `DAT_08fb0cc4[soundId]` and
  passes it into `FUN_08047dfc`, which sits deep in Krawall's driver
  cluster (`0x08046000`-`0x08048000`, see `krawall.md`) and manipulates
  a full per-channel state array -- closer in shape to a Krawall
  module-switch (`kramPlayModule`-equivalent) than a one-shot SFX
  trigger.
- **`PrepareBattleMessageDisplay_candidate`** (`0x08012FD4`) -- called
  at the top of every `ShowBattleMessage` case. Draws/positions the
  message window and clears a status bit on every active fighter's
  sprite `Object` via **`ClearFighterObjectFlag_candidate`**
  (`0x08012CB4`), which indexes a 7-slot array,
  **`g_apFighterObjects_candidate`** (`0x03002668`, `Object*[7]`, likely
  one slot per active `BattleFighter`).
- `0x0804A2C4` (**`ThumbInterworkVeneer_bx_r1`**) is one of a family of
  generic ARMv4T-Thumb interworking veneers (`0x0804A2C0`-`0x0804A2E4`,
  one `bx rN` stub per register -- Thumb has no `blx reg`), documented
  in `krawall.md`; Krawall's mixer uses the same family. Reached from
  `TickObject_candidate`'s callback dispatch.

No `_candidate` suffix: every one of the 18 cases has real, verified
dialog text (case table below), including all 5 of case 5's inner
sub-cases. The one remaining gap -- case 4's third call site (`0x08010c92`) passing
the fighter struct pointer directly as a textId, likely dead code -- is
a single unexplained instruction, not a gap in the case identities
themselves, so it doesn't block dropping the suffix here.
