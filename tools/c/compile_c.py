#!/usr/bin/env python3
"""Compile the c-file and c-file-O1 rows of regions.<ver>.txt to assembly.

agbcc is a bare cc1: it takes preprocessed C and writes assembly, so the
pipeline is cpp -> agbcc -> build/<ver>/c/<name>.s, which gen_link.py
wraps into the region's object.

The compiler profile is picked by directory (src/libc/ uses old_agbcc
without interworking; other sources use agbcc with interworking).
The manifest directive selects -O2 (c-file) or -O1 (c-file-O1).

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


def profile(src: str, prefix: str, o1: bool = False) -> tuple[str, list[str], list[str]]:
    """Returns (cc1, cppflags, cflags) for a source file."""
    inc = os.path.join(prefix, "include")
    optimization = "-O1" if o1 else "-O2"
    if src.startswith("src/libc/"):
        return (
            os.path.join(prefix, "bin", "old_agbcc"),
            ["-I", inc, "-nostdinc", "-undef", "-DABORT_PROVIDED",
             "-DHAVE_GETTIMEOFDAY", "-D__thumb__", "-DARM_RDI_MONITOR",
             "-D__GNUC__", "-DINTERNAL_NEWLIB", "-D__USER_LABEL_PREFIX__="],
            [optimization, "-fno-builtin"],
        )
    return (
        os.path.join(prefix, "bin", "agbcc"),
        ["-I", "include", "-I", inc, "-nostdinc", "-undef", "-std=gnu89"],
        # -fno-builtin: without it, agbcc treats any declaration/definition
        # of a reserved name (memset, ...) as conflicting with its own
        # builtin prototype. Applies to every game-code file, not just the
        # ones that currently reference such a name, so this doesn't need
        # to grow a list as more of them show up.
        [optimization, "-mthumb-interwork", "-Wimplicit", "-Wparentheses",
         "-Werror", "-fhex-asm", "-fno-builtin"],
    )


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


def compile_one(src: str, out: str, prefix: str, o1: bool = False,
                keep_rodata: bool = False) -> None:
    cc1, cppflags, cflags = profile(src, prefix, o1)
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
        f.write(place_in_text(cc.stdout, src, keep_rodata))
        f.write("\t.align\t2, 0\n")
        f.write(".syntax unified\n")


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
    rows = [parts for parts in lines if parts[0] in {"c-file", "c-file-O1"}]
    separate_rodata = {parts[3] for parts in lines if parts[0] == "c-rodata"}
    if not rows:
        print(f"no c-file rows in regions.{ver}.txt -- nothing to compile")
        return

    prefix = agbcc_prefix()
    for directive, _, _, src, name in rows:
        compile_one(src, f"build/{ver}/c/{name}.s", prefix,
                    o1=directive == "c-file-O1",
                    keep_rodata=name in separate_rodata)
    print(f"compiled {len(rows)} C file(s) for {ver}")


if __name__ == "__main__":
    main()
