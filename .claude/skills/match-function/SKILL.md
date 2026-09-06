---
name: match-function
description: Efficient workflow for getting a hand-written C function to compile byte-identical to a real compiled ROM function with agbcc (GCC 2.9-era). Use when decompiling/matching any single function in this project, especially ones that resist an obvious first attempt.
---

# Matching a function against agbcc's real output

Distilled from matching `ResolvePlayerAttack` (0x08017C24, US), which went from a
first-pass logic-correct draft to byte-exact over many iterations. That took far
longer than it should have because several of the steps below were discovered
late. Do them in this order next time.

## 0. Before writing any C

Confirm struct offsets and control flow against `full_disasm.s` **instruction by
instruction**, not just a fresh Ghidra decompile skim. Ghidra can have stale
enums/types (check `docs/` for known DB issues) and mis-mark ARM/Thumb or
data-as-code. `full_disasm.s` is ground truth on any disagreement. Get this
fully right before writing C — logic bugs found later are much more expensive
to untangle from compiler-quirk noise.

## 1. Stop trusting raw byte-size as the closeness metric

Total object size is not monotonic with correctness: a structurally-wrong
candidate can hit the target byte count by coincidence, and a genuine fix can
move the byte count *away* from the target while making the candidate strictly
closer in every real sense. Use `tools/opcode_diff.py <ver> <function-name>
<object-file>` as the actual metric instead of size, from your very first
build:

```bash
nix develop -c python3 tools/opcode_diff.py us ResolveEnemyAttack build/us/obj/r006_ResolveEnemyAttack.o
```

It pulls the real function's extent straight out of `build/<ver>/full_disasm.s`
(between its `thumb_func_start`/`arm_func_start` label and the next one), diffs
mnemonic sequences against the candidate object with Python's
`difflib.SequenceMatcher` (so insertions/deletions realign instead of
cascading into a wall of noise), and normalizes cosmetic-only differences
before counting groups: a trailing `.n` on any mnemonic (narrow-encoding
annotation some disassemblers print and others don't), and the ARM
condition-code mnemonic aliases `bhs`≡`bcs`/`blo`≡`bcc` (literally the same
encoded condition, different assembler convention).

It reports "N real (non-cosmetic) opcode-diff groups", not "N bytes off".
Recount after every change — a fix can trade one group for a different one at
the same total, which is easy to mistake for "no progress" if you're only
watching size. Note it's mnemonic-level only: two operands of the same
mnemonic using different registers show as "equal" even though the bytes
differ — a 0-group report is necessary but not sufficient for a real match,
so still confirm with `just compare <ver>` (whole-ROM `cmp`) or
`tools/diff_region.py <ver> <name>` (byte-level, single region, works once the
region is the right size) before calling a function done.

Also check for an unwanted stack spill after every change (`sub sp`/
`str .*\[sp` in the disassembly) — a spilled variable that shouldn't be is a
strong, cheap correctness-adjacent signal that something regressed.

## 2. Fix gaps one class at a time, cheapest first

In practice these fell into recognizable buckets, roughly in order of how
mechanically understandable (and thus how worth attacking directly) they are:

1. **Genuine C-level bugs in your draft** (wrong operator, wrong constant,
   wrong struct offset). Fix these first, obviously — sort them out via
   careful disasm tracing per step 0, not by trial and error.
2. **A local variable's *type* not matching the real value's actual
   signedness/width.** E.g. a signed `int` where the real value is logically
   unsigned forces agbcc to conservatively emit a sign-correction/rounding
   sequence before a shift, that a real unsigned type doesn't need at all.
   Spot this by looking for a `cmp #0`/`bge`/`adds`/shift correction sequence
   the real disasm doesn't have around a division-by-power-of-2.
3. **A local variable caching a field that real also caches** (proven by the
   real disasm reusing one register across multiple field reads instead of
   re-deriving the address each time) — a legitimate optimization to mirror,
   not a hack. Conversely: **a local variable caching something real does NOT
   cache** (real recomputes the address fresh at each use) is actively wrong to
   introduce, even if it doesn't affect byte count with your current
   compiler flags — it will diverge from real's shape as soon as anything
   else about the function's register pressure changes.
4. **Branch/block-layout mismatches** — same condition, but real puts the
   `if`-body as the forward-branch-away target and the `else`-body as
   fallthrough (or vice versa). Try a De Morgan inversion of the *condition*
   (not just wrapping the existing bodies in `!(...)`, which often folds back
   to the same shape) combined with detaching any embedded assignment from
   the comparison via a comma expression, so the assignment and the compare
   expand as separate operands instead of one fused expression. Verify
   operand order in the comparison too — it's not just a style choice, it can
   change which operand's address computation gets scheduled first.
5. **Switch-statement shape mismatches** (cross-jump-merged tail instructions
   that real duplicates per case; a linear-compare vs. range-check vs.
   jump-table shape for a small/sparse `switch`). For the range-check shape:
   list *every* value of the enum in cases (don't leave adjacent values
   implicit in a bare `default:`) — that's often what convinces the compiler
   it's a dense small-range switch instead of a jump table or independent
   compares. Case order in source matters too: whichever case is listed last
   tends to become the block that lands as fallthrough.
6. **A single value spilling to the stack that real keeps in a register.**
   Read `gcc/local-alloc.c`'s allocation priority (see step 3) before
   guessing — but the empirically-fastest fix, when guessing is unavoidable,
   is decomp-permuter (step 4), which is unreasonably good at finding the
   "add one more competing pseudo-register" perturbation that changes who
   wins.
7. **A redundant check real keeps but your candidate optimizes away** (e.g. a
   branch sets a variable to a compile-time-known value, then jumps to a test
   of that same variable that real still emits in full but your candidate
   collapses to an unconditional jump). This is `jump_optimize`
   (`gcc/jump.c`) folding a conditional whose target label has
   `LABEL_NUSES == 1` — see step 3's worked example. Restructure so both
   branches reach the shared check via a real control-flow edge (each an
   explicit `goto`/fallthrough into the same label, so the label has two
   incoming edges) rather than one path being a bare early `return`/dead-end
   assignment — swapping which side is the `if`-body vs. `else`-body of the
   *outer* branch (which one is the syntactically-first, fallthrough-first
   arm) changes which side needs the explicit jump into the shared label, and
   that's what flips `LABEL_NUSES`. Confirmed to *not* respond to inverting
   the condition alone, or to swapping `if (cond) X; else Y;` for
   `if (cond) { X; goto L; } Y; L:` — both compiled identically; only the
   fallthrough-order swap moved it.
8. **Two source-level locals sharing one real register.** If real reuses a
   single register across what your draft treats as two different variables
   (e.g. an intermediate scaled value and the final return value), merge them
   into one C variable reused in place, rather than introducing a second
   local — a second local competes for register allocation instead of
   matching real's reuse, and won't fix the diff.
9. **A tie among several equal-`refs` constants for who gets which hard
   register (r7 vs r8 vs r9, etc.)**, when total instruction count already
   matches and the only diff is which value lands in which register. This is
   `allocno_compare` (`gcc/global.c`) sorting purely by `live_length` when
   `refs`/`size` are equal — shortest first, first-allocated wins the
   lowest-numbered free register; ties fall through to allocno number. Don't
   guess-and-check statement order (it moves several live_lengths at once and
   rarely lands the exact needed values) — dump the real numbers instead, see
   step 3's `-dg`/`-df` addition. One concrete lever once you have real
   numbers: a **dead insn that never reaches the output can still inflate
   `live_length`**, because it's measured on the pre-`combine` stream and
   never recomputed. A struct bit-field assignment expands through GCC's
   bit-field store path (read/AND-mask/OR), and the AND-mask insn survives
   into `flow` even though `combine` deletes it later — if that dead insn
   sits between two of your tied constants' uses, it can produce an exact
   tie that a plain read/write of the same field wouldn't. Writing that one
   store through a pointer cast (`*((u8 *)p + off) = v;`) instead of the
   struct field skips the bit-field path and can break the tie.

10. **A shared tail block reached by two different paths — don't reach for
   `goto` first.** This compiler does have a cross-jumping pass
   (`gcc/jump.c`'s `find_cross_jump`/`do_cross_jump`, run under
   `JUMP_CROSS_JUMP` from `gcc/toplev.c`), but it only merges two blocks that
   already end in an unconditional jump to a shared point — it does not
   retroactively merge two *textually duplicated* copies of the same check
   sitting in different straight-line branches (confirmed: costs real bytes,
   doesn't reproduce the target, in the case below). A `goto` into a shared
   label is
   one legitimate way to get one physical block with two incoming edges, but
   before reaching for it, check whether re-picking *which case is the outer
   split* makes the shared code fall out as plain fallthrough instead: if
   real's 3-way outcome is "special case A" vs. "B and C both run the same
   tail", write the *complement of A* as the outer `if`/`else` split (so both
   B and C are naturally inside the same `else` block, each individually
   gated) rather than putting one of B/C as a first-checked branch that has
   to jump forward into the other's tail. `ResolveEnemyAttack`'s
   `AttackWeakened`/`DefenseBoost` halving looked exactly like bucket 7's
   shared-join shape and initially got a `goto`-based fix that byte-matched
   — but was later found unnecessary: the three outcomes are "both flags set
   → quarter" (the only case skipping the `DefenseBoost` recheck) vs. "either
   other combination → run the (redundant, harmless) `DefenseBoost` check".
   Splitting on `AttackWeakened && DefenseBoost` as the outer condition, with
   both remaining cases falling through the same `if (DefenseBoost) …` inside
   one `else` block, reproduced the byte-identical shared block with no
   `goto` at all. Don't assume a `goto` is structurally required just because
   duplicating the check failed — try re-deriving which condition is the
   *true* outer split first.

11. **A guard macro wrapped in `do { … } while (0)` can block a shared tail
   from forming at all, even when cross-jumping (bucket 10) would otherwise
   apply.** `gcc/cse.c`'s `cse_end_of_basic_block` decides whether to follow
   a conditional jump's taken edge by scanning backward from the target
   label to a `BARRIER`, and that scan explicitly bails out on
   `NOTE_INSN_LOOP_END`. Wrapping a macro's body in `do { … } while (0)`
   emits exactly that note right after the macro's expansion, so every call
   site using the macro stops CSE from recognizing a shared tail across the
   sites — the taken-branch path looks like a dead end to CSE even though
   the real ROM merges many of these sites into one physical block. Writing
   the macro as a bare, unwrapped block (accepting that it can't safely be
   used where `if (cond) MACRO(x); else other();` needs the trailing
   semicolon to bind correctly) let a genuinely-shared multi-site tail
   materialize on rebuild, matching the ROM's shared block byte-for-byte.
   (`TickBattleTurnStateMachine`'s `TRANSITION_TO` macro, US
   `0x0800F794`: this single change took 34 opcode-diff groups down to 22.)
   If a macro used across several call sites is suspected of hiding a real
   shared tail, try de-sugaring it (drop `do/while(0)`) before reaching for
   an explicit `goto`-based rewrite (bucket 10).

12. **A derived-pointer loop-init sitting before the zero-trip guard when
   real has it after (or vice versa) — write the loop as indexed, not
   walking.** `for (aligned = p; i < n; i++) *aligned++ = x;` expands the
   pointer as a user variable, placed wherever the source's `for`-init
   is (typically *before* the guard test). Real instead often has it
   *after* the guard, in the loop preheader — that's `loop.c`'s
   strength-reduction (`strength_reduce`, `emit_iv_add_mult`) turning the
   *array-indexed* form `for (i = 0; i < n; i++) p[i] = x;` into a giv
   (general induction variable) whose init this compiler places at
   `loop_start`, which is itself already positioned after the zero-trip
   test duplicated forward by `jump.c`'s `duplicate_loop_exit_test`. Index
   instead of walking and let `loop.c` do the strength reduction itself —
   don't hand-write the pointer walk. (`memset`, US `0x0802C450`.)

13. **A value that should out-preserve a call sequence isn't reaching the
   preserved register your operand-count math says it should.** Two
   compounding effects, both real and independently checkable via `-dg`:
   - **`reload_cse_move2add`** (`gcc/reload1.c`) rewrites a second
     `(set REGX (const_int B))` into `(set REGX (plus REGX (const_int
     B-A)))` when a same-hard-reg `(set REGX (const_int A))` is still
     live and the rewrite is cheaper — e.g. a stray `mov r0,#0xf` earlier
     in the block lets a later `& ~0xf` mask materialize as `sub
     r0,r0,#0x1f` (15-31=-16) instead of a fresh `mov r0,#0x10; neg
     r0,r0`. This only fires post-reload, on literal hard registers, so
     it only shows up when the earlier constant load is still genuinely
     the same instruction stream — i.e. when the round-up is written as
     *one* combined expression (`(x + 0xf) & ~0xf`), the compiler is free
     to route the intermediate through a scratch register and this
     rewrite never gets the chance. Write the round-up as separate
     in-place statements on one pseudo (`len = x; len += 0xf; len &=
     ~0xf;`) instead of one expression — keeping it one pseudo modified
     in place is what lets the `+0xf` land in the exact register the mask
     step reuses.
   - **Loop-depth-weighted `REG_N_REFS`** (`gcc/flow.c`, `REG_N_REFS
     (regno) += loop_depth`, driven by `NOTE_INSN_LOOP_BEG`/`_END`) feeds
     `global.c`'s `allocno_compare` priority (`floor_log2(refs)*refs/
     live_length`, bucket 9 above) — a variable's references *inside a
     loop* count extra, but only for a loop the compiler actually
     recognizes as one. A `goto`-flattened loop emits no
     `NOTE_INSN_LOOP_BEG`, so every reference inside it is weighted as
     depth 1 like straight-line code, which can make a short-lived local
     that should lose the register-allocation tie (bucket 9) win it
     instead, starving the value that actually needs to survive a run of
     calls (memset, a big call sequence, etc.) of the safe register it
     needs. Write the loop as a real `for`/`do`-`while` (an `if` guard
     wrapping a `do { … goto found; … } while (cond);` is fine — the
     `goto`s inside are irrelevant, only the *loop construct itself*
     needs to be real) rather than flattening the whole thing to labels
     and `goto`. (`AllocZeroed`, US `0x0802C2EC`: writing the round-up
     stepwise got `0xf` into a register at all; turning the pool-walk
     `goto`-loop into a real `do`/`while` is what let the pre-existing
     `len` pseudo win r8 over `pFreeListHeadSlot` once that register was
     worth winning.)

14. **A `(value & mask) | bits` flag update where real puts the mask in the
   lower register — fold through the mask temp itself, not a fresh dest.**
   CSE's `fold_rtx` epilogue (`gcc/cse.c`) places the const-holding operand
   of a commutative op second *regardless of source spelling or decl order*,
   so the AND always reads (value, mask) and `regmove` ties the two-address
   dest to the first source (the value), ballooning it past the mask
   (observed: refs=6/pri 2.0 vs refs=2/pri 0.5, so the value wins `r0`).
   Writing `mask &= value` with the reload first makes the dest *be* the
   mask from the start: the commutative better-match check (`regmove.c`)
   sees the second source already matching the dest and skips the rewrite
   entirely — no ballooning, and the mask's extra mention as dest wins it
   `r0`. Both operand orders × both decl orders were built and all four
   converge to the same RTL, so don't burn time respelling; the house idiom
   already exists in matched `InitializeBattle`
   (`clearMask &= flagsBeforeClear`, reload before the mask is
   materialized). (`InitPlayerBattleActor`, US `0x080149C4`.)

After any fix, re-run the opcode-diff (step 1) before deciding whether to keep
it — a change can fix the thing you were chasing while quietly introducing a
same-sized new diff elsewhere; only the opcode-diff count tells you which.

**A working register-allocation lever still needs to look like plausible
source — and "reuses an existing local" is not automatically enough to
clear that bar.** A single-purpose `static inline` wrapper function around
one field access (e.g. `dwStateJustEnteredHelper(FightState *fs) { return
fs->dwStateJustEntered; }`) can be a real, fully-inlined, verified fix for a
bucket-9 tie — but if it's only applied at some of the several
identical-looking call sites (because the others regress with it), that's a
strong sign it's a register-allocator proxy wearing a function's clothes,
and it should be reverted even though it measurably works. The instinct to
"just reuse a local instead of inventing a function" doesn't dodge this: if
a function has an established set of locals each with one consistent
meaning throughout (a loop counter, a specific cached result, a
save-and-restore scratch), repurposing one of them for an unrelated value
in just the one case that needs the tie broken is the *same* proxy, one
level down — a plain `i = someUnrelatedFlag; if (i) { ... }` where `i` is
otherwise only ever a loop index is exactly as implausible as the wrapper
function, and should be reverted on sight even if `tools/opcode_diff.py`
confirms it works and it's UB-free. (`TickBattleTurnStateMachine`, US
`0x0800F794`: four such reuses — the wrapper, `i` holding a boolean flag in
two unrelated cases, `savedState` holding a timer value instead of a saved
battle state, and `i = 0; field = i;` in place of `field = 0;` — were all
real, verified, independently-rebuilt improvements, and all four were
reverted once examined for plausibility rather than just effect.) A
legitimate reuse looks like: the same variable, for the same purpose it
already has, one statement earlier or later than you first wrote it — not
a different field's value borrowed into a variable whose name and every
other use describes something else. If no such natural reuse exists at a
site, that site may simply not have a source-level lever at all (see bucket
9); accept the higher diff count rather than manufacture one. When a reuse
does look natural, still check the local's *type* matches the field's width
— a `u8` local caching a wider read forces a narrower load instruction than
the ROM's, and the ROM disassembly's mnemonic (`ldr` vs `ldrb`) will tell
you outright if you check.

## 3. When you're guessing blind, go read the actual compiler source instead

This was the single highest-leverage move in the whole session, used twice,
both times replacing many failed trial-and-error attempts with a fix on the
first or second try:

```bash
git clone https://github.com/pret/agbcc.git /path/to/scratch/agbcc-src
cd /path/to/scratch/agbcc-src && git checkout <pinned rev from flake.nix>
```

The pinned revision is a real, byte-verified match for the actual compiler
binary in use (confirmed via `nix develop`'s `agbcc` derivation) — so what you
read is not "GCC 2.9-ish", it's the literal source. Old GCC (`gcc/expr.c`,
`gcc/stmt.c`, `gcc/local-alloc.c`, `gcc/global.c`, `gcc/jump.c`) is small
enough (and this compiler has **no instruction scheduler at all** — no
`sched.c`, confirm via `grep -r flag_schedule_insns gcc/toplev.c`) that a
"why does it emit *this* order" question usually has a short, findable answer:
which `expand_expr` case handles the construct, whether it goes through
`store_expr`/`EXPAND_NORMAL` (operand order preserved) vs. address expansion
under `EXPAND_SUM` (operands get reordered — constant/mult term gets sorted
last), and whether a register-allocation priority formula
(`QTY_CMP_PRI`/`floor_log2(refs)*refs*size/live_length` in `local-alloc.c`, or
`allocno_compare` in `global.c`) explains a specific spill.

Delegate this to a subagent with direct filesystem `Bash`/`Read`/`Grep` access
to the cloned source (not just pasted excerpts) and the specific real-vs-
candidate disassembly diff already narrowed down (steps 0-2 did that work;
don't make the subagent re-derive it). Ask it to cite actual file/line/function
names for its claim, and to say plainly "this isn't reachable by a source
rewrite, here's the specific pass/ordering that decides it" if that's what it
finds — that's as useful an answer as a working fix, and much more useful than
another untested guess.

**For a register-allocation tie (bucket 9), don't theorize — dump the real
numbers.** `agbcc <flags> -dg -o out.s in.i` (after `cpp`-preprocessing) makes
`global.c` print `Register N, refs = R, live_length = L, size = S` for every
pseudo, sorted in allocation order, straight into `in.i.greg` alongside the
post-allocation RTL (hard-reg-numbered, so you can grep `(const_int
<your-value>))` there to see which allocno is which and which hard register
it landed on). This is ground truth, not inference — iterate by editing a
throwaway `.c` copy, re-running `cpp`+`-dg`, and grepping the dump; only apply
a change to the real source once the dump confirms it. Cross-check with `-df`
(the same figures at `flow` time) if the numbers look off. Much faster than
rebuilding the whole project per guess.

**Always independently re-verify anything an agent (or yourself, tired) claims
fixed something:** rebuild it, re-run the opcode-diff yourself, check for
spills, and if a suspicious "should be a no-op" claim was made about a chunk
of new code, compile with and without that chunk and `cmp` the two `.o` files
— if they differ, it is *not* actually inert no matter how it reads, and needs
its own honest accounting.

**Worked example — bucket 7's redundant-check collapse.** `ResolveEnemyAttack`
(0x08017E44, US) had a miss-path/hit-path branch where real kept a redundant
`if (damage != 0 && ...)` check on both paths but a from-scratch draft
collapsed it away on the miss path alone. `gcc/jump.c`'s `jump_optimize`
(around `thread_jumps`, gated on `LABEL_NUSES(...) == 1`) only folds a
conditional into an unconditional jump when its target label has exactly one
incoming edge. The draft's `if (cond) { damage = 0; } else { <hit path> }`
put the miss arm first — a straight-line block with no other predecessor for
its copy of the check, trivially collapsible. Real's compiled shape has the
*hit* path fallthrough-first, so it must explicitly branch forward into the
shared check, giving that label two predecessors and blocking the fold.
Swapping which arm goes first (`if (hitPathCond) { <hit path> } else {
damage = 0; }`) reproduced real exactly; inverting the condition alone, or
swapping `goto`-to-shared-label for `if`/`else`, both left it unchanged —
confirming it's genuinely the fallthrough-order/edge-count property, not
surface phrasing.

## 4. decomp-permuter — set up scoring correctly or don't bother

Comparing an unlinked candidate object against bytes cut directly from the
linked ROM is close to useless: the score plateaus on relocation-vs-resolved-
address noise regardless of candidate quality. Fix: build `target.o` by
assembling a *relocatable* copy of the real disassembly for just this
function (wrap the extracted `full_disasm.s` lines in
`thumb_func_start`/`_end`, `.syntax unified` at the top), with the
literal-pool `.4byte 0x0300....`-style constants swapped for
`.extern`-declared symbol names matching the real project globals — left
*undefined* so they show up as relocations on both sides, not resolved on one
side and symbolic on the other. This alone reproduces the real function's
exact byte size when assembled standalone.

`tools/make_permuter_target.py <ver> <function-name> <out-dir>` automates all
of this: it slices the function out of `build/<ver>/full_disasm.s`, resolves
literal-pool RAM addresses against `ram_symbols.<ver>.inc` and externs them,
assembles `target.o`, preprocesses the function's actual `.c` source (read
straight from the `c-file` row's source column in `regions.<ver>.txt` — not
`manifest.py`'s parsed `Region`, whose 3rd field is the *generated*
`build/<ver>/c/<name>.s` path, not the original `.c`) into `base.c`, and
writes a `compile.sh`/`settings.toml` pair using the project's real agbcc
flags (mirroring `tools/c/compile_c.py`'s game-code profile). It prints the
`tools/opcode_diff.py` command to sanity-check the result — run that (and
check `arm-none-eabi-size target.o`'s `.text` figure against the real
function's byte count) before trusting `target.o` for permuter scoring.

```bash
permuter.py <dir> --debug          # sanity: prints a base score, doesn't crash
permuter.py <dir> -j $(nproc) --stop-on-zero --best-only
```

Re-seed (`base.c` = your latest candidate, freshly preprocessed) and rerun
after every manual fix — nearly every real win from permuter in this session
was found while it was mutating a part of the function *unrelated* to what it
ended up fixing, so treat "run it again from the new best" as a first-class
strategy step, not a last resort.

**Every "best" result is noise until proven otherwise**, on two independent
axes:
- **Permuter's own score is not the opcode-diff.** A lower score does not
  imply fewer real differences — it as often means better *register-name*
  alignment on an otherwise-unchanged instruction sequence. Recompile, re-run
  the real opcode-diff (step 1) yourself, and only adopt it if that count
  actually drops.
- **Read every promoted candidate's diff before adopting it.** Random mutation
  reliably produces candidates that score well while being subtly wrong:
  emptied-out bonus branches, an uninitialized variable standing in for a
  literal (relying on incidental garbage reading as the right value), a
  stale/aliased variable read in place of the real one, an unconditional
  overwrite of a variable used later. None of these are hypothetical — all
  were seen in one session. If a diff *looks* like inert dead code (an
  `if (always-true-expression) { }` with an empty body, an unused-looking
  assignment), don't assume — compile with and without it and `cmp` the two
  `.o` files (see step 3's last paragraph); if they differ, it's load-bearing
  for the register allocator and needs to stay, with a clear comment saying
  so and that it's a proxy, not real logic.

## 5. Comment discipline for what you land on

Some fixes are genuinely explicable (real caches this field too; real's
division is provably unsigned) — say so in the comment, briefly, and treat
them as legible source. Others are permuter-found register-pressure proxies
with no clean explanation (an always-1 dummy variable, a pointless
`do { } while (0)` wrapper, a cached pointer that's "wrong" by any normal
style standard) — say *that* plainly too, right at the point of definition:
that it's a proxy found by mutation search, not a claim about the real
original source, and that the bar for replacing it later is reproducing the
byte sequence, not preserving the specific token. Don't present a proxy fix as
if it were understood, and don't let a growing pile of them substitute for
actually finding the mechanism (step 3) when there's still budget to look.

Matched code can still be cleaned up, but only with rewrites proven
byte-neutral by rebuild + re-diff — never by reasoning alone. Safe in
practice: renaming locals (pseudo numbering follows decl *order*, not
names); replacing a magic hex offset with an equal constant expression
(`0xD8` → `3 * sizeof(BattleFighter)` — const arithmetic folds before RTL,
so any two spellings folding to the same constant are interchangeable);
retyping a temp within the same mode (`s32` → `u8 *`, the casts being
mode-preserving NOPs that vanish in expand). Not safe even when it looks
local: removing a temp (one fewer live pseudo recolors distant code — a
second live-branch temp's removal recolored sites hundreds of bytes
earlier), or restructuring the statement around it (extra `mov`, shifted
`adds` pairs). (`InitPlayerBattleActor`, US `0x080149C4`.)

Never claim a fix is verified without independently rebuilding and re-checking
yourself — an agent's (or your own) summary describes intent, not
necessarily what actually landed in the file.
