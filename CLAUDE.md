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
   byte-for-byte from the baserom plus already-tracked inputs (raw disassembly dumps,
   objcopy'd ROM images, extracted-but-unconverted assets), it belongs in `build/` (gitignored)
   and is produced by a `just` recipe, not committed. Commit only the curated inputs that
   encode actual reverse-engineering knowledge or decisions: function-boundary configs,
   symbol names, hand-written/decompiled/matched code, manually converted assets, docs. Keep
   such config per-version (`functions.us.cfg` / `functions.jp.cfg`, not one shared file).

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
  - Music/sample content lives as curated JSON+WAV under `data/audio/` (modules with inline
    pattern data referencing samples by name; samples as WAV + a JSON metadata sidecar) --
    per hard rule 2, `data/audio/` is gitignored, same footing as the baserom, never
    committed. `tools/krawall/krawall_migrate.py` bootstraps it locally
    from `baserom.us.gba` (a one-time step per clone, not run on every build -- re-running it
    overwrites any local hand-edits, since content is meant to be user-editable for future
    modding). `tools/krawall/pack_krawall.py` then packs this local, version-independent source
    (content proven byte-identical between US/JP, see `docs/formats/krawall.md`) into
    per-version, byte-exact assembly before each build, driven by `regions.<ver>.txt`'s
    `krawall-module`/`krawall-samples` rows (addresses only -- the content itself doesn't
    vary per version). `tools/krawall/extract_krawall.py` (the old raw ROM -> `asm/krawall/<ver>/*.bin`
    path, also gitignored) is no longer part of the build; kept only as a discovery/debugging
    aid. See `docs/formats/krawall.md` for the full format writeup (including the
    pattern/module field decoding this packing relies on) and its Future work section for how
    this replaced the earlier raw-`.bin` model. A separate, lossy `.xm` export still exists
    for actually listening to/viewing the music (`just extract-music-xm`), never used by the
    build.
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
├── flake.nix              # dev shell (toolchain, gbadisasm built from source + patched,
│                           #   capstone, just, mgba). flake.lock is committed.
├── patches/gbadisasm/      # patches for unmaintained upstream gbadisasm bugs
├── justfile                # task runner; recipes take ver="us"|"jp"
├── .gitignore              # baserom*.gba, gba_bios.*, *.sav, build/, *.o, *.elf
├── baserom.us.gba          # user-supplied (gitignored)
├── baserom.jp.gba          # user-supplied (gitignored)
├── gba_bios.bin            # user-supplied (gitignored), optional -- only needed for mGBA/gdb
│                           #   dynamic debugging, not for the matching build
├── rom.us.sha1, rom.jp.sha1 # pinned donor-ROM hashes
├── ld_script.us.ld, ld_script.jp.ld  # fixed-address layout, per version
├── functions.us.cfg, functions.jp.cfg  # curated gbadisasm arm_func/thumb_func seed lists --
│                           #   gbadisasm has no function discovery of its own, see below
├── regions.us.txt, regions.jp.txt  # curated manifest of EXTRACTED byte ranges: address, end,
│                           #   asm file, name -- plus `label` lines for symbols inside
│                           #   still-raw territory that extracted code needs to reference
├── macros.inc              # pret-convention function macros that asm/*.s files depend on
├── asm/                    # hand-verified extracted regions (regions.<ver>.txt rows),
│                           #   organized into subdirectories by category (e.g. asm/rt/ for
│                           #   compiler runtime builtins)
├── data/audio/             # curated Krawall music/sample source (JSON+WAV) -- gitignored,
│                           #   same footing as the baserom; bootstrapped locally by
│                           #   tools/krawall/krawall_migrate.py, packed to per-version assembly
│                           #   by tools/krawall/pack_krawall.py
├── build/                  # gitignored, fully regenerated by `just` -- raw reference
│                           #   disassembly, the stitched build input, and build artifacts
├── tools/                  # small scripts, e.g. the regions.<ver>.txt -> build input generator
└── docs/                   # compiler.md, memory-map.md (+ memory-map/krawall.md,
                            #   memory-map/rng.md) -- notes with explicit confidence levels
                            #   (PROVEN / STRUCTURAL MATCH / UNCONFIRMED), keep using that
                            #   convention for new findings
```

Bootstrap task order (status as of this writing):

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
6. [~] In progress: real function extraction, manifest-driven via `regions.<ver>.txt`,
   replacing the old "one giant regenerated disassembly" model -- everything not in the
   manifest stays raw `.incbin`; everything in it is a real, curated, committed `asm/*.s`
   file. This is the actual `asm/nonmatchings/`-style layout the original plan wanted, just
   not framed as "split the whole ROM at once." See Conventions for the extraction rule.
   The GBA header and the compiler's division-routine builtins (see `docs/compiler.md`) are
   extracted so far; the Krawall driver candidates are not (boundaries still unconfirmed --
   see `docs/memory-map/krawall.md`).

Ghidra (language `ARM:LE:32:v4t`) for analysis/labeling alongside; sync names into
`functions.<ver>.cfg`/`regions.<ver>.txt`.

Dynamic verification (mGBA + gdb, via mGBA's `--gdb` stub) was attempted for Krawall function
identification and was inconclusive -- see `docs/memory-map/krawall.md`'s "Dynamic verification
attempt" section before retrying that path; the stub's breakpoint/continue sequencing was
unreliable across many attempts and the root cause was never identified.

## Build principles

- Donor-ROM flow: clone → `nix develop` → place `baserom.us.gba` + `baserom.jp.gba` →
  `just setup` → `just compare us` / `just compare jp`. All `just` recipes take
  `ver="us"|"jp"` (default `us`) and are already wired for both versions today, not "later."
- Fixed-address linker script per version; every object placed at its original address, so
  per-object matches compose into a whole-ROM match.
- Unmapped regions: raw `.incbin` from the baserom, generated by `tools/gen_rom_s.py` for
  whatever `regions.<ver>.txt` doesn't cover. Progress = adding rows to `regions.<ver>.txt`
  and committing the corresponding `asm/*.s` file (see Conventions for the extraction rule).
- Asset pipeline: same manifest-driven model as code, not a separate system -- extractors
  run against the user's local ROM. Krawall audio is the first real case (see above): unlike
  code, the manifest rows are machine-generated (deterministic struct parsing, not human
  judgement), but they're still committed -- addresses/names are curated knowledge either
  way. What's NOT committed is the asset content itself -- actual game assets (art, audio,
  etc.) sit on the same footing as the baserom under hard rule 2, regardless of how
  mechanically they were located. Krawall audio moved from raw-`.bin` extraction
  (regenerated on every build) to curated, editable JSON+WAV under `data/audio/`
  (bootstrapped once locally, not regenerated automatically -- see above), but both stay
  gitignored either way. Round-trips are enforced by the final sha1 compare regardless.
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
- Commit messages: state what region/function was matched or symbolized.
- Don't add a row to `regions.<ver>.txt` until a function's true, complete extent is
  confirmed (every reachable branch walked to genuine termination) -- `just compare`'s sha1
  check can't catch a truncated-but-plausible boundary, since the unclaimed remainder just
  becomes opaque `.incbin` bytes next door. If unsure, leave it as `.incbin` and track it as
  a candidate in `docs/` instead.

## Reference projects & tools

- pret pokeemerald / pokeruby / pmd-red — canonical GBA layout; pmd-red = asm-first model.
- Dream-Atelier/kl-eod-decomp — modern small-game template with AI integration.
- camthesaxman/gbadisasm — matching disassembler (patched, see `patches/gbadisasm/`).
  decomp.wiki/platforms/game-boy-advance — scene hub.
- GBATEK (https://www.problemkaputt.de/gbatek.htm) — hardware reference.
