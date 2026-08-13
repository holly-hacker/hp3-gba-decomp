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

# Gitignored (game's actual copyrighted content, never committed). Re-run
# after a baserom change; addresses/names are deterministic so the
# committed manifest rows stay valid. See docs/formats/krawall.md.
# Regenerate the extracted Krawall audio data.
extract-krawall ver="us":
    python3 tools/extract_krawall.py {{ver}} > /dev/null

# Assemble and link the stitched output into a ROM image.
build ver="us": (stitch ver) (extract-krawall ver)
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
# used by the build -- see docs/formats/krawall.md.
# Export the game's music as .xm files for listening/viewing.
extract-music-xm ver="us":
    mkdir -p build/{{ver}}/music_xm
    unkrawerter -k -x -o build/{{ver}}/music_xm baserom.{{ver}}.gba
