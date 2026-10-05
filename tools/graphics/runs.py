"""Graphics groups: the `graphics` rows of regions.<ver>.txt.

A manifest row `graphics <start> <end> <feature> <Group>` claims one group:
contiguous graphics of one feature, made of runs of one kind each.
graphics/<feature>.yaml describes the feature's groups, shared by both
versions:

  groups:
    - name: PumpkinGraphics
      runs:
        - kind: image-bank
          count: 43
          names: {1: Pumpkin001}
        - kind: graphic-blobs
          names: [ServePumpkinJuiceBg0Graphic, ServePumpkinJuiceBg1Graphic]

`names` is a list with one name per item, or a mapping from one-based
positions to names: each names the items from its position up to the next
entry, counting up the name's trailing number. `count` is required with a
mapping. Any other keys are the kind's options (see each kind's OPTIONS).

The feature's editable files live in data/graphics/<feature>/, whose
graphics.json maps each group to the item settings of each of its runs. Each
feature has one generated header, include/gen/graphics/<feature>.h,
declaring the labels of all its groups. Every label is g<Name>, plus a
suffix for items with several pieces. See docs/formats/graphics.md
("Graphics build format").

Each kind is a module in kinds/ with:
  ITEMS                       the key of a run's items in check() and files()
  OPTIONS                     its options and their defaults
  check(run)                  raise ValueError for invalid settings
  files(run)                  the feature directory entries the run owns
  item_files(item)            the files one item is built from
  build(source, options, item) -> [(label, bytes)]
  walk(rom, ver, run)         each item's (start, end) from run.start,
                              reading no further than run.limit
  extract(rom, ver, run, source, find) -> the items' settings, named;
                              writes the files. find(name) is the address of
                              a named item of this version.
"""
import json
import re
import sys
from pathlib import Path

import yaml

ROOT = Path(__file__).resolve().parents[2]
for sub in ("tools", "tools/graphics", "tools/images", "tools/graphic_blob", "tools/fonts",
            "tools/room_graphics"):
    if str(ROOT / sub) not in sys.path:
        sys.path.insert(0, str(ROOT / sub))

from kinds import fonts, graphic_blobs, image_bank, room_graphics, tile_frames, tile_streams  # noqa: E402

KINDS = {"image-bank": image_bank, "graphic-blobs": graphic_blobs, "tile-streams": tile_streams,
         "tile-frames": tile_frames, "fonts": fonts, "room-graphics": room_graphics}
VERSIONS = ("us", "jp")
LAYOUT = ROOT / "graphics"
DATA = ROOT / "data" / "graphics"
INDEX = "graphics.json"
SYMBOL = re.compile(r"[A-Za-z_][A-Za-z0-9_]*\Z")


class Run:
    def __init__(self, group: "Group", kind: str, names: list[str], options: dict):
        self.group, self.kind, self.names, self.options = group, kind, names, options
        self.count = len(names)
        self.start: int | None = None
        self.limit: int | None = None


class Group:
    def __init__(self, feature: str, name: str):
        self.feature, self.name = feature, name
        self.source = DATA / feature
        self.runs: list[Run] = []


def _names(names, count) -> list[str]:
    if isinstance(names, list):
        if count is not None and count != len(names):
            raise ValueError(f"count is {count} but names lists {len(names)}")
        out = names
    elif isinstance(names, dict) and isinstance(count, int) and count > 0:
        out = [None] * count
        starts = sorted(names)
        if starts[0] != 1 or starts[-1] > count:
            raise ValueError("names must start at position 1 and stay within count")
        for start, end in zip(starts, starts[1:] + [count + 1]):
            m = re.fullmatch(r"(.*?)(\d+)", names[start])
            if end - start > 1 and not m:
                raise ValueError(f"{names[start]} names several items but has no trailing number")
            stem, digits = m.groups() if m else (names[start], "")
            out[start - 1:end - 1] = ([names[start]] if end - start == 1 else
                                      [f"{stem}{int(digits) + i:0{len(digits)}d}" for i in range(end - start)])
    else:
        raise ValueError("names must be a list, or a mapping of positions with a count")
    if not all(isinstance(n, str) and SYMBOL.fullmatch(n) for n in out) or len(set(out)) != len(out):
        raise ValueError("names must be distinct symbols")
    return out


def features() -> dict[str, list[Group]]:
    """Every graphics/<feature>.yaml, by feature path."""
    out, seen = {}, set()
    for path in sorted(LAYOUT.rglob("*.yaml")):
        feature = path.relative_to(LAYOUT).with_suffix("").as_posix()
        doc = yaml.safe_load(path.read_text())
        if not isinstance(doc, dict) or set(doc) != {"groups"}:
            raise ValueError(f"{path}: expected groups")
        groups = []
        for g in doc["groups"]:
            if not isinstance(g, dict) or set(g) != {"name", "runs"} or g["name"] in seen:
                raise ValueError(f"{path}: each group needs a distinct name and runs")
            seen.add(g["name"])
            group = Group(feature, g["name"])
            for i, r in enumerate(g["runs"], 1):
                try:
                    kind = KINDS[r["kind"]]
                    extra = set(r) - {"kind", "names", "count"} - set(kind.OPTIONS)
                    if extra:
                        raise ValueError(f"unknown keys {', '.join(sorted(extra))}")
                    options = {**kind.OPTIONS, **{k: v for k, v in r.items() if k in kind.OPTIONS}}
                    group.runs.append(Run(group, r["kind"], _names(r["names"], r.get("count")), options))
                except (KeyError, TypeError, ValueError) as exc:
                    raise ValueError(f"{path}: {g['name']} run {i}: {exc}") from None
            groups.append(group)
        out[feature] = groups
    return out


def groups() -> dict[str, Group]:
    return {g.name: g for gs in features().values() for g in gs}


class Row:
    def __init__(self, start: int, end: int, group: Group):
        self.start, self.end, self.group = start, end, group


def rows(ver: str, known: dict[str, Group]) -> list[Row]:
    """The graphics rows of regions.<ver>.txt, in address order."""
    path = ROOT / f"regions.{ver}.txt"
    out = []
    for lineno, raw in enumerate(path.read_text().splitlines(), 1):
        parts = raw.split("#", 1)[0].split()
        if parts and parts[0] == "graphics":
            if len(parts) != 5:
                raise ValueError(f"{path.name}:{lineno}: expected graphics <start> <end> <feature> <group>")
            group = known.get(parts[4])
            if group is None or group.feature != parts[3]:
                raise ValueError(f"{path.name}:{lineno}: graphics/{parts[3]}.yaml has no group {parts[4]}")
            out.append(Row(int(parts[1], 16), int(parts[2], 16), group))
    return sorted(out, key=lambda r: r.start)


def named(run: Run, items: list[dict]) -> dict:
    """A run's options and items, each item named, for its kind's check()."""
    if len(items) != run.count:
        raise ValueError(f"the description has {run.count} items, {INDEX} has {len(items)}")
    return {**run.options, KINDS[run.kind].ITEMS: [{"name": n, **item} for n, item in zip(run.names, items)]}


def load(feature: str, groups: list[Group]) -> dict[str, list[dict]]:
    """A feature's groups from graphics.json: for each, every run's options
    and named items, checked."""
    path = DATA / feature / INDEX
    index = json.loads(path.read_text())
    if set(index) != {"format", "groups"} or index["format"] != 2:
        raise ValueError(f"{path}: expected format 2 with groups")
    expected = {g.name: g for g in groups}
    if set(index["groups"]) != set(expected):
        raise ValueError(f"{path}: has groups {sorted(index['groups'])}, "
                         f"graphics/{feature}.yaml {sorted(expected)}")
    out, owned = {}, {INDEX: ""}
    for name, run_items in index["groups"].items():
        group = expected[name]
        if len(run_items) != len(group.runs):
            raise ValueError(f"{path}: {name} has {len(run_items)} runs, the description {len(group.runs)}")
        out[name] = []
        for i, (run, items) in enumerate(zip(group.runs, run_items), 1):
            kind = KINDS[run.kind]
            try:
                settings = named(run, items)
                kind.check(settings)
            except (ValueError, TypeError, KeyError) as exc:
                raise ValueError(f"{path}: {name} run {i}: {exc}") from None
            for file in kind.files(settings):
                if file in owned:
                    raise ValueError(f"{path}: {name} and {owned[file] or INDEX} both use {file}")
                owned[file] = name
            out[name].append(settings)
    # A subdirectory with its own index is a nested feature.
    unowned = sorted({p.name for p in (DATA / feature).iterdir() if not (p / INDEX).is_file()} - set(owned))
    if unowned:
        raise ValueError(f"{path}: files no group uses: {', '.join(unowned)}")
    return out


def header_path(feature: str) -> Path:
    return ROOT / "include" / "gen" / "graphics" / f"{feature}.h"


def _dump(value, indent: str = "") -> str:
    """JSON with short containers on one line and long ones split per element."""
    flat = json.dumps(value)
    if len(indent) + len(flat) <= 100 or not isinstance(value, (dict, list)) or not value:
        return flat
    inner = indent + "  "
    if isinstance(value, dict):
        body = [f"{inner}{json.dumps(k)}: {_dump(v, inner)}" for k, v in value.items()]
        return "{\n" + ",\n".join(body) + f"\n{indent}}}"
    return "[\n" + ",\n".join(inner + _dump(v, inner) for v in value) + f"\n{indent}]"


def write_index(feature: str, groups: dict[str, list[list[dict]]]) -> None:
    (DATA / feature).mkdir(parents=True, exist_ok=True)
    (DATA / feature / INDEX).write_text(_dump({"format": 2, "groups": groups}) + "\n")
