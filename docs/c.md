# Writing C

The compiler and its flags are in [`compiler.md`](compiler.md). This is
what to know before adding a `c-file` region.

## The pipeline

A `c-file <start> <end> <source.c> <name>` row in `regions.<ver>.txt`
points at a `.c` under `src/`. `tools/c/compile_c.py` runs it through the
system `cpp` and then `agbcc`, and `tools/gen_link.py` wraps the result as
the region's object. Two flag profiles, by directory:

| | compiler | flags |
|---|---|---|
| `src/libc/` | `old_agbcc` | `-O2 -fno-builtin`, no interworking |
| everything else | `agbcc` | `-O2 -mthumb-interwork -fhex-asm -Werror` |

`-fhex-asm` is agbcc-only and prints immediates as hex; it changes no
bytes. A trailing `.align 2, 0` is appended to every compiled region,
supplying the zero fill the ROM has -- without it the assembler pads Thumb
sections with `mov r8, r8`.

## Preprocessor: modern. Language: C89.

The two halves of the pipeline are from different eras, and the line
between them is where `cpp` hands off to `agbcc`.

Anything with a `#` is handled by a current `cpp` and never reaches
agbcc, so `#pragma once`, `//` comments and arbitrarily involved macros
are all free.

Everything below that is C89, because agbcc is a 2000-vintage compiler.
No declarations after statements, no `stdint.h` (use `include/types.h`),
no `bool`. Designated initializers are untested in either syntax.

Modern `cpp` will also accept constructs the original toolchain could not
have -- variadic macros, `_Pragma`. Those still match, but they make the
source something the 2003 developer could not have written.

## Constraints that affect matching

**One region per file, and a file is either all data or all code.**
agbcc emits `.rodata` before `.text` regardless of the order things
appear in the source, so a file holding both a table and a function
cannot reproduce a ROM that has them the other way round.

**Structs round up to 4 bytes.** agbcc sets
`arm_structure_size_boundary = 32`. A struct whose fields total 3 bytes
occupies 4, and getting this wrong shifts every subsequent offset.

**RAM variables are `extern`, never definitions.** `int g_foo;` becomes a
common symbol the linker places wherever it likes, but RAM addresses are
fixed by the ROM. Declare it `extern` in C and give it an address in
`ram_symbols.<ver>.inc`. `compile_c.py` rejects `.data`/`.comm` rather
than letting them vanish.

**`const` data is folded into `.text`.** The generated linker script
places each region's `.text` only. `compile_c.py` rewrites
`.section .rodata`, which changes no bytes -- both live in ROM.

Shared constants and types belong in `include/`, so a wrong row count or
struct layout is a compile error rather than a silently shifted table.

## Iterating on a function that does not match

`just compare` reports a byte offset in a 16 MB image; `check_sections.py`
catches only wrong size or address. To see what actually differs:

```sh
just diff-region <name>          # us
just diff-region <name> jp
```

It disassembles the region from the donor ROM and from the build side by
side, marking differing instructions. Mode comes from
`functions.<ver>.cfg`, overridable with `--arm`/`--thumb`. For data
regions read the hex column; the mnemonics are meaningless there.

## Choosing what to convert

Good first candidates are small, leaf (no calls out), free of
data-symbol references, and already extracted to `asm/` so there is a
byte-exact reference to diff against. Anything ARM-mode is out: the SDK's
ARM compiler does not build on a modern host, so that code stays as
assembly.
