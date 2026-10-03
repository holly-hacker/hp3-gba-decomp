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

# Discovery/reference aid only -- NOT used by the build (see `gen-link`).
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
    arm-none-eabi-ld -T ld_script.ld build/{{ver}}/full_disasm.o -o build/{{ver}}/full_disasm.elf
    arm-none-eabi-objcopy -O binary --gap-fill 0xFF build/{{ver}}/full_disasm.elf build/{{ver}}/full_disasm.gba
    cmp baserom.{{ver}}.gba build/{{ver}}/full_disasm.gba && echo "MATCH"

# One object per region, gaps .incbin'd from the baserom, and a linker
# script placing each at its manifest address.
# Generate the build inputs from regions.<ver>.txt.
gen-link ver="us": (pack-images ver) (pack-room-graphics ver) (pack-graphic-blobs ver) (pack-tile-streams ver)
    mkdir -p build/{{ver}}
    python3 tools/gen_link.py {{ver}}

# Research/debugging aid only -- NOT build input (the build gets its
# Krawall assembly from `pack-krawall`). Dumps each Krawall region as a
# raw asm/krawall/<ver>/*.bin file straight from the baserom; useful for
# diffing against pack-krawall's output while touching
# tools/krawall/krawall_codec.py. See docs/formats/krawall.md.
# Dump the raw Krawall regions as .bin files (not build input).
dump-krawall ver="us":
    python3 tools/krawall/dump_krawall.py {{ver}} > /dev/null

# Research/debugging aid only -- NOT build input (the collision data is
# built from data/room_graphics/, see docs/formats/room_graphics.md).
# Renders each room's collision map as walkability + tile-type PNGs
# straight from the baserom, for checking against real gameplay. US only
# (JP room-table address not yet located).
# Render every room's collision map to extracted/collision/<ver>/ PNGs.
dump-collision ver="us":
    python3 tools/collision/dump_collision.py {{ver}}

# Research/debugging aid only -- NOT build input. Decodes each room's BG
# layers from the baserom, so it shows the assembled rooms (US only).
# Render every room's BG layers to extracted/graphics/rooms/ PNGs.
dump-room-graphics ver="us":
    python3 tools/graphics/dump_bg_tiles.py {{ver}}

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/audio/ is gitignored (same footing as the baserom, see
# AGENTS.md hard rule 2) and meant to be user-editable for future modding,
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
# AGENTS.md hard rule 2) and meant to be user-editable for future modding,
# so it's never silently regenerated/overwritten on every build.
# Bootstrap data/text/ locally from baserom.us.gba and baserom.jp.gba.
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
# `build` -- data/images/ is gitignored (same footing as the baserom,
# see AGENTS.md hard rule 2). Walks each image-bank row of
# regions.<ver>.txt; see docs/formats/graphics.md's "Image-bank build
# format". Re-running overwrites local PNG edits.
# Bootstrap data/images/ PNGs and bank.json files from the baserom.
extract-images ver="us":
    python3 tools/images/extract_images.py {{ver}}

# The image-bank rows each name a directory of PNG sprites and bank.json.
# This re-encodes each sprite's palette, tiles, and frame data, and emits
# assembly under build/<ver>/images/ and matching generated C declarations
# under include/gen/ (shared by all versions).
# Pack all image banks for this version.
pack-images ver="us":
    python3 tools/images/pack_images.py {{ver}}

# Gitignored like data/images/ (AGENTS.md hard rule 2). Rebuilds every room
# from its files to check it matches both ROMs. Re-running overwrites local edits.
# Bootstrap data/room_graphics/ (palettes, tile sheets, maps) from the baserom.
extract-room-graphics:
    python3 tools/room_graphics/extract_room_graphics.py

# Each room-graphics row names a room's directory under data/room_graphics/.
# Encodes its 14 resources and emits assembly under build/<ver>/room_graphics/.
# Pack all room graphics for this version.
pack-room-graphics ver="us":
    python3 tools/room_graphics/pack_room_graphics.py {{ver}}

# Gitignored like data/images/ (AGENTS.md hard rule 2). Rebuilds every blob
# from its PNGs to check it matches the baserom. Re-running overwrites local edits.
# Bootstrap data/graphic_blobs/ (indexed PNGs of each blob) from the baserom.
extract-graphic-blobs ver="us":
    python3 tools/graphic_blob/extract_graphic_blobs.py {{ver}}

# Each graphic-blobs row names a directory under data/graphic_blobs/.
# Encodes its blobs and emits assembly under build/<ver>/graphic_blobs/.
# Pack all graphic blobs for this version.
pack-graphic-blobs ver="us":
    python3 tools/graphic_blob/pack_graphic_blobs.py {{ver}}

# Gitignored like data/images/ (AGENTS.md hard rule 2). Rebuilds every stream
# from its PNG to check it matches the baserom. Re-running overwrites local edits.
# Bootstrap data/tile_streams/ (PNG tile sheets) from the baserom.
extract-tile-streams ver="us":
    python3 tools/graphic_blob/extract_tile_streams.py {{ver}}

# Each tile-streams row names a directory under data/tile_streams/.
# Encodes its streams and emits assembly under build/<ver>/tile_streams/.
# Pack all tile streams for this version.
pack-tile-streams ver="us":
    python3 tools/graphic_blob/pack_tile_streams.py {{ver}}

# Run this once per clone, after `setup`, before the first `build` --
# every data/ subdirectory is gitignored (same footing as the baserom,
# AGENTS.md hard rule 2), so a fresh clone has none of it and the pack-*
# steps have nothing to read. Re-running overwrites local hand-edits.
# US-only: every extractor reads baserom.us.gba (content is either
# version-independent or not yet located in the JP ROM).
# Bootstrap every data/ subdirectory from the baserom. Run once per clone.
extract-all: extract-krawall extract-text extract-images extract-room-graphics extract-graphic-blobs extract-tile-streams
    @echo "data/ bootstrapped -- 'just compare' will work now."

# Runs agbcc, the compiler the ROM was built with -- see docs/compiler.md.
# Compile the c-file rows of regions.<ver>.txt to assembly.
compile-c ver="us": (pack-images ver) (pack-room-graphics ver) (pack-graphic-blobs ver) (pack-tile-streams ver)
    python3 tools/c/compile_c.py {{ver}}

# Regenerate compile_commands.json for clangd (editor diagnostics/go-to-def
# only -- not a build input). Re-run after a flake update, since the agbcc
# include path lives in the Nix store.
gen-compile-commands:
    python3 tools/c/gen_compile_commands.py

# Assemble every region and link them at their manifest addresses.
build ver="us": (compile-c ver) (pack-krawall ver) (pack-text ver) (gen-link ver)
    printf '%s\n' build/{{ver}}/obj/*.s | xargs -P "$(nproc)" -I{} sh -c 'arm-none-eabi-as -mcpu=arm7tdmi "$1" -o "${1%.s}.o"' _ {}
    arm-none-eabi-ld -T build/{{ver}}/link.ld build/{{ver}}/obj/*.o -o build/{{ver}}/rom.elf
    python3 tools/check_sections.py {{ver}}
    arm-none-eabi-objcopy -O binary --gap-fill 0xFF build/{{ver}}/rom.elf build/{{ver}}/rom.gba

# Build without the section check
build-mod ver="us": (compile-c ver) (pack-krawall ver) (pack-text ver) (gen-link ver)
    printf '%s\n' build/{{ver}}/obj/*.s | xargs -P "$(nproc)" -I{} sh -c 'arm-none-eabi-as -mcpu=arm7tdmi "$1" -o "${1%.s}.o"' _ {}
    arm-none-eabi-ld -T build/{{ver}}/link.ld build/{{ver}}/obj/*.o -o build/{{ver}}/mod.elf
    arm-none-eabi-objcopy -O binary --gap-fill 0xFF build/{{ver}}/mod.elf build/{{ver}}/mod.gba

# For matching work: `just compare` only reports a byte offset, this says
# which instructions differ.
# Disassemble one region side by side against the donor ROM.
diff-region name ver="us": (build ver)
    python3 -m tools.matching diff-region {{ver}} {{name}}

# Build and check the result matches the donor ROM byte-for-byte.
compare ver="us": (build ver)
    cmp baserom.{{ver}}.gba build/{{ver}}/rom.gba && echo "MATCH"

# Verifies donor ROMs, full disassembly, linked builds for both versions,
# and manifest/function-config ordering.
# Full sanity sweep: run everything, confirm it all still matches. Run before committing.
check-all: setup (disasm-compare "us") (disasm-compare "jp") (compare "us") (compare "jp") check-sorted
    @echo "us and jp: full disassembly and linked build both match the donor ROM."

# Confirm regions.<ver>.txt, functions.<ver>.cfg and ram_symbols.<ver>.inc stay sorted by address.
check-sorted:
    python3 tools/check_sorted_regions.py
    python3 tools/check_sorted_functions.py
    python3 tools/check_sorted_ram_symbols.py

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
    python3 -m tools.matching match-versions {{args}}
