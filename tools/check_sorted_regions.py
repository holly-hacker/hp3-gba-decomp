#!/usr/bin/env python3
"""Check that regions.<ver>.txt rows are sorted by address.

Every row starts with a directive keyword whose second field is the
region's start address (or the label/thumb-func address). This checks
those addresses are non-decreasing top to bottom; comments and blank
lines are ignored, so a comment attached above one entry (see
regions.us.txt's own conventions) doesn't affect the check.

It also requires a region row's <end> to be `_` when it equals the next
region row's start, and exits on the first row that spells it out.
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from manifest import LABEL_DIRECTIVES, NEXT_START  # noqa: E402


def addr_of(line: str) -> int:
    return int(line.split()[1], 16)


def check(path: str) -> list[str]:
    errors = []
    prev_addr = None
    prev_lineno = None
    prev_region = None  # (lineno, explicit end) of the last region row
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
            fields = line.split("#", 1)[0].split()
            if fields[0] in LABEL_DIRECTIVES:
                continue
            if prev_region is not None and prev_region[1] == addr:
                sys.exit(
                    f"{path}:{prev_region[0]}: end {addr:#010x} is the next region row's "
                    f"start; write it as '{NEXT_START}'"
                )
            prev_region = None
            if len(fields) >= 3 and fields[2] != NEXT_START:
                try:
                    prev_region = (lineno, int(fields[2], 16))
                except ValueError:
                    pass
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
