#!/usr/bin/env python3
"""Match arm_func/thumb_func addresses between the US and JP ROMs.

Workflow this supports: reverse-engineer/name functions in the US ROM
first (it's the one with the fuller function-discovery seed list), then
use this tool to find each function's address in the JP ROM so its name
can be copied into functions.jp.cfg -- rather than re-discovering the
same function from scratch in JP.

Method: disassemble every seeded arm_func/thumb_func boundary (using the
next seed's address as the end, capped) in both ROMs with Capstone, then
compare a normalized instruction signature -- mnemonic + operand string,
except `bl`/`blx` targets are masked out, since a call's relative-branch
encoding shifts when the caller and callee move by different amounts
(e.g. one side of a language/text-table size difference and the other
isn't). Two functions with an identical signature and no other candidate
sharing it are reported as a match; everything else (too short a
signature, or shared by >1 function on either side) is left out --
false negatives, not false positives, is the goal. ARM-mode and
Thumb-mode functions are matched separately (a shared instruction
encoding between the two modes doesn't mean the same code); a function's
own seed type decides which mode it's disassembled in, but the *end*
boundary is taken from the next seed of either type, since that's still
where the next known function starts.

This only proposes candidates. Confirm a match before relying on it: for
short/leaf functions with no internal `bl` calls, do a direct byte
comparison (they're often byte-identical -- see memcpy/getDmaAddress in
docs/memory-map/krawall.md for a worked example); for functions that call
elsewhere, a few masked bytes differing only at `bl` sites is expected
and fine. Also worth knowing: matches tend to fall into local address
"delta clusters" -- runs of consecutive functions all shifted by the same
constant -- because localized text/data of different sizes shifts
everything after it by a fixed amount until the next such gap. A
match whose delta doesn't fit its neighbors' cluster is worth double
-checking.

Usage: match_functions.py [--min-insns N]
  Requires baserom.us.gba and baserom.jp.gba in the repo root.
  Prints one line per unique match to stdout, tab-separated:
    kind  us_addr  jp_addr  delta  name  byte_length  insn_count
  (name is only ever populated for matches involving an already-named
  US function -- most matches are between anonymous functions.)
"""
import argparse
import re
import sys
from pathlib import Path

from capstone import CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB, Cs

REPO_ROOT = Path(__file__).resolve().parent.parent
ROM_BASE = 0x08000000


def load_rom(path: Path) -> bytes:
    return path.read_bytes()


def load_funcs(cfg_path: Path) -> list[tuple[int, str, str | None]]:
    """Sorted, de-duplicated (address, kind, name-or-None) from a functions.<ver>.cfg.

    kind is "arm" or "thumb". Sorted by address across both kinds together,
    since that combined ordering is what determines each function's extent.
    """
    funcs = set()
    for line in cfg_path.read_text().splitlines():
        m = re.match(r"^(arm|thumb)_func\s+(0x[0-9A-Fa-f]+)(?:\s+(\S+))?", line.strip())
        if m:
            funcs.add((int(m.group(2), 16), m.group(1), m.group(3)))
    return sorted(funcs, key=lambda x: x[0])


def normalize_operand(mnemonic: str, op_str: str) -> str:
    # bl/blx targets shift independently of the function containing them.
    return "X" if mnemonic in ("bl", "blx") else op_str


def function_signature(rom: bytes, base: int, start: int, end: int, md: Cs, cap: int):
    end = min(end, start + cap, base + len(rom))
    data = rom[start - base : end - base]
    sig = []
    length = 0
    for insn in md.disasm(data, start):
        sig.append((insn.mnemonic, normalize_operand(insn.mnemonic, insn.op_str)))
        length = insn.address + insn.size - start
    return tuple(sig), length


def build_signatures(rom: bytes, base: int, funcs, md_by_kind: dict[str, Cs], min_insns: int, cap: int):
    """funcs is the combined (addr, kind, name) list; boundaries come from it,
    but only functions matching `kind` get a signature entry, keyed by
    (kind, signature) so ARM and Thumb never collide."""
    sigs: dict[tuple, list[int]] = {}
    info: dict[int, tuple[str, str | None, int, int]] = {}
    for i, (addr, kind, name) in enumerate(funcs):
        end = funcs[i + 1][0] if i + 1 < len(funcs) else addr + cap
        sig, length = function_signature(rom, base, addr, end, md_by_kind[kind], cap)
        if len(sig) < min_insns:
            continue
        info[addr] = (kind, name, length, len(sig))
        sigs.setdefault((kind, sig), []).append(addr)
    return sigs, info


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--min-insns", type=int, default=3, help="skip functions shorter than this (default 3)")
    ap.add_argument("--cap", type=lambda s: int(s, 0), default=0x400, help="max bytes to disassemble per function (default 0x400)")
    args = ap.parse_args()

    us_rom = load_rom(REPO_ROOT / "baserom.us.gba")
    jp_rom = load_rom(REPO_ROOT / "baserom.jp.gba")
    us_funcs = load_funcs(REPO_ROOT / "functions.us.cfg")
    jp_funcs = load_funcs(REPO_ROOT / "functions.jp.cfg")

    md_by_kind = {
        "arm": Cs(CS_ARCH_ARM, CS_MODE_ARM),
        "thumb": Cs(CS_ARCH_ARM, CS_MODE_THUMB),
    }

    us_sigs, us_info = build_signatures(us_rom, ROM_BASE, us_funcs, md_by_kind, args.min_insns, args.cap)
    jp_sigs, jp_info = build_signatures(jp_rom, ROM_BASE, jp_funcs, md_by_kind, args.min_insns, args.cap)

    us_counts = {k: sum(1 for _, kind, _ in us_funcs if kind == k) for k in ("arm", "thumb")}
    jp_counts = {k: sum(1 for _, kind, _ in jp_funcs if kind == k) for k in ("arm", "thumb")}
    print(f"US funcs: {us_counts['arm']} arm / {us_counts['thumb']} thumb  "
          f"JP funcs: {jp_counts['arm']} arm / {jp_counts['thumb']} thumb", file=sys.stderr)
    print(f"US unique sigs: {len(us_sigs)}  JP unique sigs: {len(jp_sigs)}", file=sys.stderr)

    matches = []
    ambiguous = 0
    for key, us_addrs in us_sigs.items():
        jp_addrs = jp_sigs.get(key)
        if not jp_addrs:
            continue
        if len(us_addrs) == 1 and len(jp_addrs) == 1:
            us_addr = us_addrs[0]
            kind, name, length, ninsn = us_info[us_addr]
            matches.append((us_addr, jp_addrs[0], kind, name, length, ninsn))
        else:
            ambiguous += len(us_addrs)

    matches.sort(key=lambda m: m[0])
    print(f"Unique 1:1 matches: {len(matches)}  (ambiguous US funcs skipped: {ambiguous})", file=sys.stderr)

    print("kind\tus_addr\tjp_addr\tdelta\tname\tlength\tinsn_count")
    for us_addr, jp_addr, kind, name, length, ninsn in matches:
        print(f"{kind}\t0x{us_addr:08X}\t0x{jp_addr:08X}\t{jp_addr - us_addr:+d}\t{name or ''}\t{length}\t{ninsn}")


if __name__ == "__main__":
    main()
