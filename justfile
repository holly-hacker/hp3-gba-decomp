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

# Assemble and link the stitched output into a ROM image.
build ver="us": (stitch ver)
    arm-none-eabi-as -mcpu=arm7tdmi build/{{ver}}/rom.s -o build/{{ver}}/rom.o
    arm-none-eabi-ld -T ld_script.{{ver}}.ld build/{{ver}}/rom.o -o build/{{ver}}/rom.elf
    arm-none-eabi-objcopy -O binary --gap-fill 0xFF build/{{ver}}/rom.elf build/{{ver}}/rom.gba

# Build and check the result matches the donor ROM byte-for-byte.
compare ver="us": (build ver)
    cmp baserom.{{ver}}.gba build/{{ver}}/rom.gba && echo "MATCH"
