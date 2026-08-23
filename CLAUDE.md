# CLAUDE.md — Harry Potter and the Prisoner of Azkaban (GBA) decompilation

Matching decompilation of *Harry Potter and the Prisoner of Azkaban* for the Game Boy Advance
(Griptonite Games / EA, 2004). Modeled on pret-style GBA decomps (pokeemerald, pmd-red) and
newer configure-based projects (kl-eod-decomp, dtk-template).

## Hard rules (never violate)

1. **Bit-perfect at every commit.** Every commit must produce a byte-identical ROM for every
   supported version (`sha1sum -c`). A change that breaks matching does not get committed.
2. **No copyrighted content in git.** Never commit the ROM, extracted assets, or raw binary
   blobs from the ROM. Donor ROMs (`baserom.<ver>.gba`) are gitignored and supplied by the
   user. Unimplemented regions are pulled from the baserom at build time (`.incbin` /
   extraction step).
3. **The compiler and its flags are fixed by matching.** Never "upgrade" or reflag the target
   compiler once identified. Modernize build orchestration only.
4. **Verify, don't assume.** Any claim about the ROM (compiler, formats, offsets) must be
   confirmed against the actual binary before being encoded in configs or docs. Compute any
   address/offset/hex arithmetic (table bases, struct offsets, `addr - base`, index*stride,
   etc.) via an actual calculator (e.g. `python3 -c "..."`), never by hand or mentally — manual
   arithmetic on addresses is a routine, easy-to-miss source of off-by-N errors that silently
   invalidate everything built on top of them.
5. **Never commit deterministically generated content.** If a script can regenerate a file
   byte-for-byte from the baserom plus already-tracked inputs (raw disassembly dumps,
   objcopy'd ROM images, extracted-but-unconverted assets), it belongs in `build/` (gitignored)
   and is produced by a `just` recipe, not committed. Commit only the curated inputs that
   encode actual reverse-engineering knowledge or decisions: function-boundary configs,
   symbol names, hand-written/decompiled/matched code, manually converted assets, docs. Keep
   such config per-version (`functions.us.cfg` / `functions.jp.cfg`, not one shared file).
6. **Docs, commit messages, and code comments describe current state only, never the
   past.** No narrating what was tried, guessed, or gotten wrong before landing on the current
   finding; no "was named X until now"/"renamed from Y" framing; no rebuttal phrasing ("not
   X", "isn't Y") aimed at a hypothesis only a prior conversation knows about; no "this
   session"/"this pass"/"just now"/"now confirmed"/"now identified"-style references to the
   conversation in which the finding was made. State the fact and its rationale as true on
   their own terms — write every sentence as if a reader with no memory of any prior
   conversation is seeing it cold. A dead-end worth steering future work away from can stay,
   but phrased as forward-looking guidance ("not located", "X is a dead end because Y"), not
   as a correction to something the reader never saw.

## Game facts (researched, verified where noted)

- Developer Griptonite Games, publisher EA, released May 2004. Sole credited programmer
  (Michael Dorgan) — expect a small, single-author codebase.
- **Two ROM versions**: USA/Europe cart (multi-language: English US, English UK,
  French, German, Spanish, Italian, Dutch, Danish -- 8 languages) and Japan
  ("Harry Potter to Azkaban no Shuujin"). Verify exact dumps against the No-Intro DAT.
  Long-term goal: one codebase builds both.
- **Audio: Krawall engine (confirmed, located in both ROMs).** Krawall is an XM/S3M module
  player, open-sourced under LGPL v2.1: https://github.com/sebknzl/krawall
  - Directly confirmed via an embedded CVS `$Id: Krawall $Date: 2003/09/01 06:51:01 $` tag
    present verbatim in both ROMs (US `0x08FA9541`, JP `0x08F3C9CC`) -- proves the actual
    Krawall source was compiled in, not reimplemented, and pins the exact upstream revision.
  - The **current public GitHub repo is NOT that revision** -- its git history starts in
    2013 and its source carries no `$Id` tags at all. Do not expect to diff against it for
    byte-level function identification; it's useful only as an API-shape/naming reference
    (e.g. `kramStop`, `kramSetVol`, `kramSetPan`, `kramWorker`). See
    `docs/memory-map/krawall.md` for full findings, candidate function addresses, and their
    confidence levels.
  - Music/sample content is curated JSON+WAV under `data/audio/`, extracted once per clone
    and packed to byte-exact assembly on every build, like every other `data/` subsystem
    (see Build principles). Content is version-independent -- proven byte-identical between
    US/JP -- so only addresses differ per version. `docs/formats/krawall.md` has the format
    writeup and the field decoding the packing relies on.
  - License note: LGPL — do not vendor Krawall source into the repo without resolving
    license compatibility; document in CONTRIBUTING.
- **Compiler: preliminary working hypothesis is ARM ADS/RVCT (`armcc`), NOT GCC/agbcc.**
  Two independent structural signals found directly in the ROM (see `docs/compiler.md` for
  full detail, confidence levels, and remaining confirmation steps):
  - The unsigned-divide routine at `0x080002E0` uses a 32-way binary-search branch tree
    (`cmp r1, r0, lsr #N` cascade) -- armcc's division algorithm shape, not GCC's compact
    shift-subtract `__udivsi3` loop.
  - The div/mod wrapper at `0x080002A4` returns its remainder through a pointer parameter
    (passed in r2), matching armcc's `__rt_sdiv`-family calling convention. GCC never does
    this -- it has flatly separate `__divsi3`/`__modsi3`/`__udivmodsi4` functions.
  - **Not yet a byte-level proof.** Still needs either a reference armcc/ADS-compiled binary
    to diff against, or an IDA/Ghidra RVCT signature pack. Until confirmed, do not commit to
    the agbcc-fork tooling path (cf. kl-eod-decomp's `-ftst` fork) -- an ADS/RVCT-oriented
    toolchain may be required instead. Krawall shipping with GCC-oriented build scripts
    upstream is not proof of the game's own compiler; the driver code can be (and evidently
    was) linked into a non-GCC binary.
- No existing decomp of this game. Related-but-empty: SimsAdvanceRet/UrbzGBADecomp (same
  studio/era; watch for shared engine code).

## Current phase: reverse-engineering and asset extraction

The bootstrap is done: both versions build byte-identical from a manifest, and five asset
subsystems round-trip through curated `data/` source.

Day-to-day work is **understanding the game's data and getting it out of the ROM** -- locating
a table or format, proving its layout against the actual bytes, writing it up in `docs/`, and
where it's real content, giving it an `extract`/`pack` pipeline into `data/` so it becomes
editable source instead of opaque `.incbin`. Typical subjects: level/map tables and their
bounding boxes, image and tile assets, story/quest progression state, item and chest
placement.

**Do not extract code into `asm/*.s` unless explicitly asked to** -- not a priority, not
required. Read functions freely (that's how formats get confirmed), then record what they do
in `docs/`, name them in `functions.<ver>.cfg`, and leave their bytes as `.incbin`.

New asset subsystem: follow the existing pattern rather than inventing one -- format
documented in `docs/formats/`, `extract_<x>.py`/`pack_<x>.py`/`<x>_codec.py` under
`tools/<x>/`, a `regions.<ver>.txt` directive taught to `gen_rom_s.py`, both recipes in the
justfile and `extract-all`, `data/<x>/` gitignored, round-trip proven by `just compare`.

Actual layout so far (both ROM versions supported throughout, not just US):

```
├── flake.nix               # dev shell (arm-none-eabi, patched gbadisasm, unkrawerter,
│                           #   python+capstone/unicorn, just, mgba). flake.lock committed.
├── patches/                # local fixes for unmaintained gbadisasm / unkrawerter bugs
├── justfile                # task runner; most recipes take ver="us"|"jp" (default us)
├── baserom.{us,jp}.gba     # user-supplied, gitignored. gba_bios.bin too (mGBA debugging only)
├── rom.{us,jp}.sha1        # pinned donor-ROM hashes
├── ld_script.{us,jp}.ld    # fixed-address layout, per version
├── functions.{us,jp}.cfg   # curated gbadisasm arm_func/thumb_func seeds -- it has no
│                           #   function discovery of its own
├── regions.{us,jp}.txt     # the manifest: extracted byte ranges (address, end, source,
│                           #   name), plus `label` lines naming addresses inside still-raw
│                           #   territory. Directive rows (krawall-module, dialog-text,
│                           #   monster-table, ...) point at data/ instead of a file.
├── macros.inc, ram_symbols.{us,jp}.inc, krawall_names.txt  # asm macros; named addresses;
│                           #   module/sample name overrides
├── asm/                    # committed regions the manifest points at. asm/krawall/ is NOT
│                           #   one -- it's the gitignored dump from `just dump-krawall`.
├── data/                   # curated, editable asset source -- ALL gitignored, same footing
│                           #   as the baserom (hard rule 2). One subdir per subsystem,
│                           #   bootstrapped by `just extract-all`, packed by `just pack-<x>`.
├── build/                  # gitignored, fully regenerated by `just`
├── tools/                  # one dir per subsystem, plus gen_rom_s.py (manifest -> build
│                           #   input) and match_functions.py (US<->JP address matching)
└── docs/                   # compiler.md, memory-map*.md, formats/*.md -- every finding
                            #   marked PROVEN / STRUCTURAL MATCH / UNCONFIRMED; keep doing that
```

Bootstrap task order:

1. [x] `flake.nix` + `justfile` + `.gitignore`; `just setup` verifies both baserom sha1s.
2. [x] (preliminary) Fingerprinted the compiler -- working hypothesis is ARM ADS/RVCT, not
   GCC/agbcc. See `docs/compiler.md` for the two structural signals found and what's still
   needed for a byte-level proof.
3. [x] Located Krawall in both ROMs (embedded `$Id` revision tag) and found candidate driver
   functions. See `docs/memory-map/krawall.md` for addresses and confidence levels.
4. [x] Full-ROM matching disassembly, for both versions, via `gbadisasm` (chosen over
   alternatives for its `arm_func`/`thumb_func` config support, needed since crt0, the
   division routines, and the Krawall driver are all confirmed ARM-mode). Feed
   newly-discovered functions back into `functions.<ver>.cfg` (committed) as they're found.
   `just disasm-compare` reassembles that full disassembly and checks it's still
   byte-identical to the donor ROM -- run it after touching `functions.<ver>.cfg` to catch
   bad seeds (misaligned/duplicate function boundaries) that `gbadisasm` doesn't itself
   reject. Secondary to `just compare` (see task 5), not a substitute for it.
5. [x] First matching build, both versions -- `just compare` stitches `regions.<ver>.txt`
   into the actual build input, assembles, links, objcopys, and confirms byte-identical to
   the donor ROM. This is the permanent regression baseline; every future commit must keep
   both passing.
6. [~] Ongoing (no end state): asset/data extraction into `data/`, manifest-driven via
   `regions.<ver>.txt` -- see the phase note above for what this involves and how a new
   subsystem gets added. Everything not in the manifest stays raw `.incbin`, which is a
   fine resting state, not a debt to pay down.


Ghidra (`ARM:LE:32:v4t`) carries most analysis/labeling; sync confirmed names into
`functions.<ver>.cfg`. It can mis-mark data as code and get ARM/Thumb wrong -- on any
disagreement `build/<ver>/full_disasm.s` is ground truth -- and a negative search in both it
and `gbadisasm` isn't proof code doesn't exist. The `.gpr` isn't in git and has no rollback:
single-address edits are fine, confirm before wide-reaching or scripted ones.

Dynamic verification: use **mGBA's own debugger console** (`watch`/`break`/`continue`/
backtrace), driven interactively by the user. It works reliably and answers what static
tracing can't -- see the IWRAM-install and palette-queue findings in
`docs/memory-map/krawall.md` and `docs/formats/graphics.md`.

Do **not** use mGBA's `--gdb` remote stub: its breakpoint/continue sequencing proved
unreliable across many attempts and the root cause was never identified -- see
`docs/memory-map/krawall.md`'s "Dynamic verification attempt" section before spending time
on that path. `gba_bios.bin` is required either way.

## Build principles

- Donor-ROM flow: clone → `nix develop` → place both baseroms → `just setup` →
  **`just extract-all`** → `just compare us` / `just compare jp`. `extract-all` is required,
  not a convenience: `data/` is gitignored, so a fresh clone has none of it and `pack-*`
  fails with a size mismatch rather than a useful message. Once per clone; it overwrites, so
  don't re-run it over local hand-edits.
- Verbs: **extract** = ROM → `data/` (once per clone), **pack** = `data/` → assembly (every
  build), **dump** = ROM → files for reading only, never build input.
- Fixed-address linker script per version; every object placed at its original address, so
  per-object matches compose into a whole-ROM match.
- Unmapped regions: raw `.incbin` from the baserom, generated by `tools/gen_rom_s.py` for
  whatever `regions.<ver>.txt` doesn't cover. Progress is measured in understanding written
  down in `docs/` and content moved into curated `data/` source -- not in how much of the
  ROM has left `.incbin`.
- Asset pipeline: same manifest-driven model as code, not a separate system -- extractors
  run against the user's local ROM. Krawall audio is the first real case (see above): unlike
  code, the manifest rows are machine-generated (deterministic struct parsing, not human
  judgement), but they're still committed -- addresses/names are curated knowledge either
  way. What's NOT committed is the asset content itself -- actual game assets (art, audio,
  etc.) sit on the same footing as the baserom under hard rule 2, regardless of how
  mechanically they were located. Krawall audio lives as curated, editable JSON+WAV under
  `data/audio/` (bootstrapped once locally, not regenerated automatically -- see above),
  gitignored. Round-trips are enforced by the final sha1 compare regardless.
- `-DVERSION_JP`-style C-level version switching is still "later" -- not relevant yet since
  no C code exists; today's per-version handling is entirely at the asm/linker-script/config
  layer (see hard rule 5 and the layout above).

## Target toolchain (end state — document only, don't build yet)

- **Layers**: Nix (pinned packages via flake + binary cache) → Just (human/agent commands)
  → `configure.py` + Ninja (build graph). Single source of truth: per-version YAML segment
  config + `symbols.<ver>.txt`; configure.py generates ninja rules, linker scripts,
  extraction/conversion rules, objdiff config, decomp.me context.
- **Compiler**: whatever fingerprinting fully confirms. Current working hypothesis is ARM
  ADS/RVCT (`armcc`), not agbcc/GCC (see Game facts above and `docs/compiler.md`) -- if that
  holds up, the objdiff/m2c/decomp-permuter-agbcc/decomp.me tooling below (all GCC/agbcc
  -oriented) will need ADS/RVCT-compatible equivalents, not just an agbcc fork. Don't build
  out this layer until the compiler question has a byte-level answer.
- **Matching workflow**: objdiff / objdiff-cli for per-object verification and JSON
  progress reports; m2c for initial C drafts; decomp-permuter-agbcc for fishing matches;
  decomp.me for collaborative scratches (GBA/agbcc presets).
- **Progress tracking**: decomp.dev and/or frogress (progress.deco.mp) badges, fed from
  the local/self-hosted full build.
- **AI agents**: Mizuchi (https://github.com/macabeus/mizuchi) pipeline — needs GNU ld map
  file, `asm/nonmatchings/` dirs, generated ctx.c. Thumb functions are the tractable ones;
  ARM-mode code (Krawall mixer, IWRAM routines) stays asm longer.
- **Testing**: `just check` = configure + build + compare + objdiff report (JSON). Headless
  mGBA harness for boot/scenario tests — the oracle for future shiftable/mod builds where
  sha1 no longer applies.
- **CI split**: public CI builds tools + compiles C + lints (no ROM); full compare runs
  locally or on a self-hosted runner that has the ROMs.
- **Moddability roadmap**: matching build → symbolize all pointer-bearing data →
  full asset extraction → shiftable build (second linker-script mode with free placement).
  Keep `just compare` as the permanent regression oracle alongside the shiftable mode.

## Conventions

- Function names: `sub_<ADDR>` until identified, then descriptive names, tracked in
  `functions.<ver>.cfg`/`regions.<ver>.txt`.
- asm style: pret-convention macros (`macros.inc`, from `pret/pokeemerald`'s
  `asm/macros/function.inc`); Thumb default, ARM marked explicitly.
- Document every reverse-engineered format in `docs/formats/` before writing an extractor.
- `just check-all` is the gate for hard rule 1: it verifies both donor sha1s, then the full
  disassembly and the stitched build for both versions. Run it before proposing a commit.
  (`just check` is a different, not-yet-built thing -- see "Target toolchain".)
- Commit messages: state what region/function was matched or symbolized. No `Claude-Session:`
  trailer; keep `Co-Authored-By`.
- **The user commits and pushes; you don't.** Never run `git commit` without being told to,
  in words, for that specific commit -- an instruction to do work, or approval of an earlier
  commit, is not approval for the next one. Never run `git push` at all.
- Don't add a row to `regions.<ver>.txt` until the region's true, complete extent is
  confirmed (for a function: every reachable branch walked to genuine termination; for a
  table: its real row count and stride) -- `just compare`'s sha1 check can't catch a
  truncated-but-plausible boundary, since the unclaimed remainder just becomes opaque
  `.incbin` bytes next door. If unsure, leave it as `.incbin` and track it as a candidate
  in `docs/` instead.

## Reference projects & tools

- pret pokeemerald / pokeruby / pmd-red — canonical GBA layout; pmd-red = asm-first model.
- Dream-Atelier/kl-eod-decomp — modern small-game template with AI integration.
- camthesaxman/gbadisasm — matching disassembler (patched, see `patches/gbadisasm/`).
- decomp.wiki/platforms/game-boy-advance — scene hub.
- GBATEK (https://www.problemkaputt.de/gbatek.htm) — hardware reference.
