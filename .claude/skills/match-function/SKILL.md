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
closer in every real sense. Build the opcode-only diff harness immediately,
before your first real iteration, and use it as the actual metric instead:

```bash
# real side, once per function: extract + strip labels/directives, keep opcodes only
sed -n '<start>,<end>p' build/us/full_disasm.s | grep -vE '^_|\.align|\.4byte|thumb_func|^$' \
  | sed -E 's/^\s+//' | awk '{print $1}' > real_op.txt
# candidate side, per iteration: same idea from objdump -dr output
arm-none-eabi-objdump -dr cand.o | grep -E '^\s*[0-9a-f]+:' \
  | sed -E 's/^\s*[0-9a-f]+:\s+[0-9a-f ]+\t//' | grep -vE 'R_ARM|^\s*\.\.\.|\.word' \
  | awk '{print $1}' > cand_op.txt
```

Diff with Python's `difflib.SequenceMatcher` (not raw `diff`) so insertions/
deletions realign instead of cascading into a wall of noise, and **normalize
cosmetic-only differences before counting groups**:
- a trailing `.n` on any mnemonic (narrow-encoding annotation some
  disassemblers print and others don't)
- ARM condition-code mnemonic aliases: `bhs`≡`bcs`, `blo`≡`bcc` (literally the
  same encoded condition, different assembler convention — verify by decoding
  the condition field of the halfword by hand once if unsure, don't guess)
- `.short`/`.word` alignment padding, *unless* it's the specific diff you're
  chasing

Report "N real (non-cosmetic) opcode-diff groups", not "N bytes off". Recount
after every change — a fix can trade one group for a different one at the same
total, which is easy to mistake for "no progress" if you're only watching size.

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

After any fix, re-run the opcode-diff (step 1) before deciding whether to keep
it — a change can fix the thing you were chasing while quietly introducing a
same-sized new diff elsewhere; only the opcode-diff count tells you which.

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

**Always independently re-verify anything an agent (or yourself, tired) claims
fixed something:** rebuild it, re-run the opcode-diff yourself, check for
spills, and if a suspicious "should be a no-op" claim was made about a chunk
of new code, compile with and without that chunk and `cmp` the two `.o` files
— if they differ, it is *not* actually inert no matter how it reads, and needs
its own honest accounting.

## 4. decomp-permuter — set up scoring correctly or don't bother

Comparing an unlinked candidate object against bytes cut directly from the
linked ROM is close to useless: the score plateaus on relocation-vs-resolved-
address noise regardless of candidate quality. Fix: build `target.o` by
assembling a *relocatable* copy of the real disassembly for just this
function (wrap the extracted `full_disasm.s` lines in
`thumb_func_start`/`_end` from `macros.inc`, `.syntax unified` at the top),
with the literal-pool `.4byte 0x0300....`-style constants swapped for
`.extern`-declared symbol names matching the real project globals — left
*undefined* so they show up as relocations on both sides, not resolved on one
side and symbolic on the other. This alone reproduces the real function's
exact byte size when assembled standalone, and (optionally, to sanity-check
the whole setup once) can be linked against the real addresses with tiny
`.thumb_func` stub objects for any called functions, to confirm it reproduces
the donor ROM's bytes exactly before trusting it as `target.o`.

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

Never claim a fix is verified without independently rebuilding and re-checking
yourself — an agent's (or your own) summary describes intent, not
necessarily what actually landed in the file.
