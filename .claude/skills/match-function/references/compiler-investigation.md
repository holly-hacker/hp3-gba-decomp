# Compiler investigation

Use after isolating a concrete difference that source/assembly inspection does not explain.
Read the pinned revision from `flake.nix`; prefer an existing local compiler source checkout
or Nix source. If missing, clone pret/agbcc into scratch and check out that exact revision.
Do not assume a current upstream checkout is the compiler in the build.

## Generate and follow RTL

```bash
python3 -m tools.matching compile WORKSPACE --dumps lg
# Or flow + local + global:
python3 -m tools.matching compile WORKSPACE --dumps flg
# All passes, when the responsible pass is unknown:
python3 -m tools.matching compile WORKSPACE --dumps a
```

Dumps sit beside `current/candidate.i`; agbcc appends pass suffixes such as `.lreg`,
`.greg`, `.flow`. Use `rg --files WORKSPACE/current` to discover emitted names. Snapshot
important output before another build overwrites it. The generated `.i` is the exact
preprocessed input; `.s` is wrapped for assembly using production section handling.

1. Locate the earliest pass where the relevant expression or control-flow shape diverges
   from the intended shape. Search for a distinctive field offset/constant or instruction.
2. In `.lreg`, identify the destination pseudo `(reg/v:SI N)`. Pseudos spanning blocks/calls
   generally remain visible before global allocation; some locals are already allocated.
3. Find `Register N` statistics and the disposition `N in H` in `.greg`: refs, live_length,
   size, allocation order and final hard register. `.greg` RTL is already hard-register
   substituted; grepping it for pseudo N will not find the value.
4. Correlate instruction numbers across adjacent dumps of the same compilation. Do not
   assume numbers remain stable across source changes. Compare `.flow` when liveness differs.
5. Register preference is not a guarantee. An immediate compare can prefer LO_REGS, while
   conflicts force a long-lived value into a high register and add moves at use sites.

## Source map

| Question | Start in pinned agbcc source |
| --- | --- |
| Expression/address order | `gcc/expr.c`: expand_expr, store_expr, EXPAND_NORMAL/EXPAND_SUM |
| Branch/loop expansion | `gcc/stmt.c` |
| Local allocation and spills | `gcc/local-alloc.c`: QTY_CMP_PRI |
| Global ties/conflicts | `gcc/global.c`: allocno_compare, global_conflicts, find_reg |
| Threading/shared tails | `gcc/jump.c`: thread_jumps, find_cross_jump, do_cross_jump |
| Macro barriers/canonicalization | `gcc/cse.c`: cse_end_of_basic_block, fold_rtx |
| Copy propagation/PRE | `gcc/gcse.c` |
| Loop induction/hoisting | `gcc/loop.c`: strength_reduce, basic_induction_var, move_movables |
| Loop-weighted references | `gcc/flow.c`: REG_N_REFS and loop notes |
| Two-address destination | `gcc/regmove.c` |
| Post-reload constant reuse | `gcc/reload1.c`: reload_cse_move2add |
| Pass sequence/options | `gcc/toplev.c`, target `thumb.h` |

The original investigations found no instruction scheduler in this pinned compiler. Check
expansion, optimization and allocation before attributing instruction order to scheduling.
Inspect the actual comparator formula: don't generalize a tie case into the entire policy.

## Test a mechanism

State a falsifiable prediction, then inspect the relevant dump and compiler code. For a
suspected pass with a supported `-fno-...` option, make one diagnostic compilation of the
unchanged `.i` with that pass disabled. Recover the normal flags from
`tools/c/compile_c.py:profile`; copy the command into a scratch output directory and add
only the diagnostic flag. Do not modify production profiles or accept that output as a match.

Changed output supports involvement but does not identify the exact mechanism. Unchanged
output weakens the hypothesis; equivalent work by another pass or an inactive code path can
mask the effect. A source citation alone is not proof. Reproduce the predicted intermediate
change, then test an idiomatic rewrite under normal flags and recheck the whole function.

Example: ResolveEnemyAttack's shared damage recheck implicated jump threading and label use
counts. The useful question was which outer arm fell through into a shared check; simply
negating conditions or inserting a superficially equivalent goto did not change the output.

## Reference and relocation checks

`prepare` creates a relocatable target, translates known RAM-address literals into symbols,
then links it against frozen baseline ELF symbols and verifies the full requested ROM slice.
This avoids scoring resolved ROM call/address bytes against unresolved candidate relocations.
Symbol aliases, addends, shared pools and external address labels can still need investigation.
Use `arm-none-eabi-objdump -dr FILE.o` and `arm-none-eabi-nm -u FILE.o`; retain label-bearing
lines. Inspect literal bytes too. Do not filter away every line containing `<label>`.

`compare` links candidate text at its original address against the same baseline symbols.
This validates the candidate region in that context, including pools/padding. It does not
replace a fresh production build: other functions, changed symbols and version differences
must still pass `just check-all`. A byte-neutral cleanup is established by rebuilding,
not by assuming a cast or expression spelling must disappear.
