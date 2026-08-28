#!/usr/bin/env python3
"""Generate compile_commands.json for clangd, from compile_c.py's own flag profiles.

The agbcc include path lives in the Nix store, so this has to be re-run
(inside `nix develop`) whenever that path moves -- e.g. after a flake update.

Usage: gen_compile_commands.py
"""
import glob
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import compile_c

# agbcc-only or build-strictness flags that mean nothing to clang and would
# just add noise or false errors in editor diagnostics: -fhex-asm controls
# agbcc's asm output formatting, -mthumb-interwork/-O2 are codegen-only, and
# -Werror would turn clang's (differently-tuned) warnings into red squiggles
# styled as hard errors.
DROP = {"-fhex-asm", "-mthumb-interwork", "-Werror", "-O2"}


def clang_args(src: str, prefix: str) -> list[str]:
    _, cppflags, cflags = compile_c.profile(src, prefix)
    flags = [f for f in [*cppflags, *cflags] if f not in DROP]
    if not any(f.startswith("-std=") for f in flags):
        flags.append("-std=gnu89")  # old_agbcc's newlib profile omits it too
    return ["clang", "-xc", *flags, "-c", src]


def main() -> None:
    root = os.path.dirname(os.path.dirname(os.path.dirname(
        os.path.abspath(__file__))))
    prefix = compile_c.agbcc_prefix()

    entries = [
        {"directory": root, "file": src, "arguments": clang_args(src, prefix)}
        for src in sorted(glob.glob("src/**/*.c", recursive=True, root_dir=root))
    ]

    out = os.path.join(root, "compile_commands.json")
    with open(out, "w") as f:
        json.dump(entries, f, indent=2)
        f.write("\n")
    print(f"wrote {len(entries)} entries to {out}")


if __name__ == "__main__":
    main()
