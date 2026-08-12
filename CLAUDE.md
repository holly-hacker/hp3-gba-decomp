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
   confirmed against the actual binary before being encoded in configs or docs.
5. **Never commit deterministically generated content.** If a script can regenerate a file
   byte-for-byte from the baserom plus already-tracked inputs (raw Luvdis disassembly dumps,
   objcopy'd ROM images, extracted-but-unconverted assets), it belongs in `build/` (gitignored)
   and is produced by a `just` recipe, not committed. Commit only the curated inputs that
   encode actual reverse-engineering knowledge or decisions: function-boundary configs,
   symbol names, hand-written/decompiled/matched code, manually converted assets, docs. Keep
   such config per-version (`functions.us.cfg` / `functions.jp.cfg`, not one shared file).

## Game facts (researched, verified where noted)

- Developer Griptonite Games, publisher EA, released May 2004. Sole credited programmer
  (Michael Dorgan) — expect a small, single-author codebase.
- **Two ROM versions**: USA/Europe cart (multi-language: En,Fr,De,Es,It,Nl,Da) and Japan
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
    (e.g. `kramStop`, `kramSetVol`, `kramSetPan`, `kramWorker`). See `docs/memory-map.md` for
    full findings, candidate function addresses, and their confidence levels.
  - Music/samples can be ripped to .xm/.s3m with UnkrawerterGBA
    (https://github.com/MCJack123/UnkrawerterGBA) and rebuilt with Krawall's `krawerter`.
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

## Current phase: bootstrap (keep it simple)

Get a minimal workflow going first; expand tooling later (see "Target toolchain" below).

Actual layout so far (both ROM versions supported throughout, not just US):

```
├── flake.nix              # nix develop: gcc-arm-embedded, luvdis + capstone (pinned inline,
│                           #   luvdis isn't in nixpkgs), just, mgba. flake.lock is committed.
├── justfile                # setup, disasm/build/compare (all take ver="us"|"jp")
├── .gitignore              # baserom*.gba, gba_bios.*, *.sav, build/, *.o, *.elf
├── baserom.us.gba          # user-supplied (gitignored)
├── baserom.jp.gba          # user-supplied (gitignored)
├── gba_bios.bin            # user-supplied (gitignored), optional -- only needed for mGBA/gdb
│                           #   dynamic debugging, not for the matching build
├── rom.us.sha1, rom.jp.sha1 # pinned donor-ROM hashes
├── ld_script.us.ld, ld_script.jp.ld  # fixed-address layout, per version
├── functions.us.cfg, functions.jp.cfg  # curated Luvdis function-boundary configs (committed)
├── asm/                    # reserved for split/hand-verified matched content -- currently
│                           #   empty; the full-ROM disassembly is NOT tracked here (see below)
├── build/                  # gitignored. `just disasm/build/compare` regenerates
│                           #   build/<ver>/rom.s -> .o -> .elf -> .gba from scratch every time
├── data/                   # data sections (.incbin from baserom initially)
├── symbols.us.txt          # known function/data symbols -- not yet created
├── tools/                  # small python tools (compare, later extractors) -- currently
│                           #   empty; ad hoc investigation scripts are not committed, but
│                           #   reusable analysis helpers should go here as they're written
└── docs/                   # compiler.md, memory-map.md -- notes with explicit confidence
                            #   levels (PROVEN / STRUCTURAL MATCH / UNCONFIRMED), keep using
                            #   that convention for new findings
```

Bootstrap task order (status as of this writing):

1. [x] `flake.nix` + `justfile` + `.gitignore`; `just setup` verifies both baserom sha1s.
2. [x] (preliminary) Fingerprinted the compiler -- working hypothesis is ARM ADS/RVCT, not
   GCC/agbcc. See `docs/compiler.md` for the two structural signals found and what's still
   needed for a byte-level proof.
3. [x] Located Krawall in both ROMs (embedded `$Id` revision tag) and found candidate driver
   functions. See `docs/memory-map.md` for addresses and confidence levels.
4. [x] Full-ROM matching disassembly with Luvdis, for both versions:
   `just disasm us` / `just disasm jp` (wraps `luvdis disasm baserom.<ver>.gba -c
   functions.<ver>.cfg -o build/<ver>/rom.s`). Output is regenerated on demand, never
   committed -- see hard rule 5. Feed newly-discovered functions back into
   `functions.<ver>.cfg` (the curated config, which IS committed) as they're found.
5. [x] First matching build, both versions: `just compare us` / `just compare jp` -- assembles,
   links (`ld_script.<ver>.ld`), objcopys (`--gap-fill 0xFF`), and confirms byte-identical to
   the donor ROM via `cmp`. This is the permanent regression baseline; every future commit
   must keep both passing.
6. [ ] Not started: split the disassembly into modules; start an `asm/nonmatchings/`
   per-function layout (needed later for objdiff/Mizuchi/decomp.me context generation). Only
   commit content here once it's actually been split/verified/named -- not a raw dump.

Ghidra (language `ARM:LE:32:v4t`) for analysis/labeling alongside; sync names into
`symbols.us.txt` and the Luvdis config.

Dynamic verification (mGBA + gdb, via mGBA's `--gdb` stub) was attempted for Krawall function
identification and was inconclusive -- see `docs/memory-map.md`'s "Dynamic verification
attempt" section before retrying that path; the stub's breakpoint/continue sequencing was
unreliable across many attempts and the root cause was never identified.

## Build principles

- Donor-ROM flow: clone → `nix develop` → place `baserom.us.gba` + `baserom.jp.gba` →
  `just setup` → `just compare us` / `just compare jp`. All `just` recipes take
  `ver="us"|"jp"` (default `us`) and are already wired for both versions today, not "later."
- Fixed-address linker script per version; every object placed at its original address, so
  per-object matches compose into a whole-ROM match.
- Unmapped regions: `.incbin "baserom.us.gba", <offset>, <size>` in `data/*.s`. Progress =
  replacing incbin ranges with real asm/C/converted assets.
- Asset pipeline (later): editable formats in repo (.png, .xm, .json) converted at build
  time to console formats (gbagfx for graphics; custom extractors for Griptonite formats).
  Round-trips are enforced by the final sha1 compare.
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

- Function names: `sub_<ADDR>` until identified, then descriptive names; keep
  `symbols.us.txt` as the authoritative name map.
- asm style: Luvdis/pret-compatible macros; Thumb default, ARM marked explicitly.
- Document every reverse-engineered format in `docs/formats/` before writing an extractor.
- Commit messages: state what region/function was matched or symbolized.

## Reference projects & tools

- pret pokeemerald / pokeruby / pmd-red — canonical GBA layout; pmd-red = asm-first model.
- Dream-Atelier/kl-eod-decomp — modern small-game template with AI integration.
- aarant/luvdis — matching disassembler. decomp.wiki/platforms/game-boy-advance — scene hub.
- GBATEK (https://www.problemkaputt.de/gbatek.htm) — hardware reference.
