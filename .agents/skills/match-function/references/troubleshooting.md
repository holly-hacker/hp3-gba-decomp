# Mismatch troubleshooting

These are scoped hypotheses for the pinned agbcc, distilled from existing matches. Confirm
that the mechanism applies in the current dumps and rebuild. Example names point into `src/`
and `functions.us.cfg`; they are evidence to inspect, not templates to copy blindly.
Entry numbers correspond to the symptom routing table in SKILL.md.

## 1. Wrong semantics or field access

Trace operators, constants, offsets, loads/stores and call signatures against ROM assembly.
Fix known C-level errors before allocator experiments. Mnemonic equality does not establish
operand equality. Ghidra types can be stale; check headers and callers too.

## 2. Signedness and width

Extra `cmp #0`/`bge`/add/shift around division by a power of two can be signed rounding.
An unsigned value may remove it. Sub-word locals can introduce masks because Thumb
`PROMOTE_MODE` promotes them; prefer s32/u32 arithmetic and truncate at a genuine boundary.
Do not narrow merely to save a register. Inspect `ldr` versus `ldrb`/`ldrh`. Do give a call
result the width of the field it is stored in: a `u16` local for a call result stored to a `u16`
field supplies the `lsls`/`lsrs #16` before a later compare and changed reload choices at a
bitfield store (UpdateActorSpriteFrame, US 0x08002F28, `allocId`, `slotAllocId`; the callee
AllocObjVramTiles returns `u32`).

Promotion can also let `combine` fold `(a^b)&a` into one `bicsi3` when `a` is a named
sub-word local, where the same expression over array re-reads (HImode, `subreg`-wrapped)
doesn't fold. An unwanted `bic` versus a reference's `eors`+`ands` pair: drop the local,
re-read the array. Example: UpdateKeyInput, US `0x080254A8`.
To keep the ROM's `ldrsh` plus register mask for `s16field & 0xFF` (which otherwise narrows to `ldrh`),
assign inside the expression: `table[(angle = s.field) & 0xFF]`. Example: ProcessBuckbeakMinigameFrame.

## 3. Cached field/address

Repeated use of one loaded register can suggest a cached field; repeated address formation
can suggest direct access. Test a meaningful local versus direct field use. Compiler
optimization means neither observation uniquely identifies the original source.

Across a store, types decide: agbcc's `-O2` enables type-based aliasing, so CSE keeps a loaded
value past a store of an unrelated type. `c-common.c:c_get_alias_set` gives alias set 0, which
conflicts with every store, to char types, bitfields, whole-struct copies and any access
reached through a union member. A ROM reload after an unrelated store (`str r0, [g, #16]; strh;
ldr r0, [g, #16]`) points to such an access. By the same rule, a build reload the ROM lacks can
come from a `u8` pad/cast or union the original did not use. Compiling the `.i` with
`-fno-strict-aliasing` confirms the mechanism; then find which store or load needs the set by
retyping one side at a time. Example: QueueBattleBgLoad, US `0x0801B4BC`, stores the tilemap
size through full-width bitfields (`u16 wWidth : 16`, BgTilemapBuffer).

## 4. Branch layout and expression order

Try the complementary outer condition with arms exchanged when fallthrough differs.
Check operand evaluation order and separate an embedded assignment from its comparison;
a comma expression is another diagnostic form. Negating a condition alone may canonicalize
back to identical output. Example: ResolveEnemyAttack.
An early `return NULL` lands opposite its source position when the other arm has no branch:
write `if (p != NULL) { ...; return p; } return NULL;` for a NULL-first ROM (CreateScriptEmitter8).
Arguments and operands expand left to right, and combine places a folded load at its later
use. A load the ROM performs before an earlier argument or a preceding constant set was
assigned to a local in its own statement first (TickBattleMenuInput's `lastRow`;
ShowBattleMessage's `fighterType` before `textId = 0x996`, US `0x080101D0`, `0x08010864`).
`fold` moves a literal to the call or sum it can join (`rand + (k << n) + 12` adds 12 to `rand` first);
a ROM keeping the literal elsewhere had separate statements (TickServePumpkinJuiceCustomer, US `0x0803494C`).

## 5. Switch shape

For linear compares versus range checks/jump tables, inspect explicit case coverage and
source case order. Enumerating adjacent enum values can expose a dense range; the final
case may affect fallthrough. Keep behavior for default/out-of-range inputs faithful.
Investigate tail merging separately from dispatch. Do not add cases without semantic grounds.

## 6. Unexpected spill

Inspect lreg/greg allocation priorities and live ranges before random statement ordering.
A competing pseudo can change the winner, but artificial competition is not acceptable
source. Use a short permuter experiment only to discover a lead, then seek a natural rewrite.

## 7. Redundant check disappears

`jump.c` threading can fold a conditional reached through a single-use label. Shared incoming
edges and fallthrough order can preserve the check. ResolveEnemyAttack's hit/miss split is a
worked example: swapping the outer arms mattered; condition inversion alone and one explicit
shared-label rewrite did not. Verify label use counts in the current RTL.

## 8. Two locals, one register

Try merging same-purpose temporaries with disjoint lifetimes when the ROM reuses a register.
Do not infer source identity solely from register reuse. Keep unrelated semantic roles separate
unless allocation requires otherwise, as below.
A second local can change allocation even when it seems to be a harmless copy.
When a short-lived temporary takes its source's register (`ldrh r0; lsls r0, r0, #2`) but the
ROM's is fresh, `local-alloc.c:combine_regs` tied them because the destination was block-local.
Reusing a variable that lives across blocks breaks the tie, even across unrelated roles
(DecompressHuffTree, US 0x08024EDC, computes the tree size in `bits`).

## 9. Constant allocation ties

Inspect `global.c:allocno_compare`: refs, size, live_length and allocno order affect priority.
For equal refs/size, shorter live_length can win; tied ordering matters. Measure in lreg/greg.
A bit-field store's expanded mask can affect flow-time liveness even if combine removes it;
a byte-pointer store takes another expansion path. Use this to investigate types, not to
justify unexplained casts. See compiler-investigation for pseudo-to-hard-register mapping.

A plain `(x & ~3) | (y & 3)` also narrows `~3` to `movs r0, #0xfc`; a real bitfield store never
narrows and always builds it as `movs r0, #4` + `negs r0, r0`. The latter in the ROM means a
real C bitfield -- overlay one on the byte via a local pointer cast. Example:
SetActorAffineTransform, US `0x0800366C`.

For an equal-refs tie between two same-shaped pseudos, the one whose last use comes first
in source wins the shorter live_length and the preferred hard register. Reorder the two
independent statements that consume them (not the loop). Example: UpdateKeyInput's
loop-setup registers, US `0x080254A8`.

Two locals set to the same constant back to back: `cse.c:make_regs_eqv` sets the one whose
last mention comes later in the source (`REGNO_LAST_UID`) to the constant and makes the other
a copy of it, and the copy's refs can decide the tie. Assignment order does not matter; make
the local the ROM sets to the constant the one mentioned last (DecompressBgTile, US
`0x08006300`, takes `symbol = code;` at the loop exit so `length` outlasts `code`).

## 10. Shared tail / apparent need for goto

`jump.c:find_cross_jump/do_cross_jump` can merge suitable jump-ending blocks; duplicated
source does not guarantee merging. Re-derive the true outer split first. In ResolveEnemyAttack,
“both flags” versus the remaining combinations permits a shared DefenseBoost recheck inside
one else arm. A goto matched too, but structured control flow expressed the same join.

Cross-jumping runs after register allocation, so duplicated source also changes allocation:
each copy's references count toward the variables it uses. When a goto-joined draft matches
except for two callee-saved registers swapped, write the shared block out in each branch.
Example: HandleChestTouch, US 0x0800BF20 (the parameter took r4 only with two copies).

The same copy can account for dead `movs rN,#0` sets (some in a high register) that the
ROM keeps: each copy's u8 field stores share one zero mask register through the tail. A size
argument loaded before the data pointer needs a local read before the call, scoped to each
copy. Example: TickBgTileAnimations, US `0x0800A610`. In ConfirmSpecialMoveMenu, US
`0x08011EB8`, an else-if chain instead joined at the shared block and lost the zero in `r6`.

A merged tail's register convention is set by whichever branch reaches it needing zero
fixup moves; the other branch pays the reconciling `adds`. Fix that branch's own tie
(entry 9) first -- the tail's ordering won't resolve in isolation. Example: UpdateKeyInput,
US `0x080254A8`.

## 11. Guard macro prevents merging

`do { ... } while (0)` emits loop notes. `cse.c:cse_end_of_basic_block` can stop at
`NOTE_INSN_LOOP_END`, preventing traversal needed for a shared tail. Desugar an existing macro
as an experiment; a bare block has different semicolon/if-else safety. Example:
TickBattleTurnStateMachine's TRANSITION_TO. This does not justify adding inert wrappers.

## 12. Indexed-loop giv synthesis: pointer placement or a folded constant

An indexed loop lets `loop.c:strength_reduce/emit_iv_add_mult` synthesize a pointer induction
variable in the preheader, after a duplicated exit test. A handwritten walking pointer may
initialize before the guard -- test `p[i]` vs `*p++` based on the target (memset, US
0x0802C450). Or it may fold a field-offset constant into the giv's initial value, leaving
candidate short a per-iteration reload+add the ROM repeats (`.loop`: `mult STRIDE add CONST`)
-- try adding the constant to an already-formed `base+i*stride` sum so the giv reads `add 0`
(ExitBattle, US 0x0800DE50). Let strength reduction happen when the target's shape matches it.
The same switch affects a struct base register copied late in a block (`adds r4, r0, #0`): an
indexed global access in the loop keeps that gcse PRE copy, walking pointers let loop.c drop it
(SubmitSerialMessage, US 0x0803F438).
A pointer walking down from `&a[N - 1]` with a signed `cmp ptr, base` came from an up-counting
`for (i = 0; i < N; i++)` that loop.c reversed; written counting down, the giv was "not worth
while" and the counter stayed (ClearItemInventory, US 0x08026D58).
A counter the ROM keeps unreduced and stores to a global once after the loop, through the address
register of an earlier store, was the global field itself (`for (g.n = 0; src[g.n] != END; g.n++)`):
`loop.c:load_mems` keeps it in a new register that is never a biv. load_mems refuses when a loop
store or read may alias the field; under strict aliasing an `int` field shares the `u32` elements'
alias set, a `long` does not (OpenItemListFromIds, US 0x08027B44). `-fno-strength-reduce` on the
`.i` checks the loop body quickly.

## 13. Value fails to survive calls

Two distinct mechanisms can interact. `reload1.c:reload_cse_move2add` can reuse a hard-register
constant; stepwise `len += 0xf; len &= ~0xf;` may expose reuse that a combined expression
does not. Separately, `flow.c` weights refs by loop depth. A label/goto loop lacks the loop
notes of a for/do loop and can change priority. Inspect both before combining fixes.
Example: AllocZeroed, US 0x0802C2EC; a real do loop allowed len to win r8.

## 14. Mask/value get opposite registers

CSE canonicalizes commutative operands, so swapping spelling/declaration order can converge
to the same RTL. `mask &= value` makes the mask the destination and can change regmove's
two-address choice. Verify priorities and reload order. Examples: InitPlayerBattleActor and
InitializeBattle's `clearMask &= flagsBeforeClear`; four simple order permutations converged.

## 15. Merging locals changes an unrelated tie

Merging same-role counters at disjoint sites combines refs/live_length and can affect a third
pseudo's conflicts. Inspect measured allocation before and after. The merge is legitimate
only if the roles fit; borrowing a counter for a boolean or timer is not a natural solution.

## 16. Expected loop copy collapses

`gcse.c` copy propagation may merge identical preheader/body assignments. Separate meaningful
carried/next values can preserve copy-in/copy-out. Inspect `COPY-PROP` messages in the gcse
dump; disabling gcse is a diagnostic probe. Different source expressions alone are not proof
of different RTL. Example context: AddPlaytimeDelta's loop investigations. For a loop that
has an extra pre-loop copy of its exit test instead, see entry 28.

## 17. Copy fix triggers unrelated strength reduction

A clean `plus carried -30` may become a basic induction variable and pull another expression
into an unwanted accumulator. Test `nextValue = carried; nextValue -= 30;` and inspect
`loop.c:basic_induction_var`. Combine may merge a small +1 differently from -30 due to Thumb
immediate constraints; confirm the observed asymmetry in dumps instead of generalizing it.

## 18. Invariant load lands across the wrong loop boundary

A preheader statement can give gcse PRE an insertion point for another load. Inlining a
constant may remove that block; later `loop.c:move_movables` can place the load differently.
Example: AddPlaytimeDelta, US 0x0800C6EC; overflow and borrow loops used different forms.
Inspect each loop separately even when source looks symmetric.

## 19. Byte count matches but a loop-carried update is out of order

Two loop-carried values share a step (e.g. a destination counter and a second loop's own
index) and the update sequence is swapped relative to the ROM despite equal size. `loop.c` may
attach each giv's update to whichever biv's increment it follows in source; test moving the
shared counter into that loop's increment clause (`pendingI++, i++`) instead of the body or an
index sum (`[i + pendingI]`). Example: ExitBattle, US 0x0800DE50 loop 2.

## 20. Global member address is pooled as `sym+const` instead of `adds #const`

`p = &g.array[i]` folds the member offset into the literal pool (`.word g+0x1c`). Reading and
writing `g.array[i]` directly, in both the compare and the store, keeps the plain symbol in the
pool and emits `adds rX, #offset` after the index shift. Example: UpdateBuckbeakMinigame,
US 0x08009BE0. Likewise, indexing with a variable the branch has already fixed (`table[kind]`
inside `if (kind == 1)`) gives `ldr base; adds #offset` where `table[1]` pools `base+offset`
(HandleChestTouch, US 0x0800BF20).
An index with a constant folds into the pool only in an address (`&a[i + 4]`); `a[i + 4].field`
keeps `(i + 4) * size`. When both forms in the ROM pool `a+const` and share `i * size`, the
records are a separate array starting there (SetBattleMenuIconState, US `0x08011ABC`, indexes
`g_aBattleMenuIconAssets`, which follows two face tables).

## 21. Switch layout

- Case bodies are emitted in source order. A jump table whose targets are out of numeric order
  means the source cases were written in that order (Wizard Cracker Pop-it update: 5, 0, 1, 6,
  7, 2, 3, 4).
- `case 0: X; break; case 1: X; break;` gives `cmp #1; beq; cmp #1; blo` (Harry vs Dementors
  init). `case 0: case 1:` merges into one range test (`bls`).
- A chain of `if / else if / else` on one value is not a `switch`, and swapping `== 0` for
  `!= 0` swaps which block falls through (Wizard Cracker Pop-it pause and results menus).

## 22. Argument extension follows the callee's declared type

Passing an `s16` field as an argument loads with `ldrh` when the parameter is `u16` and with
`ldrsh` (no extension) when it is `s16`; a cast at the call site does not change this. The
SetActorAffineTransform angle parameter is `s16` for that reason.
A constant argument follows the same rule: `-0x100` to a `u16` parameter is `0xFF00`
(`movs`/`lsls`), to an `s16` parameter the pooled SImode `0xFFFFFF00` (SetActorOrbitAngleVels).

## 23. Array base loaded early and hoisted instead of a neighboring constant

`arr[s.count++] = x` with `arr` a separate symbol loads `arr` before the count update, so
`loop.c` hoists it (longer lifetime) and the struct base stays in the loop. If the ROM loads the
array literal after the count store, the array is likely a member of the same struct
(`s.arr[s.count++]`, pooled as `s+offset`). The hoisted base then changes global allocation and
exit-test duplication. Example: TickActorList, US 0x08000918.

## 24. Bitfield read emits `ldr` instead of `ldrb`

Casting a byte to a bitfield struct (`((Bits *)&obj->b)->f`) reads in SImode because agbcc
structs are word-aligned. A bitfield member declared directly in the containing struct reads
with `ldrb` and writes with `ldrb`/`strb`. The base type still matters: a single-use compare of
a `u8` field at bit 0 folds to `ands`, a `u32` field keeps the ROM's `lsl`/`lsr` pair. Test both.
Examples: `Actor.bDrawLayer` (u8, TickActorList), `Actor.bAffineSlotState` (u32,
TickFighterAttackAnimState).

## 25. One shared local versus per-site locals

A local assigned at several disjoint sites is one pseudo: it sums refs and live_length, so its
`allocno_compare` priority differs from block-local copies, it may take a callee-saved register,
and it moves neighbouring pseudos between hard registers (including reload spill-register
choice). When values at disjoint sites land in different registers than the ROM, test each site
as block-local versus one function-level variable, and flip the whole group together: single-site
flips changed nothing while the group flip matched. Examples: InterpretActorScript, US
`0x08018CC0`, opcodes 0x27/0x2B/0x83/0x84/0x85/0x97/0x9D-0xA0 share one signed index;
UpdateActorSpriteFrame, US 0x08002F28, needs `record`/`frameData` per site.
The shared local can be a two-word struct copied whole (`pos = pTarget->pos`, then
`dst.x = pos.x; dst.y = pos.y`) instead of two scalar temporaries; flipping both sites matched,
either alone did not. Example: TickCameraFocus_candidate, US 0x0800A03C.

## 26. Base and index of an address add swapped (`adds rD, rBase, rIdx`)

When only the operand order of `base + index` differs, and with it which register the sum
reuses, check how the sum is expanded; reordering the C spelling does not change it.
`optabs.c:expand_binop` swaps commutative operands only when the target is the second operand
or the first is not a register. With a pointer base, `base[i]` and `*(base + i)` expand to
`(plus idx base)`, while `p = base; p += i; *p` expands to `(plus p idx)` with `p` as the target.
Examples: TickParticleLayer and BucketParticlesByPriority (US 0x080317EC, 0x08030C00),
`entry = g_apParticlesByPriority[n]; entry += i;`. Conversely, a pointer plus offset loaded from
a field expanded base first in either spelling, and an integer sum
`*(u16 *)((u32)ofs + (u32)ptr)` put the index first (DrawParticle, US 0x0803186C).
To get the index computed first but the base as the sum's target, add a byte offset to a
byte-pointer base: `*(u16 *)((const u8 *)&nodes[n] + ((bits & 1) << 1))` (DecompressHuffTree,
US 0x08024EDC).
For an element of a pointer member, `fighter = &s->p[i]` loads the index first and adds
`base + index`; reading `s->p[i].field` directly loads the base first and adds
`index + base` (the address is canonicalized with the multiply first). OpenBattleTopMenu, US
`0x080104A0`, accesses `g_pFightState->pFighters[i]` directly; TickBattleMenuInput keeps a pointer.

## 27. Reload registers (r0-r2) shifted from some point on

`reload1.c:allocate_reload_reg` rotates through reload registers (`last_spill_reg`), so one
extra or missing reload earlier in insn order shifts every later choice. Causes: a branch
written out twice and merged by cross-jumping after reload (entry 10), or a REG_EQUIV
constant pseudo left unallocated and rematerialized just before its use. Example:
WriteRoomBgTile_candidate, US 0x0803DD7C.

## 28. Rotated loop has an extra pre-loop copy of its exit test

The ROM enters the loop with `b test`; the build also has a copy of the test before it.
`jump.c:duplicate_loop_exit_test` copies the test, and cross-jumping removes the copy only if
both are register-identical. A `u16` index compared with `0xFFFF` builds the constant as
HImode, so the copy and loop.c's hoisted constant land in different registers. Declare it
`u32` (still loaded with `ldrh`). Check `.greg` for two `const_int 65535` pseudos. Example:
ReleaseBgTileCacheEntry, US 0x0803DF18.
The copy also stays when the loop ends an `if` arm whose exit label is followed only by the
jump past the `else`; ending that arm with its own `return` let cross-jumping remove it
(MoveMemory, US `0x0802C174`, whose forward branch is CopyMemory's body).
A pre-loop copy that also holds exit work, folded to constants (`movs r0, #0; b store`), is a
`for (;;)` starting with `if (...) { X; break; }`: the copy includes X (JumpToScriptLabel).

## 29. Two-address op with a copy in front of it (`adds rD, rS, #0; eors rD, rC`)

A byte field read directly (`pCycle->bFlags & X`, `pCycle->bFlags ^= X`) is a QImode load.
CSE/PRE share that load across blocks, so the op's source is a `(subreg:SI (reg:QI t))`
operand; `regmove.c` only ties `REG` operands, so the result keeps its own register and reload
emits the copy. Copying the field into a `u32` local ties them (`eors rS, rC`, no copy). If the
compare and the op sit after an if/else that only picks the operand, write them out in each arm:
`jump.c` cross-jumping merges the identical tails after reload, which also yields the
`b`-to-shared-`cmp` shape. Example: StepColorCycle, US `0x0800D7E8`.

## 30. Inlined helper: copy the standalone copy's exact shape

When the ROM has a standalone function whose body is also inlined into a larger function (here a
callback holding the same timeout test), match the standalone copy first and inline that exact
source. `return a > 600;` and `if (a > 600) return 1; return 0;` compile standalone to different
code, and inlined twice they hoist the literal differently: the `if`/`return 1`/`return 0` form
shares one constant register hoisted out of both loops in `loop.c` pass 1 (after the address
copy); `return a > 600;` or a `timeout` local leaves the constant first or per loop. Example:
RunSerialExchange, US `0x0803F52C`, inlines the test that `SerialPhase2` (`0x0803FBC0`) holds.

## 31. Load immediately before a constant store (`ldrh rX, [p]; strh rZero, [p]`)

agbcc emits a dead load for a plain `a[i] = 0` on a volatile array element, but not for `*p = 0`
through a volatile pointer. Keep the field volatile and the indexed store. Example: InitSerial,
US `0x0803F0A8`.

## 32. Constant kept in a register for compare and store (`cmp r2, r1`; `str r2`)

`bank = 2; if (bank != s->field) { s->field = bank; ... &table[bank] ... }` keeps the constant in
a register when `bank` is also an index. Written with the literal (`field != 2`, `table[2]`) the
compare takes an immediate and the address folds into the pool. Example: ProcessBuckbeakMinigameFrame,
US `0x08009144`.
A constant stored as a stack argument from a callee-saved register set at the function's
first instruction came from a local initialized to it at its declaration: CSE reuses that
register for the store. DrawBattleMenuText's `u8 spellId = 0` (JP `0x08011520`).

## 33. Constant argument materialized after the stack-argument stores

A literal register argument above 255 (`movs`+`lsls`) is forced into a pseudo while arguments
are evaluated, so it precedes the stack stores whatever locals or casts surround it. When the ROM
loads it just before the call, the argument was a parameter of an inlined helper: inline expansion
substitutes the constant at the load. Move the call into a `static inline` helper taking that
value. A helper index parameter also reproduces a constant that stays on one term of an index
expression, which `i = K` assignments only imitate. Example: DrawChooseCharacterSelection, US `0x0800C3FC`.
The same helper also stops loop.c hoisting: identical constant movables are combined into one
pseudo that takes a register early, but `integrate.c:try_constants` folds the constant into
`(plus reg const)` when inlined, so there is nothing to hoist (CopyBgTilemapRectByCell, US `0x08006A98`).
Conversely, a constant the ROM holds in a register set at the start of an inlined body (shared
with other uses of the same value) was passed to a word-sized helper parameter: with `u8 row`
the `0` folded into each use, with `u32 row` it stayed one pseudo, which CSE also reused for
the loop's `0 < count` test (ConfirmBattleTopMenu's Cast Spell case, US `0x08011BEC`).

## 34. Parameter copy and base register kept as separate pseudos

When the ROM leaves a parameter's entry copy (`adds r4, r0, #0`, or `adds r0, r2, #0` in front of a
`muls`) and parks a value in a callee-saved register that nothing needs to survive a call, combine
did not fold the copies: the parameter pseudo is set more than once. Assign the result back to the
parameter (`pTilemap = pTilemap + y * stride + x; return *pTilemap;`). A fresh local folds away.
Example: GetTilemapCell, US `0x08007774`. The "set more than once" part is inferred from the RTL
dumps, not read out of `combine.c`.

## 35. Clamp written as a ternary versus set-then-override

`v = 32; if (x <= 31) v = x;` loads `x` after `movs #32`. The ROM order `ldrh; movs rV,#32; cmp;
bhi; adds rV, r0` is `v = x <= 31 ? x : 32;` with the field read in all three places.
Example: CopyLoadedTilemapToBuffer, US `0x080078E8`.

## 36. Insns that combine deletes still count

`insn_count` in `loop.c:move_movables` and `REG_LIVE_LENGTH` in `flow.c` are computed before
combine. A hoist is made only when `threshold * savings * lifetime >= insn_count` (threshold 26
without calls), so deleted zero-extends can keep a 1x1 movable in the loop: a `u16` cell built in
two steps (`cell = *p & 0xFFF; cell |= pal << 12; *p++ = cell;`) takes the outer loop from 24 to 28
insns (check the `Loop from ... real insns` lines in `.loop`; SetTilemapRectPalette, US
`0x080076A4`). The same effect lengthens a pseudo and drops its `allocno_compare` priority below a
close neighbour: `s32 length` with `length / 2` (signed-rounding insns, removed later) put
LoadGraphicBlobTiles's pDest ahead of length (US `0x080065D4`).
A giv that the ROM strength-reduces but the build recomputes shows in `.loop` as `giv of insn N not
worth while, A vs B` (B is insn_count): `(s16)(pActor->pos.x >> 16)` and `pActor->pos.x >> 16`
both become `ldrsh`, but the cast's extra insns pushed a loop from 120 to 131
(UpdateDementorMinigameDementors, US `0x0801E8CC`).
`local-alloc.c:update_equiv_regs` also doubles `REG_LIVE_LENGTH` for each constant set seen before
a non-constant one (`pending = 0x100` at init and reset, then `pending = node`: x4; compare `.flow`
with `.lreg`). Lengthen the competitor instead: a `u16` temporary for a halfword store adds HImode
insns (DecompressHuffTreeTile, US `0x08024F80`). `gcse.c` PRE's loop-top temporaries for
`p++`/`count--` rank the same way, so the decrement's source position picks which one takes the
register reload later spills (BuildHuffTreeTileOffsets, US `0x08025024`).

## Candidate acceptance and cleanup

A diff improvement is evidence, not permission to land a proxy. Selective one-field inline
wrappers, unrelated-local reuse, empty conditions and dummy loops need a natural explanation
or replacement. Keep useful experimental evidence outside production C. Compare output with
and without suspicious constructs; compare text/relocations rather than whole object metadata.

After matching, try real arrays, typed fields, multiplication and necessary casts only.
Renames usually preserve output; removing locals or changing types/statement structure can
recolor distant code. Same machine mode does not prove two C types are interchangeable.
Always rebuild. Zero mnemonic groups, equal size and a permuter score are all insufficient
as exact-byte or semantic acceptance criteria.
