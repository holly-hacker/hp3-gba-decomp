# Writing C

The compiler and its flags are in [`compiler.md`](compiler.md). This is
what to know before changing C.

## The pipeline

A `c-file <source.c> <name>` row in `regions.<ver>.txt`
points at a `.c` under `src/`. The build (`build/build.ninja`, written by
`tools/configure.py` with the flags of `tools/c/compile_c.py`) runs it
through the system `cpp` and then `agbcc`, and assembles the result into
the region's object; Ninja reruns a step only when its source or a header
it read changed. The flags are `-O2 -mthumb-interwork -fhex-asm -Werror`.

A `c-file-O1` row uses the same compiler and flags with `-O1` in place of
`-O2`. The EEPROM driver (`src/eeprom/`) matches only under `-O1`.

A `c-file-arm` row compiles ARM-mode code with `agbcc_arm` and
`-O2 -mthumb-interwork -fomit-frame-pointer -Werror` (no `-fhex-asm`,
which it lacks).

A `c-file` row places its object's `.text`. A `c-rodata <name>` row
places the `.rodata` of the C row named `<name>`, its `const` data, in
the read-only data part of the manifest. A file that holds only data
still has its `c-file` row in the code part, at the start of its folder,
where its `.text` is empty. A `c-data <name>` row likewise places the
object's `.data`, initialised non-const data such as
`char *table[] = { "..." }`: the pointer table goes to `.data` and its
strings to `.rodata` (`src/gamecube/joybus_error_strings.c`).

Third-party code under `3rd_party/` (Krawall) has its own rows, compiled
with GCC 3.0.2 at `-O3` ([`compiler.md`](compiler.md)) from headers in
`include/3rd_party/<lib>/`:

- `c-file-gcc3 <source.c> <name>` for Thumb C, `c-file-gcc3-arm` for
  ARM C, and `asm-file-cpp` for a preprocessed `.S`. The row places the
  object's `.text`; an object without code is still declared this way.
- These objects keep `.text`, `.rodata`, `.iwram` and `.ewram` apart.
  `c-rodata <name>` places `.rodata`, and `c-iwram <name> [<address>]`
  and `c-ewram <name> [<address>]` the sections Krawall copies to IWRAM
  and EWRAM: stored in ROM, linked at their RAM address. The first
  `c-iwram` and `c-ewram` row gives the address; the rows after it follow
  on.
- The link fails on an object with a non-empty section that no row
  places.

Third-party source follows its upstream style rather than the rules
below.

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

Game code is compiled with `VERSION_US` or `VERSION_JP` defined. Share one
source between the versions and wrap only the differing code in `#ifdef`.

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
`ram_symbols.<ver>.inc`.

**The link fails on unplaced data.** A C object's row places only its
`.text`. Its `.rodata` (`const` data) needs a `c-rodata` row, its `.data`
a `c-data` row; these and any `.comm`/`.bss` otherwise fail the link with
"an object has a section that no regions.<ver>.txt row places", followed
by an `unplaced: <object>: <section> (<size> bytes)` line for each.

Shared constants and types belong in `include/`, so a wrong row count or
struct layout is a compile error rather than a silently shifted table.

## Finding a mismatch

`just compare` names the region holding the first differing byte, skipping
pointers and branch offsets the linker filled in, which change whenever
their target moves. To see what actually differs:

```sh
just diff-region <name>          # us
just diff-region <name> jp
```

It disassembles the region from the donor ROM and from the build side by
side, marking differing instructions. Mode comes from the row's
directive, or for assembly from the source's first mode directive,
overridable with `--arm`/`--thumb`. For data
regions read the hex column; the mnemonics are meaningless there.
