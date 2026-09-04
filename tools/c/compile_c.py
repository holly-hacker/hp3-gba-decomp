#!/usr/bin/env python3
"""Compile the c-file rows of regions.<ver>.txt to assembly.

agbcc is a bare cc1: it takes preprocessed C and writes assembly, so the
pipeline is cpp -> agbcc -> build/<ver>/c/<name>.s, which gen_link.py
wraps into the region's object.

Two flag profiles, picked by directory, because the ROM's own halves were
built differently (docs/compiler.md): src/libc/ is newlib, built with
old_agbcc and no interworking; everything else is game code, built with
agbcc and -mthumb-interwork.

Usage: compile_c.py <ver>   (before `gen-link`)
"""
import os
import re
import shutil
import subprocess
import sys

def agbcc_prefix() -> str:
    exe = shutil.which("agbcc")
    if exe is None:
        sys.exit("agbcc not found -- are you in `nix develop`?")
    return os.path.dirname(os.path.dirname(os.path.realpath(exe)))


def profile(src: str, prefix: str) -> tuple[str, list[str], list[str]]:
    """Returns (cc1, cppflags, cflags) for a source file."""
    inc = os.path.join(prefix, "include")
    if src.startswith("src/libc/"):
        return (
            os.path.join(prefix, "bin", "old_agbcc"),
            ["-I", inc, "-nostdinc", "-undef", "-DABORT_PROVIDED",
             "-DHAVE_GETTIMEOFDAY", "-D__thumb__", "-DARM_RDI_MONITOR",
             "-D__GNUC__", "-DINTERNAL_NEWLIB", "-D__USER_LABEL_PREFIX__="],
            ["-O2", "-fno-builtin"],
        )
    return (
        os.path.join(prefix, "bin", "agbcc"),
        ["-I", "include", "-I", inc, "-nostdinc", "-undef", "-std=gnu89"],
        # -fno-builtin: without it, agbcc treats any declaration/definition
        # of a reserved name (memset, ...) as conflicting with its own
        # builtin prototype. Applies to every game-code file, not just the
        # ones that currently reference such a name, so this doesn't need
        # to grow a list as more of them show up.
        ["-O2", "-mthumb-interwork", "-Wimplicit", "-Wparentheses",
         "-Werror", "-fhex-asm", "-fno-builtin"],
    )


def place_in_text(asm: str, src: str) -> str:
    """Fold read-only data into .text, and reject what has nowhere to go.

    The generated link.ld places each region's .text and nothing else, so
    agbcc's `.section .rodata` for const data has to become .text -- the
    bytes are the same and both live in ROM. `.data` and .comm/.lcomm have no home:
    they want writable RAM, whose addresses are fixed by the ROM, so RAM
    variables belong in ram_symbols.<ver>.inc and are `extern` in C.
    """
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


def compile_one(src: str, out: str, prefix: str) -> None:
    cc1, cppflags, cflags = profile(src, prefix)
    pre = subprocess.run(["cpp", *cppflags, src],
                         capture_output=True, text=True)
    if pre.returncode:
        sys.exit(f"cpp failed on {src}:\n{pre.stderr}")
    cc = subprocess.run([cc1, *cflags, "-o", "-", "-"],
                        input=pre.stdout, capture_output=True, text=True)
    if cc.returncode:
        sys.exit(f"{os.path.basename(cc1)} failed on {src}:\n{cc.stderr}")

    os.makedirs(os.path.dirname(out), exist_ok=True)
    with open(out, "w") as f:
        # The region wrapper is .syntax unified; agbcc emits divided
        # syntax. The trailing .align pads to the 4-byte boundary with
        # explicit zeros, which is what the ROM has.
        f.write(".syntax divided\n")
        f.write(place_in_text(cc.stdout, src))
        f.write("\t.align\t2, 0\n")
        f.write(".syntax unified\n")


def main() -> None:
    if len(sys.argv) != 2:
        sys.exit(f"usage: {sys.argv[0]} <ver>")
    ver = sys.argv[1]

    rows = [
        line.split()
        for raw in open(f"regions.{ver}.txt")
        for line in [raw.split("#", 1)[0].strip()]
        if line.startswith("c-file ")
    ]
    if not rows:
        print(f"no c-file rows in regions.{ver}.txt -- nothing to compile")
        return

    prefix = agbcc_prefix()
    for _, _, _, src, name in rows:
        compile_one(src, f"build/{ver}/c/{name}.s", prefix)
    print(f"compiled {len(rows)} C file(s) for {ver}")


if __name__ == "__main__":
    main()
