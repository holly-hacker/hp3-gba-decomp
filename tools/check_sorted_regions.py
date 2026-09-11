#!/usr/bin/env python3
"""Check that regions.<ver>.txt rows are sorted by address.

Every row starts with a directive keyword whose second field is the
region's start address (or the label/thumb-func address). This checks
those addresses are non-decreasing top to bottom; comments and blank
lines are ignored, so a comment attached above one entry (see
regions.us.txt's own conventions) doesn't affect the check.
"""
import sys


def addr_of(line: str) -> int:
    return int(line.split()[1], 16)


def check(path: str) -> list[str]:
    errors = []
    prev_addr = None
    prev_lineno = None
    with open(path) as f:
        for lineno, raw_line in enumerate(f, 1):
            line = raw_line.strip()
            if not line or line.startswith("#"):
                continue
            try:
                addr = addr_of(line)
            except (IndexError, ValueError):
                sys.exit(f"{path}:{lineno}: couldn't parse an address from this row")
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
        errors += check(f"regions.{ver}.txt")
    if errors:
        for e in errors:
            print(e, file=sys.stderr)
        print(f"{len(errors)} region row(s) out of address order", file=sys.stderr)
        return 1
    print("regions.us.txt and regions.jp.txt are sorted by address")
    return 0


if __name__ == "__main__":
    sys.exit(main())
