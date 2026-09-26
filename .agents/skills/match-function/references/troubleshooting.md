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
Do not narrow merely to save a register. Inspect `ldr` versus `ldrb`/`ldrh`.

Promotion can also let `combine` fold `(a^b)&a` into one `bicsi3` when `a` is a named
sub-word local, where the same expression over array re-reads (HImode, `subreg`-wrapped)
doesn't fold. An unwanted `bic` versus a reference's `eors`+`ands` pair: drop the local,
re-read the array. Example: UpdateKeyInput, US `0x080254A8`.

## 3. Cached field/address

Repeated use of one loaded register can suggest a cached field; repeated address formation
can suggest direct access. Test a meaningful local versus direct field use. Compiler
optimization means neither observation uniquely identifies the original source.

## 4. Branch layout and expression order

Try the complementary outer condition with arms exchanged when fallthrough differs.
Check operand evaluation order and separate an embedded assignment from its comparison;
a comma expression is another diagnostic form. Negating a condition alone may canonicalize
back to identical output. Example: ResolveEnemyAttack.

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
Do not infer source identity solely from register reuse. Keep unrelated semantic roles separate.
A second local can change allocation even when it seems to be a harmless copy.

## 9. Constant allocation ties

Inspect `global.c:allocno_compare`: refs, size, live_length and allocno order affect priority.
For equal refs/size, shorter live_length can win; tied ordering matters. Measure in lreg/greg.
A bit-field store's expanded mask can affect flow-time liveness even if combine removes it;
a byte-pointer store takes another expansion path. Use this to investigate types, not to
justify unexplained casts. See compiler-investigation for pseudo-to-hard-register mapping.

A plain `(x & ~3) | (y & 3)` also narrows `~3` to `movs r0, #0xfc`; a real bitfield store never
narrows and always builds it as `movs r0, #4` + `negs r0, r0`. The latter in the ROM means a
real C bitfield -- overlay one on the byte via a local pointer cast. Example:
SetObjectAffineTransform, US `0x0800366C`.

For an equal-refs tie between two same-shaped pseudos, the one whose last use comes first
in source wins the shorter live_length and the preferred hard register. Reorder the two
independent statements that consume them (not the loop). Example: UpdateKeyInput's
loop-setup registers, US `0x080254A8`.

## 10. Shared tail / apparent need for goto

`jump.c:find_cross_jump/do_cross_jump` can merge suitable jump-ending blocks; duplicated
source does not guarantee merging. Re-derive the true outer split first. In ResolveEnemyAttack,
“both flags” versus the remaining combinations permits a shared DefenseBoost recheck inside
one else arm. A goto matched too, but structured control flow expressed the same join.

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
of different RTL. Example context: AddPlaytimeDelta's loop investigations.

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
pool and emits `adds rX, #offset` after the index shift. Example: UpdateHippogriffGlideMinigame,
US 0x08009BE0.

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
SetObjectAffineTransform angle parameter is `s16` for that reason.

## 23. Array base loaded early and hoisted instead of a neighboring constant

`arr[s.count++] = x` with `arr` a separate symbol loads `arr` before the count update, so
`loop.c` hoists it (longer lifetime) and the struct base stays in the loop. If the ROM loads the
array literal after the count store, the array is likely a member of the same struct
(`s.arr[s.count++]`, pooled as `s+offset`). The hoisted base then changes global allocation and
exit-test duplication. Example: TickObjectList, US 0x08000918.

## 24. Bitfield read emits `ldr` instead of `ldrb`

Casting a byte to a bitfield struct (`((Bits *)&obj->b)->f`) reads in SImode because agbcc
structs are word-aligned. A `u8 f : n` member declared directly in the containing struct reads
with `ldrb` and writes with `ldrb`/`strb`. Example: `Object.bDrawLayer` in TickObjectList.

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
