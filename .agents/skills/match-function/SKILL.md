---
name: match-function
description: Decompile a ROM function into readable, byte-matching C in this HP3 GBA repository, or investigate a mismatch using its pinned agbcc toolchain.
---

# Matching ROM functions

Produce idiomatic C that documents the game and accurately recreates its ROM.
Both readable meaning and matching output are acceptance criteria. The original
implementation establishes that a solution exists in the original build context;
a stalled attempt means the reconstruction or context needs more investigation.
Report an unresolved mismatch precisely; do not declare matching impossible.

## Working agreement

- Read repository guidance and [style-guide.md](references/style-guide.md) before writing C.
- Use the pinned compiler and production flags. Diagnostic flag changes stay in experiments.
- Prefer meaningful variables, typed fields, normal expressions and structured control flow.
  Explicit register assignments, excessive casts/gotos, dummy work and allocator-only
  wrappers are exceptional. Explain a proposed exception to the user before accepting
  it or building further work on it; otherwise keep investigating idiomatic alternatives.
- Comments explain game behavior and meaningful uncertainty. Do not add explanations
  of ordinary C syntax or compiler matching tricks to readable source.
- Never accept undefined behavior to improve a score. Byte equality is required, but
  it does not excuse uninitialized reads, invalid accesses or fabricated source logic.
- Keep experimental candidates under `build/matching/`; preserve useful alternatives.
  Do not overwrite unrelated user work or put ROM-derived artifacts in git.

## 1. Establish the target

Run commands from the repository root. **Check the environment once:** run
`command -v agbcc old_agbcc arm-none-eabi-as arm-none-eabi-objdump just`.
If all are available, run commands directly; do not start another `nix develop`.
Otherwise, use `nix develop -c <command>`. Treat a set `IN_NIX_SHELL` variable as
supporting evidence, but check tool availability rather than relying on it alone.
Discover options with `python3 -m tools.matching --help`.

1. Identify version, function address, instruction mode, callers, callees, and source
   profile. Game C uses agbcc; `src/libc/` uses old_agbcc. ARM C requires an identified
   compiler profile; the candidate workflow currently supports Thumb only.
2. Check the current build with `just compare us` and `just compare jp`. Record any
   pre-existing failure before changing code. Do not rerun asset extraction over edits.
3. Refresh reference assembly with `just disasm-compare VERSION` when seeds or the
   dump are stale. Inspect `build/VERSION/full_disasm.s` against the ROM; Ghidra can
   have stale types or misidentified code. Generated assembly is evidence, not an
   infallible boundary oracle.
4. Trace reachable paths, return/tail-call behavior, tables and literal pools. Confirm
   struct offsets, widths and signedness from instructions and callers. Compute address
   arithmetic with Python. The next known function label need not be the true end.

An exploratory C draft can help test understanding; do not spend time tuning registers
while known semantic or boundary questions remain.

## 2. Prepare and compile

For a function already in the manifest:

```bash
python3 -m tools.matching prepare us ResolveEnemyAttack
python3 -m tools.matching compile build/matching/us/ResolveEnemyAttack
python3 -m tools.matching compare build/matching/us/ResolveEnemyAttack
python3 -m tools.matching snapshot build/matching/us/ResolveEnemyAttack baseline
```

For an unmatched function, provide `prepare VERSION NAME --source PATH --end 0xEND`.
The function needs an entry in `full_disasm.s`; persist confirmed names in
`functions.VERSION.cfg`. END is exclusive and
must include its pools/padding. Use `--profile-source src/libc/NAME.c` for libc drafts
outside that directory. No production manifest row is required. Conflicting seed/manifest addresses stop preparation;
use `--reference-name NAME` only after verifying a differently named disassembly entry.

Preparation refuses to overwrite an existing workspace. It assembles the reference slice (ending at the requested address label
when present, otherwise the next function label), links against baseline symbols, and checks every byte against the
requested ROM extent. If this fails, inspect the retained `reference/` files and resolve
boundaries, missing symbols or shared pools; do not weaken verification to proceed.
A successful byte check validates extraction, not completeness of your reachability analysis.

Edit `WORKSPACE/current/candidate.c`, or import a draft with `compile WORKSPACE --source PATH`.
Compilation shares the production profile and section handling. Local quoted includes
must remain reachable from the candidate or its original source directory.
`compare` uses the most recently compiled object; recompile after every source change.
Workspaces freeze baseline symbols: recreate under a new workspace location/name by
moving the old workspace aside if symbol addresses, types, flags or reference inputs change.

## 3. Diagnose and experiment

`compare` reports exact linked-region bytes and a selected-function operand diff.
Its categories (register, operand/address, branch, relocation) suggest where to look;
they do not establish a compiler mechanism. Literal pools and padding also matter.
`opcode-diff VERSION NAME OBJECT` is a coarse mnemonic-only aid, never an acceptance gate.
Zero mnemonic groups can hide wrong registers, constants, targets and data.

Use a short loop:

1. State the mismatch and one testable hypothesis.
2. Make a focused source change; compile and compare.
3. Inspect the entire difference, including spills and other blocks, rather than only
   the count. Keep a semantic improvement or useful alternative even when its score rises.
4. Snapshot meaningful candidates with distinct names. To restore one, copy its
   `candidates/NAME/current/candidate.c` back into `current/`, then recompile.

Read the relevant entries in [troubleshooting.md](references/troubleshooting.md):

| Symptom | Entries |
| --- | --- |
| Extra masks, shifts, wrong field accesses | 1–3, 24 |
| Branch layout, switch shape, duplicated/shared checks | 4–5, 7, 10–11 |
| Spills, wrong registers, unexpected local reuse | 6, 8–9, 13–15 |
| Loop initialization, copies, hoisted loads | 12, 16–19, 23 |
| Pool entries, switch layout, argument extension | 20–22 |

After several experiments fail to explain the same difference, stop respelling blindly.
Revisit the outer control-flow split, types, caching, loop form and compiler context.
A promising candidate can be a local minimum: branch from an earlier snapshot and test
another natural structure instead of accumulating special cases on the lowest score.
For an isolated compiler question, read [compiler-investigation.md](references/compiler-investigation.md)
and inspect dumps/source. A failed rewrite is evidence about that experiment, not proof
that the function cannot match.

## 4. Optional permuter experiments

Use only after manual analysis has a concrete remaining question. First snapshot the
candidate, then `permuter-setup WORKSPACE`; it refuses to overwrite earlier inputs/results.
Run `permuter-run WORKSPACE` for at most 120 seconds by default, with two workers.
Short experiments may use `--seconds 180`. Do not chain repeated short runs to evade
this limit or let automated search replace investigation.

For longer runs, explain what is stuck, what the search may reveal, and the proposed
wall time/workers; ask the user first. Only after explicit approval use
`--seconds N --approved-long-run`. The tool terminates the worker process group on timeout
and preserves results/logs. The flag records an assertion, not an automatic permission grant.

Inspect every proposed mutation for changed behavior, uninitialized/stale reads, aliasing,
invalid shifts, overflow, and artificial constructs. Register-only improvements count as
progress even without a lower mnemonic score. Recompile a reviewed candidate with normal
production settings and inspect all differences. A zero score alone proves neither safe
source nor a complete ROM match. Refresh setup from an improved candidate by preserving
and moving the previous `permuter/` directory aside first.

## 5. Finish

- Review C for readable types, field accesses, names, expressions and control flow;
  simplify decompiler artifacts and rebuild after any structural cleanup.
- Copy accepted source to the appropriate `src/` path. Integrate only a confirmed complete
  region, synchronize necessary declarations/symbols, and retain unsupported regions as incbin.
- Run `just diff-region NAME VERSION` for a fresh linked region comparison and
  `just check-all` for both-version donor, disassembly and build verification.
  A workspace match is provisional until this passes.
- Report what matched, verification performed, and concrete unresolved issues. If work
  stops short, preserve the draft and useful hypotheses without calling it impossible.
  Follow repository rules for commits; completing a match does not authorize a commit.

## Maintaining this skill

Add knowledge when a verified discovery changes future decisions. Prefer correcting or
merging an existing entry. Keep the main workflow around 150 lines; put conditional detail
in references. A troubleshooting entry should usually be 3–8 lines: symptom, mechanism,
experiment, example/evidence. Scope observations to their compiler/context; retain useful
failed approaches without session narratives. Do not append transcripts, scores or repeated
warnings. Record extensive one-function analysis separately only when it is worth preserving.
