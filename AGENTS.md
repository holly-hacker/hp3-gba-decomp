# Agent guide

Matching decompilation of *Harry Potter and the Prisoner of Azkaban* for the
Game Boy Advance (Griptonite Games / EA, 2004). All code is decompiled: both
USA/Europe (`us`) and Japan (`jp`) build byte-identical ROMs from the C,
assembly and asset sources in this repository. Verify each version
independently.

## Hard rules

1. **Preserve matching.** Every commit must keep both ROM builds byte-identical
   to their verified baseroms.
2. **Keep ROM content out of git.** Do not commit donor ROMs, extracted game
   assets, or raw ROM blobs. Local asset source under `data/` must be ignored.
3. **Keep the matching toolchain fixed.** Use the compiler profiles in
   `tools/c/compile_c.py`; do not upgrade or reflag the compiler.
4. **Verify ROM claims against bytes.** Compute address, offset, size, and
   stride arithmetic with a script, never mentally.
5. **Commit curated knowledge, written standalone.** Regenerable output
   belongs in ignored directories (normally `build/`). Docs, comments, and
   commit messages state current facts, without conversation history or
   session references.

The user commits and pushes. Do not run `git commit` without explicit
authorization for that specific commit. Never run `git push`. Commit messages
identify the functions, regions or subsystem changed; omit agent session
trailers and retain applicable `Co-Authored-By` attribution.

The top-level `README.md` and `mdbook/` are human-maintained: propose
corrections to the user instead of editing them. Preserve unrelated work and
local asset edits.

## Repository map

- `regions.{us,jp}.txt`: build manifests (`c-file` rows, assembly, asset
  directives). `functions.{us,jp}.cfg`: function names and ARM/Thumb entry
  points. `ram_symbols.{us,jp}.inc`: RAM symbol addresses. Keep all sorted
  by address.
- `src/` and `include/`: game C, organized by the code blocks in
  `tools/rom_layout.json`.
- `3rd_party/krawall/`: the Krawall audio library (LGPL-2.1-or-later),
  headers in `include/3rd_party/krawall/`.
- `graphics/<feature>.yaml`: graphics groups shared by both versions.
- `docs/`: compiler notes, manifest row kinds (`docs/c.md`) and data
  formats (`docs/formats/`).
- `build/<ver>/`: generated objects, linker script, disassembly and ROM.

## C code

Read `docs/compiler.md` and `docs/c.md` before changing C. Game C is Thumb
with interworking, compiled with GCC `2.9-arm-000512` (agbcc); Krawall uses
GCC 3.0.2. Apply every change to both US and JP and verify both builds.

Use C89 and existing types from `include/`. Raw pointers (casts of integer
addresses) must never appear in C code; the only exception is
`include/hw/io_regs.h`. RAM variables are `extern` declarations with
addresses in `ram_symbols.<ver>.inc`.

Krawall follows the public Krawall source (commit `9a2b869`): keep its
layout, names, formatting and comments, and mark each difference with a
`// HP3-GBA: <what differs>` comment. The style rules above do not apply.

## Assets

`extract` converts the donor ROM into local editable `data/` source; `pack`
converts that source into build input; `dump` produces analysis output.
Extraction can overwrite local edits: never run it over hand-edited assets.
New formats are documented in `docs/formats/`, follow the existing
extractor/packer pattern under `tools/`, and must round-trip byte-exactly.

## Commands and validation

Run commands from the repository root inside `nix develop` (or
`nix develop -c <command>`); `just --list` shows recipes, which default to
`us`. On a fresh checkout, supply `baserom.{us,jp}.gba`, run `just setup`,
then `just extract-all`.

- `just compare <ver>`: build and compare the ROM byte for byte.
- `just diff-region <name> <ver>`: instruction differences in a region.
- `just check-all`: every check for both versions. Run before proposing a
  commit.

Report what was verified and any unavailable checks without claiming an
unrun build matches.
