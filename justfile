# Task runner for the HP3 GBA decomp. Run `just` to list recipes.
# ver is "us" or "jp" throughout; defaults to "us".

default:
    @just --list

# Verify the donor ROMs match the pinned hashes.
setup:
    sha1sum -c rom.us.sha1
    sha1sum -c rom.jp.sha1

# Regenerate the full-ROM disassembly from the baserom + curated function
# config. This is a discovery/reference aid only -- NOT used by the build
# (see `stitch`).
disasm ver="us":
    mkdir -p build/{{ver}}
    { \
        echo ".syntax unified"; \
        echo '.include "macros.inc"'; \
        echo ".text"; \
        gbadisasm -c functions.{{ver}}.cfg baserom.{{ver}}.gba; \
    } > build/{{ver}}/full_disasm.s

# Generate the actual build input from regions.<ver>.txt: .incbin for
# everything not yet extracted, .include for each curated asm/data file.
stitch ver="us":
    mkdir -p build/{{ver}}
    python3 tools/gen_rom_s.py {{ver}} > build/{{ver}}/rom.s

# Regenerate the extracted Krawall audio data (asm/krawall/<ver>/, gitignored
# -- the game's actual copyrighted content, never committed) that
# regions.<ver>.txt's audio rows .incbin. Must be re-run after a baserom
# change; addresses/names are deterministic so the committed manifest rows
# stay valid. See docs/formats/krawall.md.
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

# Export the game's music as .xm files for listening/viewing. Lossy
# (effect remapping, pattern rewrites for playback accuracy) and NOT used
# by the build -- see docs/formats/krawall.md.
extract-music-xm ver="us":
    mkdir -p build/{{ver}}/music_xm
    unkrawerter -k -x -o build/{{ver}}/music_xm baserom.{{ver}}.gba
