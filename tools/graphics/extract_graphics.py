#!/usr/bin/env python3
"""Extract graphics groups from the baseroms into data/graphics/.

Each group of each version is walked from its start, run by run, and must
end exactly at the manifest's end address. Each group is extracted once,
from the first version whose manifest has it (us, then jp), and every item
must rebuild to that ROM's bytes. With no group names, data/graphics/ is
cleared first and every group is extracted; with names, only those groups'
files and settings are replaced.

data/graphics/ is gitignored, same footing as the baserom (AGENTS.md hard
rule 2); extraction overwrites local edits.

Usage: extract_graphics.py [group ...]
"""
import copy
import json
import shutil
import sys
from pathlib import Path

import runs


def remove(path: Path) -> None:
    if path.is_dir():
        shutil.rmtree(path)
    elif path.exists():
        path.unlink()


def walk(ver: str, rom: bytes, known) -> tuple[dict[str, list[runs.Run]], dict[str, int]]:
    """Every group of this version as runs with their starts set, and every
    item's address."""
    found, addresses = {}, {}
    for row in runs.rows(ver, known):
        addr, walked = row.start, []
        for run in row.group.runs:
            run = copy.copy(run)
            run.start, run.limit = addr, row.end
            try:
                spans = runs.KINDS[run.kind].walk(rom, ver, run)
            except (ValueError, IndexError) as exc:
                raise ValueError(f"{ver}: {row.group.name}: {exc}") from None
            addresses.update((name, start) for name, (start, _) in zip(run.names, spans))
            walked.append(run)
            addr = spans[-1][1]
        if addr != row.end:
            raise ValueError(f"{ver}: {row.group.name} ends at {addr:#010x}, not {row.end:#010x}")
        found[row.group.name] = walked
    return found, addresses


def main() -> None:
    wanted = set(sys.argv[1:])
    try:
        features = runs.features()
        known = {g.name: g for gs in features.values() for g in gs}
        roms, walked = {}, {}
        for ver in runs.VERSIONS:
            roms[ver] = (runs.ROOT / f"baserom.{ver}.gba").read_bytes()
            walked[ver] = walk(ver, roms[ver], known)
        plan: dict[str, str] = {}
        for ver in runs.VERSIONS:
            for name in walked[ver][0]:
                if not wanted or name in wanted:
                    plan.setdefault(name, ver)
        if wanted - set(plan):
            raise ValueError(f"no manifest has a graphics group named {', '.join(sorted(wanted - set(plan)))}")
        if not wanted:
            remove(runs.DATA)

        for feature, groups in features.items():
            if not any(g.name in plan for g in groups):
                continue
            index = runs.DATA / feature / runs.INDEX
            settings = json.loads(index.read_text())["groups"] if index.is_file() else {}
            for group in groups:
                if group.name not in plan:
                    continue
                ver = plan[group.name]
                if group.name in settings:
                    for run, items in zip(group.runs, settings[group.name]):
                        for file in runs.KINDS[run.kind].files(runs.named(run, items)):
                            remove(group.source / file)
                group.source.mkdir(parents=True, exist_ok=True)
                extracted = []
                for run in walked[ver][0][group.name]:
                    try:
                        items = runs.KINDS[run.kind].extract(roms[ver], ver, run, group.source,
                                                              walked[ver][1].__getitem__)
                    except (ValueError, IndexError, KeyError) as exc:
                        raise ValueError(f"{ver}: {group.name}: {exc}") from None
                    extracted.append([{k: v for k, v in item.items() if k != "name"} for item in items])
                settings[group.name] = extracted
                print(f"{ver}: extracted {group.name} into {group.source.relative_to(runs.ROOT)}")
            runs.write_index(feature, {g.name: settings[g.name] for g in groups if g.name in settings})
    except (OSError, ValueError) as exc:
        sys.exit(str(exc))


if __name__ == "__main__":
    main()
