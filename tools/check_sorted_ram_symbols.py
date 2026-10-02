#!/usr/bin/env python3
"""Check that ram_symbols.<ver>.inc `.set` rows are sorted by address.

Every symbol row is `.set <name>, <address>  @ comment` -- this checks those
addresses are non-decreasing top to bottom. Comments and blank lines are
ignored.
"""
import re
import sys

SET_RE = re.compile(r"^\.set\s+\w+\s*,\s*(0[xX][0-9A-Fa-f]+|\d+)")


def check(path: str) -> list[str]:
    errors = []
    prev_addr = None
    prev_lineno = None
    with open(path) as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.strip()
            if not line.startswith(".set"):
                continue
            m = SET_RE.match(line)
            if not m:
                sys.exit(f"{path}:{lineno}: couldn't parse an address from this row")
            addr = int(m.group(1), 0)
            if prev_addr is not None and addr < prev_addr:
                errors.append(
                    f"{path}:{lineno}: address {addr:#010x} is out of order "
                    f"(follows {path}:{prev_lineno}'s {prev_addr:#010x})"
                )
            prev_addr, prev_lineno = addr, lineno
    return errors


def main() -> int:
    errors = []
    for ver in ("us", "jp"):
        errors += check(f"ram_symbols.{ver}.inc")
    if errors:
        for e in errors:
            print(e, file=sys.stderr)
        print(f"{len(errors)} RAM symbol row(s) out of address order", file=sys.stderr)
        return 1
    print("ram_symbols.us.inc and ram_symbols.jp.inc are sorted by address")
    return 0


if __name__ == "__main__":
    sys.exit(main())
