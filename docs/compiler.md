# Compiler

See [`README.md`](README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED).

**Thumb code — PROVEN.** Both ROMs are built with GCC `2.9-arm-000512`
(the ARM/Cygnus snapshot Nintendo shipped as the AGB SDK compiler; its
source is packaged as [pret/agbcc](https://github.com/pret/agbcc)), GNU
binutils, and newlib.

- Game code: Thumb, `-O2`, `-mthumb-interwork`.
- Bundled libgcc/libc: Thumb, `-O2 -fno-builtin`, no interworking.

## Proof: the library block

A contiguous run of libgcc and libc objects near the end of the code
region reproduces **byte for byte** from a locally built agbcc
`libgcc.a`/`libc.a` (only relocated bytes masked out; trailing `c046`
object padding appears as `0000` linker fill in the ROM):

| US | JP | object | bytes |
|---|---|---|---|
| `0804A2C0` | `0804A1EC` | `_call_via_rX` | 60 |
| `0804A2FC` | `0804A228` | `_divsi3` | 148 |
| `0804A390` | `0804A2BC` | `_dvmd_tls` (`__div0`) | 4 |
| `0804A394` | `0804A2C0` | `_modsi3` | 208 |
| `0804A464` | `0804A390` | `_udivsi3` | 120 |
| `0804A4DC` | `0804A408` | `_umodsi3` | 192 |
| `0804A59C` | `0804A4C8` | `dp-bit` | 3484 |
| `0804B338` | `0804B264` | `fp-bit` | 2380 |
| `0804BC84` | `0804BBB0` | `_lshrdi3` | 52 |
| `0804BCB8` | `0804BBE4` | `_muldi3` | 112 |
| `0804BD28` | `0804BC54` | `_negdi2` | 24 |
| `0804BD40` | `0804BC6C` | libc `bzero` | 28 |
| `0804BD5C` | `0804BC88` | libc `memcpy` | 96 |

`dp-bit` and `fp-bit` are ~5.8 KB of compiler-generated Thumb from C, so
the match pins the code generator, not just the library source.

Control: the same matcher run over 393 objects from devkitARM r5's
gcc-3.3.3 thumb multilib finds 3 matches — `_call_via_rX`, `_divsi3`,
`_udivsi3`, the hand-written assembly whose Thumb text is unchanged
between the two versions. Every compiler-generated object fails.

`_call_via_rX` is live: game code `bl`s into it 169 times.

## Proof: game code

Thumb switch dispatch is the fingerprint that separates the game's own
code from a linked-in prebuilt library.

```
    gcc 3.3.3                        2.9-arm-000512 / this ROM (0x08003A8E)
    ldr  r2, [pc, #N]                  lsls r0, r0, #2
    lsls r3, r3, #2                    ldr  r1, [pc, #4]
    ldr  r3, [r3, r2]                  adds r0, r0, r1
    mov  pc, r3                        ldr  r0, [r0]
                                       mov  pc, r0
```

All 99 switch sites in the code region use the second form, in both
ROMs. A whole-image sweep finds 138 of the second form and one apparent
instance of the first, at `0x0841996C` (US) / `0x0841979C` (JP) --
inside compressed asset data, not code. One `_call_via_rX` table exists
in the image. There is no second toolchain.

## Version bracket, independent of agbcc

The ROM's `__modsi3`/`__umodsi3` lack the `mov curbit, ip` / `mov
work, #0x7` / `tst` / `beq` guard that GCC trunk added in r35888
(2000-08-22), and Thumb `lib1funcs` exist at all only after the
merged-arm-thumb-backend merge (2000-04-08). No FSF release ever shipped
that window — 3.0 already carries the fix.

## ARM-mode code — UNCONFIRMED

Compiled ARM-mode C exists (e.g. `0x08FB11E4` in the Krawall region) and
is shaped like interworking old-GCC output, but is not byte-verified.
The SDK's ARM compiler is a separate binary; pret's `gcc_arm/` does not
build on a modern x86_64 host (`make cc1` fails with `FATAL_EXIT_CODE`
undeclared in `rtl.c`), so it has not been tested against.

The ARM routines at `0x0800027C`, `0x080002A4` and `0x080002E0` are
hand-written assembly, not compiler runtime: `0x080002E0` is a 32-way
binary-search dispatch into unrolled restoring division, and the two
wrappers above it return the remainder through a pointer in `r2`. The
compiler's own division helpers are the Thumb `_divsi3`/`_modsi3`/
`_udivsi3`/`_umodsi3` objects listed above.

## Optimizer quirk: cross-branch loop-invariant merging

`gcc/loop.c`'s `-O2` invariant-hoisting pass can merge two textually-separate
loads in a loop's `if`/`else` branches into one value hoisted above the loop
and cached in a register, even though only one branch executes per
iteration -- e.g. a global-pointer address that the real ROM instead
reloads via a fresh literal-pool load in each branch, uncached.

Mechanism (checked against the pinned agbcc revision, see "Reproducing"
below): `find_and_verify_loops` records each invariant-looking `set` as a
`struct movable`. `combine_movables` unifies two movables whenever
`n_times_set[regno] == 1` for both and `rtx_equal_for_loop_p` finds their
generated RTL identical -- true for any two branches loading the same
global through the same addressing mode, regardless of C-level phrasing, so
renaming variables or splitting the expression differently does not defeat
the merge itself. `move_movables` then hoists the merged pair only if
`threshold * savings * lifetime >= insn_count` (`threshold` is a
target-wide constant from `regclass.c`; `savings`/`lifetime`/`insn_count`
are specific to the loop's actual instruction sequence, and merging roughly
doubles the first two). A residual "extra register-cached global" diff is
therefore still closable by hand: match real's exact statement and branch
order (not just its logic) so the surrounding loop's cost numbers drop the
merged candidate back under threshold. `DecompressDialogText`
(`src/text/decompress_dialog_text.c`) is a worked example -- initializing
`pending`/`pendingFlag` before the null check, and writing the
pending/pendingFlag update as `if (decodedByte > 0xef && !pendingFlag)
{...} else if (pendingFlag) {...} else {...}` (matching real's exact
fallthrough/branch-target layout, no `goto`) both push the hoist back below
threshold. decomp-permuter is worth a run if manual restructuring doesn't
converge -- a mutation that raises `n_times_set[regno]` for one side, or
changes `insn_count`, can also break the merge or its hoist.

A separate quirk: at a block with two predecessors, GCC 2.9's `cse.c` can
eliminate a redundant sub-expression (e.g. a repeated `x << 24`) but still
re-derive the final value at the join point instead of reusing either
predecessor's already-computed copy, when that value is exposed only
through a persistent named local rather than repeated inline expressions.
Re-deriving the expression at each use site instead of caching it in a
local lets CSE find (or not find) the sharing the way real's compiler did,
when a residual diff looks like a register/recompute choice rather than a
wrong value.

## Reproducing

`nix develop` provides `agbcc` and `old_agbcc`; `flake.nix` pins the
source. Compare any object's `.text` from its `libgcc.a`/`libc.a` against
the addresses above, or read `tools/c/compile_c.py` for the flags each
half of the ROM was built with.
