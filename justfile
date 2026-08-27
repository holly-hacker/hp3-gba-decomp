# Task runner for the HP3 GBA decomp. Run `just` to list recipes.
# ver is "us" or "jp" throughout; defaults to "us".
#
# NOTE: `just --list` only shows a recipe's LAST comment line as its
# description -- keep that line short and put any extra detail above it.

default:
    @just --list

# Verify the donor ROMs match the pinned hashes.
setup:
    sha1sum -c rom.us.sha1
    sha1sum -c rom.jp.sha1

# Discovery/reference aid only -- NOT used by the build (see `stitch`).
# Regenerate the full-ROM disassembly from the baserom + function config.
disasm ver="us":
    mkdir -p build/{{ver}}
    { \
        echo ".syntax unified"; \
        echo '.include "macros.inc"'; \
        echo ".text"; \
        gbadisasm -c functions.{{ver}}.cfg baserom.{{ver}}.gba; \
    } > build/{{ver}}/full_disasm.s

# Doesn't gate `just compare` (see `disasm`'s comment) but catches bad
# function-boundary seeds in functions.<ver>.cfg -- misaligned/duplicate
# seeds can make gbadisasm mis-split functions in ways that still assemble.
# Assemble the full-ROM disassembly and confirm it's still byte-perfect.
disasm-compare ver="us": (disasm ver)
    arm-none-eabi-as -mcpu=arm7tdmi build/{{ver}}/full_disasm.s -o build/{{ver}}/full_disasm.o
    arm-none-eabi-ld -T ld_script.{{ver}}.ld build/{{ver}}/full_disasm.o -o build/{{ver}}/full_disasm.elf
    arm-none-eabi-objcopy -O binary --gap-fill 0xFF build/{{ver}}/full_disasm.elf build/{{ver}}/full_disasm.gba
    cmp baserom.{{ver}}.gba build/{{ver}}/full_disasm.gba && echo "MATCH"

# Everything not yet extracted becomes .incbin, everything in the manifest
# an .include of its curated asm/data file.
# Generate the actual build input from regions.<ver>.txt.
stitch ver="us":
    mkdir -p build/{{ver}}
    python3 tools/gen_rom_s.py {{ver}} > build/{{ver}}/rom.s

# Research/debugging aid only -- NOT build input (the build gets its
# Krawall assembly from `pack-krawall`). Dumps each Krawall region as a
# raw asm/krawall/<ver>/*.bin file straight from the baserom; useful for
# diffing against pack-krawall's output while touching
# tools/krawall/krawall_codec.py. See docs/formats/krawall.md.
# Dump the raw Krawall regions as .bin files (not build input).
dump-krawall ver="us":
    python3 tools/krawall/dump_krawall.py {{ver}} > /dev/null

# Research/debugging aid only -- NOT build input (no pack-collision
# exists; the room-table collision fields aren't proven complete enough
# for a regions.<ver>.txt row yet, see docs/formats/collision.md).
# Renders each room's collision map as walkability + tile-type PNGs
# straight from the baserom, for checking against real gameplay. US only
# (JP room-table address not yet located).
# Render every room's collision map to extracted/collision/<ver>/ PNGs.
dump-collision ver="us":
    python3 tools/collision/dump_collision.py {{ver}}

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/audio/ is gitignored (same footing as the baserom, see
# CLAUDE.md hard rule 2) and meant to be user-editable for future modding,
# so it's never silently regenerated/overwritten on every build.
# Bootstrap data/audio/ locally from baserom.us.gba.
extract-krawall:
    python3 tools/krawall/extract_krawall.py

# Gitignored (build/), like everything else pack_krawall.py writes. Reads
# local data/audio/ (run `extract-krawall` first if missing -- version-
# independent) plus this version's krawall-module/krawall-samples rows in
# regions.<ver>.txt for addresses.
# Pack data/audio/ into this version's Krawall assembly.
pack-krawall ver="us":
    python3 tools/krawall/pack_krawall.py {{ver}}

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/text/ is gitignored (same footing as the baserom, see
# CLAUDE.md hard rule 2) and meant to be user-editable for future modding,
# so it's never silently regenerated/overwritten on every build. US only
# -- dialog text hasn't been located in the JP ROM (see docs/formats/text.md).
# Bootstrap data/text/ locally from baserom.us.gba.
extract-text:
    python3 tools/text/extract_text.py

# Gitignored (build/), like everything else pack_text.py writes. Reads
# local data/text/ (run `extract-text` first if missing) plus this
# version's dialog-text/dialog-text-table rows in regions.<ver>.txt for
# addresses.
# Pack data/text/ into this version's dialog-text assembly.
pack-text ver="us":
    python3 tools/text/pack_text.py {{ver}}

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/monsters/ is gitignored (same footing as the baserom,
# see CLAUDE.md hard rule 2) and meant to be user-editable, so it's never
# silently regenerated/overwritten on every build. US only -- see
# docs/formats/folio_bruti.md.
# Bootstrap data/monsters/ locally from baserom.us.gba.
extract-monsters:
    python3 tools/monsters/extract_monsters.py

# Gitignored (build/), like everything else pack_monsters.py writes. Reads
# local data/monsters/ (run `extract-monsters` first if missing) plus
# this version's monster-table row in regions.<ver>.txt for addresses.
# Pack data/monsters/ into this version's monster-table assembly.
pack-monsters ver="us":
    python3 tools/monsters/pack_monsters.py {{ver}}

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/scripts/ is gitignored (same footing as the baserom,
# see CLAUDE.md hard rule 2) and meant to be user-editable, so it's never
# silently regenerated/overwritten on every build. US only -- see
# docs/formats/object_script.md.
# Bootstrap data/scripts/ locally from baserom.us.gba.
extract-objscript:
    python3 tools/objscript/extract_objscript.py

# Gitignored (build/), like everything else pack_objscript.py writes. Reads
# local data/scripts/ (run `extract-objscript` first if missing) plus
# this version's objscript-table row in regions.<ver>.txt for addresses.
# Pack data/scripts/ into this version's objscript-table assembly.
pack-objscript ver="us":
    python3 tools/objscript/pack_objscript.py {{ver}}

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/items/ is gitignored (same footing as the baserom,
# see CLAUDE.md hard rule 2) and meant to be user-editable, so it's never
# silently regenerated/overwritten on every build. US only -- see
# docs/formats/save.md.
# Bootstrap data/items/ locally from baserom.us.gba.
extract-items:
    python3 tools/items/extract_items.py

# Gitignored (build/), like everything else pack_items.py writes. Reads
# local data/items/ (run `extract-items` first if missing) plus this
# version's item-table row in regions.<ver>.txt for addresses.
# Pack data/items/ into this version's item-table assembly.
pack-items ver="us":
    python3 tools/items/pack_items.py {{ver}}

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/images/ is gitignored (same footing as the baserom,
# see CLAUDE.md hard rule 2). US only. Also writes viewable PNGs to
# extracted/items/ (gitignored, never build input -- see
# docs/formats/graphics.md's "Item icons" section).
# Bootstrap data/images/items/*.bin and extracted/items/*.png from baserom.us.gba.
extract-item-icons:
    python3 tools/items/extract_item_icons.py

# Gitignored (build/), like everything else pack_item_icons.py writes.
# Reads local data/images/items/ (run `extract-item-icons` first if
# missing) plus this version's item-icon-data row in regions.<ver>.txt
# for addresses. Unlike pack-items, this is a literal copy-through --
# no known encoder exists for the type-4 codec these icons use.
# Pack data/images/items/ into this version's item-icon-data assembly.
pack-item-icons ver="us":
    python3 tools/items/pack_item_icons.py {{ver}}

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/levels/ is gitignored (same footing as the baserom,
# see CLAUDE.md hard rule 2) and meant to be user-editable. US only --
# see docs/memory-map/battle.md.
# Bootstrap data/levels/ locally from baserom.us.gba.
extract-levels:
    python3 tools/levels/extract_levels.py

# Gitignored (build/), like everything else pack_levels.py writes. Reads
# local data/levels/ (run `extract-levels` first if missing) plus this
# version's level-table rows in regions.<ver>.txt for addresses.
# Pack data/levels/ into this version's level-table assembly.
pack-levels ver="us":
    python3 tools/levels/pack_levels.py {{ver}}

# Run this once per clone, after `setup`, before the first `build` --
# every data/ subdirectory is gitignored (same footing as the baserom,
# CLAUDE.md hard rule 2), so a fresh clone has none of it and the pack-*
# steps have nothing to read. Re-running overwrites local hand-edits.
# US-only: every extractor reads baserom.us.gba (content is either
# version-independent or not yet located in the JP ROM).
# Bootstrap every data/ subdirectory from the baserom. Run once per clone.
extract-all: extract-krawall extract-text extract-monsters extract-objscript extract-levels extract-items extract-item-icons
    @echo "data/ bootstrapped -- 'just compare' will work now."

# Assemble and link the stitched output into a ROM image.
build ver="us": (stitch ver) (pack-krawall ver) (pack-text ver) (pack-monsters ver) (pack-objscript ver) (pack-levels ver) (pack-items ver) (pack-item-icons ver)
    arm-none-eabi-as -mcpu=arm7tdmi build/{{ver}}/rom.s -o build/{{ver}}/rom.o
    arm-none-eabi-ld -T ld_script.{{ver}}.ld build/{{ver}}/rom.o -o build/{{ver}}/rom.elf
    arm-none-eabi-objcopy -O binary --gap-fill 0xFF build/{{ver}}/rom.elf build/{{ver}}/rom.gba

# Build and check the result matches the donor ROM byte-for-byte.
compare ver="us": (build ver)
    cmp baserom.{{ver}}.gba build/{{ver}}/rom.gba && echo "MATCH"

# Not `check` -- that name's reserved for the fancier configure.py+ninja+
# objdiff version described in CLAUDE.md's "Target toolchain", not built
# yet. Verifies donor ROMs, then the full disassembly and the stitched
# build for both versions.
# Full sanity sweep: run everything, confirm it all still matches. Run before committing.
check-all: setup (disasm-compare "us") (disasm-compare "jp") (compare "us") (compare "jp")
    @echo "us and jp: full disassembly and stitched build both match the donor ROM."

# Lossy (effect remapping, pattern rewrites for playback accuracy) and NOT
# used by the build -- see docs/formats/krawall.md. Writes to extracted/,
# not build/ -- this is human-viewing output, not a build artifact.
# Dump the game's music as .xm files for listening/viewing.
dump-music-xm ver="us":
    mkdir -p extracted/{{ver}}/music_xm
    unkrawerter -k -x -o extracted/{{ver}}/music_xm baserom.{{ver}}.gba

# Proposes candidates only -- see the script's docstring for how to confirm
# one before trusting it (e.g. copying a name into functions.jp.cfg).
# Find US<->JP thumb_func address correspondences by instruction shape.
match-functions *args:
    python3 tools/match_functions.py {{args}}
