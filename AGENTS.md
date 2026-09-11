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
5. **Commit knowledge, not generated dumps.** Track curated boundaries,
   symbols, code, format definitions, and documentation. Regenerable build and
   analysis output belongs in ignored directories, normally `build/`, with a
   reproducible command. Keep address-bearing configs per version.
6. **Write standalone, current-state documentation.** Docs, comments, and
   commit messages should explain the resulting facts and rationale without
   conversation history, abandoned guesses, or session references.

The user commits and pushes. Do not run `git commit` without explicit
authorization for that specific commit. Never run `git push`. Commit messages
should identify the function or region matched or symbolized; omit agent
session trailers and retain applicable `Co-Authored-By` attribution.

`README.md` is human-maintained: propose corrections to the user instead of
editing it. Preserve unrelated work and local asset edits.

## Repository map

- `functions.{us,jp}.cfg`: curated function names and ARM/Thumb entry points
  for gbadisasm. Keep sorted by address.
- `regions.{us,jp}.txt`: build manifests for assembly, `c-file` regions, asset
  directives, and labels inside raw regions. Keep sorted by address.
- `src/`, `include/`: matching C, reconstructed tables, shared types and
  declarations. `src/libc/` uses the separate newlib compiler profile.
- `asm/`, `macros.inc`: curated assembly and function macros. The ignored
  `asm/krawall/` directory contains analysis dumps, not build inputs.
- `ram_symbols.{us,jp}.inc`: fixed RAM symbol addresses.
- `tools/c/`, `tools/matching/`: production compilation and candidate matching.
- `tools/manifest.py`, `tools/gen_link.py`, `tools/check_sections.py`: manifest
  parsing, fixed-address linking, and region size/address validation.
- `tools/<subsystem>/`, `data/`: asset codecs and local editable asset source.
- `build/<ver>/`: generated disassembly, assembly, objects, linker script, and
  ROM. Unclaimed manifest ranges are filled from the baserom with `.incbin`.
- `docs/README.md`: findings index and confidence definitions.
  `docs/memory-map/` describes code and RAM; `docs/formats/` describes data.
- `flake.nix`, `flake.lock`, `justfile`: pinned development tools and commands.

## ROM mapping

Read the relevant subsystem documentation and existing symbols before tracing
new code. Record findings in the owning document and link to it from related
documents rather than duplicating facts. Use the confidence levels in
`docs/README.md`: **PROVEN**, **STRUCTURAL MATCH**, and **UNCONFIRMED**.

Use `sub_<ADDR>` for unidentified functions and descriptive names when their
behavior is supported by evidence. Retain `_candidate` for provisional
identifications. Sync confirmed names into the appropriate function config,
manifest, declarations, and documentation where applicable.

Confirm the complete extent before adding a manifest region: walk all reachable
branches to termination, account for literal pools and alignment, and prove
table counts and strides. A truncated region can still pass the whole-ROM
comparison because its remainder is filled from the baserom. Leave uncertain
ranges raw and document the candidate boundaries.

Ghidra is an analysis aid (`ARM:LE:32:v4t`); verify its function boundaries and
ARM/Thumb interpretation against ROM bytes and `build/<ver>/full_disasm.s`.
Disassembler output also depends on curated seeds. Failed discovery or search
does not prove code is absent. Ghidra projects are local and have no repository
rollback: confirm before broad or scripted edits; single-address edits are fine.

`just match-functions --help` exposes US/JP correspondence discovery. Treat
instruction-shape matches as candidates and verify them before transferring
names or adding regions. Do not assume a fixed offset between versions.

For dynamic verification, use mGBA's debugger console interactively with the
user; it requires the local `gba_bios.bin`. Avoid the unreliable `--gdb` remote
stub; see `docs/memory-map/krawall.md` for the debugging findings.

## Matching functions

Read `docs/compiler.md` and `docs/c.md` before adding C regions. The detailed
matching workflow and style references are available to any agent at
`.agents/skills/match-function/SKILL.md`; read them when matching a function.

Use `python3 -m tools.matching --help` to discover the candidate workflow:
`prepare`, `compile`, `compare`, `snapshot`, and bounded permuter commands.
Work on candidates in isolated generated workspaces, confirm their reference
bytes and full extent, and integrate a verified match into `src/` and the
appropriate `c-file` manifest row. Candidate comparison is followed by the
production ROM comparison. Use `just diff-region <name> <ver>` for instruction
differences in an integrated region.

The compiler is GCC `2.9-arm-000512` (agbcc). Game C is Thumb with interworking;
`src/libc/` uses `old_agbcc` without interworking. Exact flags are owned by
`tools/c/compile_c.py`. The available compiler builds do not support ARM C;
keep ARM functions in assembly. Krawall source must not be vendored without
resolving its LGPL licensing; see `docs/memory-map/krawall.md` and
`docs/formats/krawall.md` for engine and format research.

Use C89, existing types from `include/`, and the project's C style. Keep one
region per source file and separate code from data. RAM variables must be
`extern` declarations with addresses in `ram_symbols.<ver>.inc`. Account for
agbcc's four-byte struct size rounding. Reuse shared types and verify layouts
against accesses in the ROM.

## Assets

`extract` converts the donor ROM into local editable `data/` source; `pack`
converts that source into build input; `dump` produces analysis/viewing output.
Extraction can overwrite local edits and must not run automatically on builds.

For a new subsystem, document the format in `docs/formats/`, follow the existing
extractor/packer/codec pattern under `tools/`, add manifest support and Just
recipes where appropriate, and verify byte-exact round trips. Add extraction
to `extract-all` when it supplies required build inputs. Some tools are only
for analysis or only support US; check their implementation and documentation.

## Commands and validation

Run commands from the repository root inside `nix develop`, or with
`nix develop -c <command>`. Use `just --list` for available recipes; versioned
recipes generally default to `us`.

For a fresh checkout, supply `baserom.us.gba` and `baserom.jp.gba`, run
`just setup` to verify their pinned hashes, then `just extract-all` to populate
required local assets. Do not repeat extraction over hand-edited assets.

- `just compare us` / `just compare jp`: compile, pack, link, validate sections,
  and compare the resulting ROM byte for byte against its baserom.
- `just disasm-compare <ver>`: regenerate and reassemble the full disassembly
  and compare against the baserom. Run after changing function seeds; this
  complements the production build comparison.
- `just check-sorted`: validate manifest and function-config ordering.
- `just check-all`: verify donor hashes, full disassembly and production builds
  for both versions, and config ordering. Run before proposing a commit.
- `python3 -m unittest discover -s tools/matching/tests -v`: regression tests
  for changes to matching tools.

Use checks appropriate to the files changed; documentation-only edits need
reference and diff checks. Report what was verified and any unavailable checks
without claiming an unrun build matches.
