#!/usr/bin/env python3
"""The C compilers' flags, and the compile step of third-party sources.

agbcc is a bare cc1: it takes preprocessed C and writes assembly. Game C
goes cpp -> agbcc -> build/<ver>/c/<name>.s through the rules
tools/configure.py writes from profile(); the manifest directive selects
-O2 (c-file), -O1 (c-file-O1) or agbcc_arm for ARM-mode code (c-file-arm).

Third-party code has its own compiler: c-file-gcc3 and c-file-gcc3-arm
use GCC 3.0.2, and asm-file-cpp rows are only preprocessed. Their output
needs fix-ups, so this script compiles them one file per call.

Usage: compile_c.py <directive> <source> <out>   (writes <out>.d for Ninja)
"""
import os
import re
import shutil
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from krawall.gen_header import OUTPUT as KRAWALL_HEADER  # noqa: E402
from manifest import ASM_CPP_DIRECTIVE, SECTIONED_DIRECTIVES  # noqa: E402

GCC3_CC1 = "arm-elf-cc1-3.0.2"

# Krawall's build configuration: mixing buffers, channels and player state
# in EWRAM. The 16 kHz, 60 Hz default needs no define.
KRAWALL_DEFINES = ["-DIWRAM_USAGE_SMALL"]


def agbcc_prefix() -> str:
    exe = shutil.which("agbcc")
    if exe is None:
        sys.exit("agbcc not found -- are you in `nix develop`?")
    return os.path.dirname(os.path.dirname(os.path.realpath(exe)))


def profile(prefix: str, o1: bool = False, ver: str | None = None,
            arm: bool = False) -> tuple[str, list[str], list[str]]:
    """Returns (cc1, cppflags, cflags) for game C.

    ver defines VERSION_US or VERSION_JP for game code whose source differs
    between the two ROMs. arm selects agbcc_arm, which lacks -fhex-asm,
    needs -quiet to stop printing pass timings, and needs
    -fomit-frame-pointer to drop the APCS frame the ROM doesn't have.

    __GNUC__ is agbcc's (GCC 2): -undef drops the host compiler's, and
    Krawall's public header (generated into build/include by
    tools/krawall/gen_header.py) maps its IWRAM functions to their stubs
    for GCC 2.
    """
    inc = os.path.join(prefix, "include")
    optimization = "-O1" if o1 else "-O2"
    krawall_include = os.path.dirname(os.path.dirname(KRAWALL_HEADER))
    cppflags = ["-I", "include", "-I", krawall_include, "-I", inc,
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
             "-fno-builtin", "-marm" if arm else "-mthumb"])


def section_names(asm: str) -> list[str]:
    """Every section the assembly switches to, in order of first use.
    Directives are case-insensitive; Krawall's .S files write .TEXT."""
    names = re.findall(r"^\s*(?:\.section\s+([.\w]+)|\.(text|data|bss)\b)",
                       asm, re.M | re.I)
    return list(dict.fromkeys(a or f".{b.lower()}" for a, b in names))


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


def compile_sectioned(src: str, out: str, prefix: str,
                      directive: str) -> None:
    """Compiles (or, for a .S, preprocesses) a third-party source.

    Its sections stay apart for the manifest to place. Each section ends
    padded to 4 bytes with the assembler's fill (nop in code, zeros
    elsewhere), as it was between the original objects.
    """
    arm = directive != "c-file-gcc3"
    cc1, cppflags, cflags = gcc3_profile(src, prefix, arm)
    if directive == ASM_CPP_DIRECTIVE:
        cppflags = ["-x", "assembler-with-cpp", "-D__ASSEMBLER__", *cppflags]
    pre = subprocess.run(["cpp", "-P", *cppflags, "-MD", "-MF", f"{out}.d",
                          "-MT", out, src],
                         capture_output=True, text=True)
    if pre.returncode:
        sys.exit(f"cpp failed on {src}:\n{pre.stderr}")
    if directive == ASM_CPP_DIRECTIVE:
        asm = pre.stdout
    else:
        cc = subprocess.run([cc1, *cflags, "-o", "-", "-"],
                            input=pre.stdout, capture_output=True, text=True)
        if cc.returncode:
            sys.exit(f"{GCC3_CC1} failed on {src}:\n{cc.stderr}")
        # `.file "<stdin>"` would make the assembler list <stdin> as a
        # dependency.
        asm = re.sub(r"^\s*\.file\s.*\n", "", cc.stdout, flags=re.M)
        # The original assembler filled an .align inside code with zeros;
        # only the end of a section got nops. Today's fills both with nops.
        asm = re.sub(r"^(\s*\.align\s+\d+)\s*$", r"\1, 0", asm, flags=re.M)
        asm = merge_section_flags(asm)
    # The assembler ignores everything after .END, padding included.
    end = re.search(r"^\s*\.end\b", asm, re.M | re.I)
    if end:
        asm = asm[:end.start()]
    padding = "".join(f"\t.section\t{name}\n\t.align\t2\n"
                      for name in section_names(asm) if name != ".bss")
    with open(out, "w") as f:
        f.write(asm + "\n" + padding)


def main() -> None:
    if len(sys.argv) != 4 or sys.argv[1] not in SECTIONED_DIRECTIVES:
        sys.exit(f"usage: {sys.argv[0]} <directive> <source> <out>")
    directive, src, out = sys.argv[1:]
    compile_sectioned(src, out, agbcc_prefix(), directive)


if __name__ == "__main__":
    main()
