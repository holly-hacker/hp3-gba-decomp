# Agent guide

Matching decompilation of *Harry Potter and the Prisoner of Azkaban* for the
Game Boy Advance (Griptonite Games / EA, 2004). Both USA/Europe (`us`) and
Japan (`jp`) have byte-identical builds. Active work is mapping ROM code and
data, documenting their behavior, and decompiling individual functions to
matching C. Asset extraction is also supported where formats are understood.
Coverage differs between versions; verify each version independently.

## Hard rules

1. **Preserve matching.** Every commit must keep both ROM builds byte-identical
   to their verified baseroms. Never commit a change that breaks matching.
2. **Keep ROM content out of git.** Do not commit donor ROMs, extracted game
   assets, or raw ROM blobs. Local asset source under `data/` must be ignored;
   check ignore coverage when adding a subsystem. Curated decompiled code and
   reconstructed C tables follow the existing `src/` conventions.
3. **Keep the matching toolchain fixed.** Compiler versions and flags are part
   of matching. Use the profiles in `tools/c/compile_c.py`; do not upgrade or
   reflag the compiler to make a candidate compile or match.
4. **Verify ROM claims against bytes.** Confirm addresses, instruction mode,
   layouts, and semantics before encoding them as facts. Compute address,
   offset, size, and stride arithmetic with a calculator or script, never
   mentally. Keep hypotheses explicitly marked.
5. **Commit curated knowledge, written standalone.** Track boundaries,
   symbols, code, format definitions, and documentation, per version where
   address-bearing. Regenerable output belongs in ignored directories
   (normally `build/`) with a reproducible command. Docs, comments, and commit
   messages state current facts and rationale, without conversation history,
   abandoned guesses, or session references.

The user commits and pushes. Do not run `git commit` without explicit
authorization for that specific commit. Never run `git push`. Commit messages
should identify the function or region matched or symbolized; omit agent
session trailers and retain applicable `Co-Authored-By` attribution.

The top-level `README.md` and `mdbook/` are human-maintained: propose
corrections to the user instead of editing them. Preserve unrelated work and
local asset edits.

## Repository map

- `functions.{us,jp}.cfg`: function names and ARM/Thumb entry points for
  gbadisasm. `regions.{us,jp}.txt`: build manifests (assembly, `c-file`
  regions, asset directives, labels inside raw regions). Keep both sorted by
  address.
- `ram_symbols.{us,jp}.inc`: fixed RAM symbol addresses.
- `graphics/<feature>.yaml`: graphics groups shared by both versions.
- `src/libc/` uses the separate newlib compiler profile.
- The ignored `asm/krawall/` holds analysis dumps, not build inputs.
- `build/<ver>/`: generated disassembly, objects, linker script, and ROM.
  Unclaimed manifest ranges are filled from the baserom with `.incbin`.
  `build/cache/` is a safe-to-delete content-addressed cache.
- `tools/coverage.py`: manifest coverage by ROM area/kind (and by code block
  with `--blocks`). The per-version code/data areas and named code blocks
  are in `tools/rom_layout.json`, shared with `tools/progress_report.py`.
- `docs/README.md`: findings index and confidence definitions.
  `docs/memory-map/` describes code and RAM; `docs/formats/` describes data.

## ROM mapping

Read the relevant subsystem documentation and existing symbols before tracing
new code. Record findings in the owning document and link to it from related
documents rather than duplicating facts. Use the confidence levels in
`docs/README.md`: **PROVEN**, **STRUCTURAL MATCH**, and **UNCONFIRMED**.

Matched C under `src/` is authoritative: it is verified to compile to the ROM
bytes, so prefer it (and its headers) over prose docs when they disagree. To
name a global, look up its address in `ram_symbols.<ver>.inc` and cite the
symbol rather than the raw address.

Use `sub_<ADDR>` for unidentified functions and descriptive names when their
behavior is supported by evidence. Retain `_candidate` for provisional
identifications. Sync confirmed names into the function config, manifest,
declarations, and documentation.

Confirm the complete extent before adding a manifest region: walk all reachable
branches to termination, account for literal pools and alignment, and prove
table counts and strides. A truncated region can still pass the whole-ROM
comparison because its remainder is filled from the baserom. Leave uncertain
ranges raw and document the candidate boundaries.

Verify function boundaries and ARM/Thumb interpretation against ROM bytes and
`build/<ver>/full_disasm.s`. Failed discovery or search does not prove code is
absent. If available, a Ghidra MCP can be used for additional verification.

`just match-functions --help` proposes US/JP function correspondences. Treat
them as candidates and verify before transferring names or adding regions; do
not assume a fixed offset between versions.

## Matching functions

Read `docs/compiler.md`, `docs/c.md`, and `.agents/skills/match-function/SKILL.md`
before matching. `python3 -m tools.matching --help` lists the candidate
workflow (`prepare`, `compile`, `compare`, `snapshot`, permuter). Work in
isolated generated workspaces, then integrate a verified match into `src/` and
its `c-file` manifest row, and confirm with the production ROM comparison.
`just diff-region <name> <ver>` shows instruction differences in an integrated
region.

The compiler is GCC `2.9-arm-000512` (agbcc); game C is Thumb with
interworking. It cannot build ARM C, so keep ARM functions in assembly. Krawall
source must not be vendored without resolving its LGPL licensing; see
`docs/memory-map/krawall.md` and `docs/formats/krawall.md`.

Match every decompiled function in both US and JP, in the same pass: apply
the same rows and names to JP and verify the JP build.

Use C89 and existing types from `include/`. Raw pointers (casts of integer
addresses) must never appear in C code; the only exception is
`include/hw/io_regs.h`. One region per source file; keep
code and data separate. RAM variables are `extern` declarations with addresses
in `ram_symbols.<ver>.inc`. Account for agbcc's four-byte struct size rounding
and verify layouts against ROM accesses.

## Assets

`extract` converts the donor ROM into local editable `data/` source; `pack`
converts that source into build input; `dump` produces analysis output.
Extraction can overwrite local edits: never run it automatically on builds or
over hand-edited assets.

For a new subsystem, document the format in `docs/formats/`, follow the
existing extractor/packer/codec pattern under `tools/`, add manifest support
and Just recipes, and verify byte-exact round trips. Add extraction to
`extract-all` when it supplies required build inputs. A new graphics format is
a kind module in `tools/graphics/kinds/`; see `docs/formats/graphics.md`.
Some tools are analysis-only or US-only; check before relying on them.

## Commands and validation

Run commands from the repository root inside `nix develop` (or
`nix develop -c <command>`); `just --list` shows recipes, which default to
`us`. On a fresh checkout, supply `baserom.{us,jp}.gba`, run `just setup`
(verifies hashes), then `just extract-all`.

- `just compare <ver>`: compile, pack, link, validate sections, and compare
  the ROM byte for byte against its baserom.
- `just disasm-compare <ver>`: reassemble the full disassembly and compare.
  Run after changing function seeds.
- `just check-sorted`: validate manifest and function-config ordering.
- `just check-all`: all of the above for both versions plus donor hashes. Run
  before proposing a commit.

Use checks appropriate to the files changed; documentation-only edits need
reference and diff checks. Report what was verified and any unavailable checks
without claiming an unrun build matches.
