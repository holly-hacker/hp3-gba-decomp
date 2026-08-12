# Task runner for the HP3 GBA decomp. Run `just` to list recipes.
# ver is "us" or "jp" throughout; defaults to "us".

default:
    @just --list

# Verify the donor ROMs match the pinned hashes.
setup:
    sha1sum -c rom.us.sha1
    sha1sum -c rom.jp.sha1

# Regenerate the full-ROM disassembly from the baserom + curated function
# config. Never commit build/ output -- this step must be able to reproduce
# it from scratch every time.
disasm ver="us":
    mkdir -p build/{{ver}}
    luvdis disasm baserom.{{ver}}.gba -c functions.{{ver}}.cfg -o build/{{ver}}/rom.s

# Assemble and link the disassembly into a ROM image.
build ver="us": (disasm ver)
    arm-none-eabi-as -mcpu=arm7tdmi build/{{ver}}/rom.s -o build/{{ver}}/rom.o
    arm-none-eabi-ld -T ld_script.{{ver}}.ld build/{{ver}}/rom.o -o build/{{ver}}/rom.elf
    arm-none-eabi-objcopy -O binary --gap-fill 0xFF build/{{ver}}/rom.elf build/{{ver}}/rom.gba

# Build and check the result matches the donor ROM byte-for-byte.
compare ver="us": (build ver)
    cmp baserom.{{ver}}.gba build/{{ver}}/rom.gba && echo "MATCH"
