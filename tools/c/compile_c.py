#!/usr/bin/env python3
"""Compile the c-file and c-file-O1 rows of regions.<ver>.txt to assembly.

agbcc is a bare cc1: it takes preprocessed C and writes assembly, so the
pipeline is cpp -> agbcc -> build/<ver>/c/<name>.s, which gen_link.py
wraps into the region's object.

The manifest directive selects -O2 (c-file) or -O1 (c-file-O1), or
agbcc_arm for ARM-mode code (c-file-arm). Third-party code has its own
compiler: c-file-gcc3 and c-file-gcc3-arm use GCC 3.0.2, and asm-file-cpp
rows are only preprocessed.

The cpp output is cheap to produce and determines everything else, so it
keys the build cache (tools/buildcache.py): unchanged sources and headers
reuse their assembly without running agbcc.

Usage: compile_c.py <ver>   (before `gen-link`)
"""
import os
import re
import shutil
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
import buildcache  # noqa: E402
from krawall.gen_header import write_public_header  # noqa: E402
from manifest import (  # noqa: E402
    ASM_CPP_DIRECTIVE,
    C_FILE_DIRECTIVES,
    SECTIONED_DIRECTIVES,
)

GCC3_CC1 = "arm-elf-cc1-3.0.2"

# Krawall's build configuration (docs/memory-map/krawall.md): mixing
# buffers, channels and player state in EWRAM. The 16 kHz, 60 Hz default
# needs no define.
KRAWALL_DEFINES = ["-DIWRAM_USAGE_SMALL"]

def agbcc_prefix() -> str:
    exe = shutil.which("agbcc")
    if exe is None:
        sys.exit("agbcc not found -- are you in `nix develop`?")
    return os.path.dirname(os.path.dirname(os.path.realpath(exe)))


def profile(src: str, prefix: str, o1: bool = False,
            ver: str | None = None,
            arm: bool = False) -> tuple[str, list[str], list[str]]:
    """Returns (cc1, cppflags, cflags) for a source file.

    ver defines VERSION_US or VERSION_JP for game code whose source differs
    between the two ROMs. arm selects agbcc_arm, which lacks -fhex-asm,
    needs -quiet to stop printing pass timings, and needs
    -fomit-frame-pointer to drop the APCS frame the ROM doesn't have.

    __GNUC__ is agbcc's (GCC 2): -undef drops the host compiler's, and
    Krawall's public header (generated into build/include) maps its IWRAM
    functions to their stubs for GCC 2.
    """
    inc = os.path.join(prefix, "include")
    optimization = "-O1" if o1 else "-O2"
    cppflags = ["-I", "include", "-I", write_public_header(), "-I", inc,
                "-nostdinc", "-undef", "-D__GNUC__=2", "-std=gnu89",
                *([f"-DVERSION_{ver.upper()}"] if ver else [])]
    if arm:
        return (
            os.path.join(prefix, "bin", "agbcc_arm"),
            cppflags,
            [optimization, "-quiet", "-mthumb-interwork",
             "-fomit-frame-pointer", "-Wimplicit", "-Wparentheses", "-Werror",
             "-fno-builtin"],
        )
    return (
        os.path.join(prefix, "bin", "agbcc"),
        cppflags,
        # -fno-builtin: without it, agbcc treats any declaration/definition
        # of a reserved name (memset, ...) as conflicting with its own
        # builtin prototype. Applies to every game-code file, not just the
        # ones that currently reference such a name, so this doesn't need
        # to grow a list as more of them show up.
        [optimization, "-mthumb-interwork", "-Wimplicit", "-Wparentheses",
         "-Werror", "-fhex-asm", "-fno-builtin"],
    )


def gcc3_profile(src: str, prefix: str,
                 arm: bool) -> tuple[str, list[str], list[str]]:
    """Returns (cc1, cppflags, cflags) for third-party C or a .S file.

    GCC before 3.3 left __arm__/__thumb__ to the driver, so they are
    defined here for both C and assembly.
    """
    cc1 = shutil.which(GCC3_CC1)
    if cc1 is None:
        sys.exit(f"{GCC3_CC1} not found -- are you in `nix develop`?")
    lib = os.path.basename(os.path.dirname(src))
    cppflags = ["-I", f"include/3rd_party/{lib}",
                "-I", os.path.join(prefix, "include"), "-nostdinc", "-undef",
                "-D__arm__", *([] if arm else ["-D__thumb__"]),
                *(KRAWALL_DEFINES if lib == "krawall" else [])]
    return (cc1, cppflags,
            ["-quiet", "-fpreprocessed", "-O3", "-mthumb-interwork",
             "-marm" if arm else "-mthumb"])


def section_names(asm: str) -> list[str]:
    """Every section the assembly switches to, in order of first use.
    Directives are case-insensitive; Krawall's .S files write .TEXT."""
    names = re.findall(r"^\s*(?:\.section\s+([.\w]+)|\.(text|data|bss)\b)",
                       asm, re.M | re.I)
    return list(dict.fromkeys(a or f".{b.lower()}" for a, b in names))


def place_in_text(asm: str, src: str, keep_rodata: bool = False) -> str:
    """Fold read-only data into .text, and reject what has nowhere to go.

    The generated link.ld places each region's .text, so agbcc's
    `.section .rodata` for const data has to become .text -- the bytes are
    the same and both live in ROM. keep_rodata leaves it in place for a
    source whose .rodata a c-rodata row puts at its own address.
    `.data` and .comm/.lcomm have no home: they want writable RAM, whose
    addresses are fixed by the ROM, so RAM variables belong in
    ram_symbols.<ver>.inc and are `extern` in C.
    """
    if not keep_rodata:
        asm = re.sub(r"^\s*\.section\s+\.rodata\b.*$", ".text", asm, flags=re.M)
    for pattern, shown, what in ((r"\.data\b", ".data", "a writable global"),
                                 (r"\.l?comm\b", ".comm/.lcomm",
                                  "an uninitialised global")):
        if re.search(rf"^\s*{pattern}", asm, re.M):
            sys.exit(
                f"{src}: emits {shown} ({what}). RAM lives at fixed "
                f"addresses -- declare it extern in C and give it an address "
                f"in ram_symbols.<ver>.inc."
            )
    return asm


SECTION_FLAGS = re.compile(r'^(\s*\.section\s+([.\w]+)),"(\w*)"(?:,%\w+)?\s*$', re.M)


def merge_section_flags(asm: str) -> str:
    """Gives every switch to a section the union of the flags it is given.

    Code and data placed in one named section (IWRAM_CODE and IWRAM) get
    "ax" and "aw"; the original assembler accepted the change, today's
    rejects it.
    """
    flags: dict[str, set[str]] = {}
    for m in SECTION_FLAGS.finditer(asm):
        flags.setdefault(m.group(2), set()).update(m.group(3))
    return SECTION_FLAGS.sub(
        lambda m: f'{m.group(1)},"{"".join(sorted(flags[m.group(2)]))}",%progbits',
        asm)


def compile_sectioned(src: str, out: str, prefix: str, tools: str,
                      directive: str) -> None:
    """Compiles (or, for a .S, preprocesses) a third-party source.

    Its sections stay apart for the manifest to place, so its read-only
    data is not folded into .text. Each section ends padded to 4 bytes
    with the assembler's fill (nop in code, zeros elsewhere), as it was
    between the original objects.
    """
    arm = directive != "c-file-gcc3"
    cc1, cppflags, cflags = gcc3_profile(src, prefix, arm)
    if directive == ASM_CPP_DIRECTIVE:
        cppflags = ["-x", "assembler-with-cpp", "-D__ASSEMBLER__", *cppflags]
    pre = subprocess.run(["cpp", "-P", *cppflags, src],
                         capture_output=True, text=True)
    if pre.returncode:
        sys.exit(f"cpp failed on {src}:\n{pre.stderr}")
    if directive == ASM_CPP_DIRECTIVE:
        asm = pre.stdout
    else:
        key = buildcache.digest(tools, os.path.realpath(cc1), cflags, src,
                                pre.stdout)
        cached = buildcache.load("c", key)
        if cached is None:
            cc = subprocess.run([cc1, *cflags, "-o", "-", "-"],
                                input=pre.stdout, capture_output=True,
                                text=True)
            if cc.returncode:
                sys.exit(f"{GCC3_CC1} failed on {src}:\n{cc.stderr}")
            cached = cc.stdout.encode()
            buildcache.store("c", key, cached)
        # `.file "<stdin>"` would make the assembler list <stdin> as a
        # dependency (tools/assemble.py).
        asm = re.sub(r"^\s*\.file\s.*\n", "", cached.decode(), flags=re.M)
        # The original assembler filled an .align inside code with zeros;
        # only the end of a section got nops. Today's fills both with nops.
        asm = re.sub(r"^(\s*\.align\s+\d+)\s*$", r"\1, 0", asm, flags=re.M)
        asm = merge_section_flags(asm)
    place_in_text(asm, src, keep_rodata=True)
    padding = "".join(f"\t.section\t{name}\n\t.align\t2\n"
                      for name in section_names(asm) if name != ".bss")
    wrapped = (".syntax divided\n" + (".arm\n" if arm else ".thumb\n") + asm
               + "\n" + padding + ".text\n.syntax unified\n")
    buildcache.write_if_changed(out, wrapped.encode())


def compile_one(src: str, out: str, prefix: str, ver: str, tools: str,
                o1: bool = False, keep_rodata: bool = False,
                arm: bool = False) -> None:
    cc1, cppflags, cflags = profile(src, prefix, o1, ver, arm)
    pre = subprocess.run(["cpp", *cppflags, src],
                         capture_output=True, text=True)
    if pre.returncode:
        sys.exit(f"cpp failed on {src}:\n{pre.stderr}")
    key = buildcache.digest(tools, os.path.realpath(cc1), cflags, src,
                            keep_rodata, pre.stdout)
    asm = buildcache.load("c", key)
    if asm is None:
        asm = compile_preprocessed(src, cc1, cflags, pre.stdout, keep_rodata,
                                   arm)
        buildcache.store("c", key, asm)
    buildcache.write_if_changed(out, asm)


def compile_preprocessed(src: str, cc1: str, cflags: list[str], pre: str,
                         keep_rodata: bool, arm: bool = False) -> bytes:
    cc = subprocess.run([cc1, *cflags, "-o", "-", "-"],
                        input=pre, capture_output=True, text=True)
    if cc.returncode:
        sys.exit(f"{os.path.basename(cc1)} failed on {src}:\n{cc.stderr}")
    return wrap_asm(cc.stdout, src, keep_rodata, arm).encode()


def wrap_asm(asm: str, src: str, keep_rodata: bool = False,
             arm: bool = False) -> str:
    """Makes compiler output assemble as a region's contents.

    The region wrapper is .syntax unified; agbcc emits divided syntax.
    agbcc_arm doesn't state its instruction set, so .arm does.
    The trailing .align pads to the 4-byte boundary with explicit zeros,
    which is what the ROM has.
    """
    return (".syntax divided\n" + (".arm\n" if arm else "")
            + place_in_text(asm, src, keep_rodata)
            + "\t.align\t2, 0\n" + ".syntax unified\n")


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    lines = [
        line.split()
        for raw in open(f"regions.{ver}.txt")
        for line in [raw.split("#", 1)[0].strip()]
        if line
    ]
    rows = [parts for parts in lines if parts[0] in C_FILE_DIRECTIVES]
    separate_rodata = {parts[3] for parts in lines if parts[0] == "c-rodata"}
    if not rows:
        print(f"no c-file rows in regions.{ver}.txt -- nothing to compile")
        return

    prefix = agbcc_prefix()
    tools = buildcache.tool_digest()
    def compile_row(row):
        directive, _, _, src, name = row[:5]
        if directive in SECTIONED_DIRECTIVES:
            compile_sectioned(src, f"build/{ver}/c/{name}.s", prefix, tools,
                              directive)
            return
        compile_one(src, f"build/{ver}/c/{name}.s", prefix, ver, tools,
                    o1=directive == "c-file-O1",
                    keep_rodata=name in separate_rodata,
                    arm=directive == "c-file-arm")

    with ThreadPoolExecutor() as pool:
        list(pool.map(compile_row, rows))
    print(f"compiled {len(rows)} C file(s) for {ver}")


if __name__ == "__main__":
    main()
