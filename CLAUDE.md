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

## Game facts (researched, verified where noted)

- Developer Griptonite Games, publisher EA, released May 2004. Sole credited programmer
  (Michael Dorgan) — expect a small, single-author codebase.
- **Two ROM versions**: USA/Europe cart (multi-language: En,Fr,De,Es,It,Nl,Da) and Japan
  ("Harry Potter to Azkaban no Shuujin"). Verify exact dumps against the No-Intro DAT.
  Long-term goal: one codebase builds both.
- **Audio: Krawall engine (confirmed for both versions).** Krawall is an XM/S3M module
  player, open-sourced under LGPL v2.1: https://github.com/sebknzl/krawall
  - Music/samples can be ripped to .xm/.s3m with UnkrawerterGBA
    (https://github.com/MCJack123/UnkrawerterGBA) and rebuilt with Krawall's `krawerter`.
  - The driver code in ROM may be diffable against the LGPL source rather than decompiled.
  - License note: LGPL — do not vendor Krawall source into the repo without resolving
    license compatibility; document in CONTRIBUTING.
- **Compiler: UNKNOWN — first real task.** Fingerprint from the ROM:
  - libgcc helpers (`__udivsi3`, `__divsi3`, ...) → GCC family (agbcc-style workflow, like pret).
  - ARM ADS runtime (`__rt_sdiv`, `__rt_udiv`, ...) → armcc/ADS (harder; different tooling).
  - Krawall shipped for GCC toolchains, which hints GCC, but this is not proof.
  - Non-Nintendo games sometimes need patched agbcc forks to match (cf. kl-eod-decomp's
    `-ftst` fork).
- No existing decomp of this game. Related-but-empty: SimsAdvanceRet/UrbzGBADecomp (same
  studio/era; watch for shared engine code).

## Current phase: bootstrap (keep it simple)

Get a minimal workflow going first; expand tooling later (see "Target toolchain" below).

Initial layout to create:

```
├── flake.nix              # nix develop: arm-none-eabi binutils, python3, just, luvdis deps, mgba
├── justfile               # task runner: setup, build, compare, clean
├── .gitignore             # baserom*.gba, build/
├── baserom.us.gba         # user-supplied (gitignored); jp later
├── rom.us.sha1            # pinned hash of target ROM
├── ld_script.us.ld        # fixed-address layout
├── asm/                   # Luvdis output, split into modules over time
├── data/                  # data sections (.incbin from baserom initially)
├── symbols.us.txt         # known function/data symbols
├── tools/                 # small python tools (compare, later extractors)
└── docs/                  # notes: memory map, formats, decisions
```

Bootstrap task order:

1. `flake.nix` + `justfile` + `.gitignore`; `just setup` verifies baserom sha1.
2. Fingerprint the compiler (strings/disasm of division helpers, prologue idioms,
   switch-table style). Record findings in `docs/compiler.md`.
3. Locate Krawall in the binary (compare against LGPL source; find `kramWorker` etc.).
   Record in `docs/memory-map.md`.
4. Full-ROM matching disassembly with Luvdis (https://github.com/aarant/luvdis):
   `luvdis baserom.us.gba -c functions.cfg -o asm/rom.s`. Feed discovered functions back
   into the config. Luvdis guarantees output that reassembles identically.
5. First matching build: arm-none-eabi-as + ld with `ld_script.us.ld` + objcopy
   (`--gap-fill 0xFF`, pad to ROM size) → `just compare` passes sha1. **Commit this as the
   baseline.**
6. Split `asm/rom.s` into modules; start `asm/nonmatchings/` per-function layout early
   (needed later for objdiff/Mizuchi/decomp.me context generation).

Ghidra (language `ARM:LE:32:v4t`) for analysis/labeling alongside; sync names into
`symbols.us.txt` and the Luvdis config.

## Build principles

- Donor-ROM flow: clone → place `baserom.us.gba` → `just setup` → `just build` → `just compare`.
- Fixed-address linker script per version; every object placed at its original address, so
  per-object matches compose into a whole-ROM match.
- Unmapped regions: `.incbin "baserom.us.gba", <offset>, <size>` in `data/*.s`. Progress =
  replacing incbin ranges with real asm/C/converted assets.
- Asset pipeline (later): editable formats in repo (.png, .xm, .json) converted at build
  time to console formats (gbagfx for graphics; custom extractors for Griptonite formats).
  Round-trips are enforced by the final sha1 compare.
- Multi-version (later): `just build jp` selects `baserom.jp.gba`, `ld_script.jp.ld`,
  `-DVERSION_JP`, `build/jp/`.

## Target toolchain (end state — document only, don't build yet)

- **Layers**: Nix (pinned packages via flake + binary cache) → Just (human/agent commands)
  → `configure.py` + Ninja (build graph). Single source of truth: per-version YAML segment
  config + `symbols.<ver>.txt`; configure.py generates ninja rules, linker scripts,
  extraction/conversion rules, objdiff config, decomp.me context.
- **Compiler**: whatever fingerprinting determines (likely agbcc or a fork), vendored and
  built by a Nix derivation (`hardeningDisable = ["all"]`, old-C warning suppression),
  fronted by ccache.
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
