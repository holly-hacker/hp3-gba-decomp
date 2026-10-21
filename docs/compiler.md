# Compiler

See [`README.md`](README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED).

**Thumb code — PROVEN.** Both ROMs are built with GCC `2.9-arm-000512`
(the ARM/Cygnus snapshot Nintendo shipped as the AGB SDK compiler; its
source is packaged as [pret/agbcc](https://github.com/pret/agbcc)), GNU
binutils, and newlib.

- Game code: Thumb, `-O2`, `-mthumb-interwork`.
- Bundled libgcc/libc: Thumb, `-O2 -fno-builtin`, no interworking.

The Krawall audio library is the exception: it was built separately, with
GCC 3.0.2 (see "Krawall: GCC 3.0.2" below).

## Proof: the library block

A contiguous run of libgcc and libc objects near the end of the code
region (`_call_via_rX` through libc `memcpy`) reproduces **byte for byte**
from a locally built agbcc `libgcc.a`/`libc.a`. The build links them
unchanged through the manifest's `lib-object` rows.

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
in the image. The game's own code has no second toolchain; Krawall,
which was linked in as a separately built library, is the one
exception (below).

## Version bracket, independent of agbcc

The ROM's `__modsi3`/`__umodsi3` lack the `mov curbit, ip` / `mov
work, #0x7` / `tst` / `beq` guard that GCC trunk added in r35888
(2000-08-22), and Thumb `lib1funcs` exist at all only after the
merged-arm-thumb-backend merge (2000-04-08). No FSF release ever shipped
that window — 3.0 already carries the fix.

## ARM-mode code — PROVEN

Game ARM code is built with the SDK's separate ARM compiler, packaged as
pret/agbcc's `gcc_arm/` and provided by `nix develop` as `agbcc_arm`
(same `2.9-arm-000512` version string). Flags: `-O2 -mthumb-interwork
-fomit-frame-pointer`; without `-fomit-frame-pointer` it emits an APCS
frame the ROM lacks. The game's ARM routines (`src/arm_routines/`, from
`0x08005F10`) match byte-for-byte under this profile (`c-file-arm`, see
[`c.md`](c.md)).

`agbcc` and `old_agbcc` are Thumb-only: `-marm` is rejected
(`agbcc: Invalid option 'arm'`).

Krawall's ARM code, in the IWRAM image and `mixRampOut`, comes from the
Krawall compiler below.

## Krawall: GCC 3.0.2 — PROVEN

Krawall (`3rd_party/krawall/`) is compiled with FSF
GCC 3.0.2, `-O3 -mthumb-interwork -fno-builtin`, Thumb (`-mthumb`) for
`c-file-gcc3` rows and ARM (`-marm`) for `c-file-gcc3-arm` rows.
`krapPlay` calls `bzero`, which GCC 3.0.2 turns into a `memset` call
unless builtins are disabled. The reconstructed
`directsound.c` and `general.c` reproduce the ROM byte for byte under
these flags, as does the public Krawall source's `kradActivate`
unchanged. The public `mixer.c` says it was built with 3.0.2 ("makes GCC
3.0.2 generate an invalid constant").

Neighbouring releases do not reproduce it:

- **3.1.1, 3.2.2, 3.2.3, 3.3.2**: `getDmaAddress` and `dsInit` do not
  match. `dsInit`'s mono branch stays inline where the ROM moves it to the
  end of the function: from 3.1 on, branch prediction ignores `== 0`
  tests, which 3.0 predicts false. 3.2.x also keeps `getDmaAddress`'s
  variable addresses in registers across blocks where the ROM reloads
  them.
- 3.1.1 also lays out ARM functions such as `kramSetFreq` differently,
  and 3.3.2 loads byte fields differently in Thumb code
  (`eff_cvolslide`).
- 3.0.4 was not tested; like all of 3.0, it builds only for a 32-bit
  host.

Over the unmodified public source, 3.0.2 reproduces 20 functions exactly
against 9 for 3.2.2.

Build details that the bytes depend on:

- GCC before 3.3 left `__arm__`/`__thumb__` to the driver; the build
  defines them for `cc1` (`tools/c/compile_c.py`).
- The original assembler filled an `.align` inside a section with zeros,
  and padded only the end of a code section with `nop`. Today's gas pads
  both with `nop`, so the build gives the compiler's `.align` directives
  an explicit zero fill.

## Reproducing

`nix develop` provides `agbcc` and `old_agbcc`, and `arm-elf-cc1-3.0.2`
for Krawall; `flake.nix` pins their sources. `just compare` links each library object above from its
`libgcc.a`/`libc.a`; `tools/c/compile_c.py` holds the game code's flags.
