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

# Research/debugging aid only -- NOT build input (the build gets its
# Krawall assembly from tools/krawall/pack_krawall.py). Dumps each Krawall
# region as a raw asm/krawall/<ver>/*.bin file straight from the baserom;
# useful for diffing against pack_krawall.py's output while touching
# tools/krawall/krawall_codec.py. See docs/formats/krawall.md.
# Dump the raw Krawall regions as .bin files (not build input).
dump-krawall ver="us":
    python3 tools/krawall/dump_krawall.py {{ver}}

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

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/text/ is gitignored (same footing as the baserom, see
# AGENTS.md hard rule 2) and meant to be user-editable for future modding,
# so it's never silently regenerated/overwritten on every build.
# Bootstrap data/text/ locally from baserom.us.gba and baserom.jp.gba.
extract-text:
    python3 tools/text/extract_text.py

# One-time per clone (see `extract-all`), NOT run automatically by
# `build` -- data/graphics/ is gitignored (same footing as the baserom,
# AGENTS.md hard rule 2). Extracts every graphics row of both manifests, or
# only the named runs. Re-running overwrites local edits.
# Bootstrap data/graphics/ from the baseroms.
extract-graphics *runs:
    python3 tools/graphics/extract_graphics.py {{runs}}

# Run this once per clone, after `setup`, before the first `build` --
# every data/ subdirectory is gitignored (same footing as the baserom,
# AGENTS.md hard rule 2), so a fresh clone has none of it and the pack
# steps have nothing to read. Re-running overwrites local hand-edits.
# Bootstrap every data/ subdirectory from the baseroms. Run once per clone.
extract-all: extract-krawall extract-text extract-graphics
    @echo "data/ bootstrapped -- 'just compare' will work now."

# Regenerate compile_commands.json for clangd (editor diagnostics/go-to-def
# only -- not a build input). Re-run after a flake update, since the agbcc
# include path lives in the Nix store.
gen-compile-commands:
    python3 tools/c/gen_compile_commands.py

# Writes build/build.ninja from the manifests. Ninja reruns it when they
# change, so this is only needed once per clone.
# Write the Ninja build file.
configure:
    python3 tools/configure.py

# Krawall's IWRAM code is writable (kradInterrupt patches itself), hence
# --no-warn-rwx-segments. --emit-relocs keeps the relocations in rom.elf for
# tools/compare.py. link.ld names every object it links. The donor ROM is
# zero-filled to 16 MiB. The rules are in tools/configure.py.
# Pack, compile, assemble and link this version's ROM.
build ver="us":
    test -f build/build.ninja || python3 tools/configure.py
    ninja -f build/build.ninja build/{{ver}}/rom.gba

# Build both versions' ROMs at once.
build-all:
    test -f build/build.ninja || python3 tools/configure.py
    ninja -f build/build.ninja

# For matching work: `just compare` names the first differing region, this
# says which instructions differ.
# Disassemble one region side by side against the donor ROM.
diff-region name ver="us": (build ver)
    python3 tools/diff_region.py {{ver}} {{name}}

# Build and check the result matches the donor ROM byte-for-byte.
compare ver="us": (build ver)
    python3 tools/compare.py {{ver}}

# Verifies donor ROMs, linked builds for both versions and RAM symbol ordering.
# Full sanity sweep: run everything, confirm it all still matches. Run before committing.
check-all: setup build-all check-sorted
    python3 tools/compare.py us
    python3 tools/compare.py jp
    @echo "us and jp: linked build matches the donor ROM."

# Confirm ram_symbols.<ver>.inc stays sorted by address.
check-sorted:
    python3 tools/check_sorted_ram_symbols.py

# Lossy (effect remapping, pattern rewrites for playback accuracy) and NOT
# used by the build -- see docs/formats/krawall.md. Writes to extracted/,
# not build/ -- this is human-viewing output, not a build artifact.
# Dump the game's music as .xm files for listening/viewing.
dump-music-xm ver="us":
    mkdir -p extracted/{{ver}}/music_xm
    unkrawerter -k -x -o extracted/{{ver}}/music_xm baserom.{{ver}}.gba
