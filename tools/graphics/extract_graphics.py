#!/usr/bin/env python3
"""Extract graphics groups from the baseroms into data/graphics/.

Each group of each version is walked from its start in GROUP_ADDRESSES,
run by run, and must end exactly at its end there. Each group is extracted
once, from the first version whose manifest has it (us, then jp), and every item
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

# Where each group is in each donor ROM: (start, end).
GROUP_ADDRESSES = {
    "us": {
        "OverworldSpellEffects": (0x0806E904, 0x080781A4),
        "AllyHeads": (0x080781A4, 0x0807E7F8),
        "OverworldPlayerSprites": (0x0807E7F8, 0x080A6D54),
        "ItemAndHelpIcons": (0x080A6D54, 0x080AC8CC),
        "MonsterOverworldSprites": (0x080AC8CC, 0x080BC1C4),
        "MenuSprites": (0x080BC1C4, 0x080BD564),
        "ActorSprites": (0x080BD564, 0x080D0B54),
        "OptionIconUs": (0x080D0B54, 0x080D0C38),
        "ActorSprites2": (0x080D0C38, 0x08196408),
        "SpecialSceneFrames": (0x081B2E98, 0x081DB29C),
        "RoomGraphics": (0x081DB29C, 0x08854EE0),
        "RoomAltPalettes": (0x08854EE0, 0x08856710),
        "BgGraphics": (0x08856710, 0x089AD364),
        "RainTiles": (0x089AD364, 0x089AE030),
        "BattleSprites": (0x089AE030, 0x08A31ADC),
        "LumosParticles": (0x08A31ADC, 0x08A326DC),
        "EquipCharacterSelect": (0x08A326DC, 0x08A37DA4),
        "BattleHudAndEffects": (0x08A37DA4, 0x08A9C6D0),
        "BuckbeakMinigameWaterFrames": (0x08D3EFFC, 0x08D3F2B4),
        "PatronusCutscene": (0x08D3F2B4, 0x08D48D74),
        "ServePumpkinJuiceFrames": (0x08D48D74, 0x08D4A410),
        "DivinationTeaFrames": (0x08D4A410, 0x08D56A68),
        "OwlCareSprites": (0x08D56A68, 0x08D71B5C),
        "OwlCarePalettes": (0x08D71E10, 0x08D71F50),
        "OwlCare": (0x08D71F70, 0x08D79D24),
        "DialogBackgrounds": (0x08D79D24, 0x08D7C480),
        "BattleEffects2": (0x08D7C480, 0x08D7E528),
        "WizardCrackerPopIt": (0x08D7E528, 0x08D80E6C),
        "WizardCrackerSprites": (0x08D80E6C, 0x08D8E7EC),
        "PumpkinGraphics": (0x08D8E7EC, 0x08D9A360),
        "DebugMenu": (0x08D9A360, 0x08DA08BC),
        "MenuSelectionPalette": (0x08DA08BC, 0x08DA0AC0),
        "CutsceneDrawings": (0x08DA0AC0, 0x08DC8084),
        "HippogriffLanguageMinigameBgs": (0x08DC8084, 0x08DF3918),
        "StatusCharacters": (0x08DF3918, 0x08E1D5DC),
        "HogwartsUpNight": (0x08E1D5DC, 0x08E3254C),
        "MainMenuTitles": (0x08E3254C, 0x08E359C0),
        "CoolTrain": (0x08E359C0, 0x08E36D88),
        "DivinationTeaGraphics": (0x08E36D88, 0x08E3D050),
        "BuckbeakMinigameGraphics": (0x08E3D050, 0x08E52964),
        "BoggartGraphics": (0x08E52964, 0x08E65D6C),
        "FontsAndPortraits": (0x08E65D6C, 0x08EAC798),
        "FamousWizardCards": (0x08F4BEDC, 0x08FA953C),
    },
    "jp": {
        "OverworldSpellEffects": (0x0806E840, 0x080780E0),
        "AllyHeads": (0x080780E0, 0x0807E734),
        "OverworldPlayerSprites": (0x0807E734, 0x080A6C90),
        "ItemAndHelpIcons": (0x080A6C90, 0x080AC808),
        "MonsterOverworldSprites": (0x080AC808, 0x080BC100),
        "MenuSprites": (0x080BC100, 0x080BD4A0),
        "ActorSprites": (0x080BD4A0, 0x080D0A90),
        "ActorSprites2": (0x080D0A90, 0x08196260),
        "SpecialSceneFrames": (0x081B2CC8, 0x081DB0CC),
        "RoomGraphics": (0x081DB0CC, 0x08854D10),
        "RoomAltPalettes": (0x08854D10, 0x08856540),
        "BgGraphics": (0x08856540, 0x089AD194),
        "RainTiles": (0x089AD194, 0x089ADE60),
        "BattleSprites": (0x089ADE60, 0x08A3190C),
        "LumosParticles": (0x08A3190C, 0x08A3250C),
        "EquipCharacterSelect": (0x08A3250C, 0x08A37BD4),
        "BattleHudAndEffects": (0x08A37BD4, 0x08A9C500),
        "BuckbeakMinigameWaterFrames": (0x08D3EE2C, 0x08D3F0E4),
        "PatronusCutscene": (0x08D3F0E4, 0x08D48BA4),
        "ServePumpkinJuiceFrames": (0x08D48BA4, 0x08D4A240),
        "DivinationTeaFrames": (0x08D4A240, 0x08D56898),
        "OwlCareSprites": (0x08D56898, 0x08D7198C),
        "OwlCarePalettes": (0x08D71C40, 0x08D71D80),
        "OwlCare": (0x08D71DA0, 0x08D79B54),
        "DialogBackgrounds": (0x08D79B54, 0x08D7C2B0),
        "BattleEffects2": (0x08D7C2B0, 0x08D7E358),
        "WizardCrackerPopIt": (0x08D7E358, 0x08D80C9C),
        "WizardCrackerSprites": (0x08D80C9C, 0x08D8E61C),
        "PumpkinGraphics": (0x08D8E61C, 0x08D9A190),
        "DebugMenu": (0x08D9A190, 0x08DA06EC),
        "MenuSelectionPalette": (0x08DA06EC, 0x08DA08F0),
        "CutsceneDrawings": (0x08DA08F0, 0x08DC7EB4),
        "HippogriffLanguageMinigameBgs": (0x08DC7EB4, 0x08DF3748),
        "StatusCharacters": (0x08DF3748, 0x08E1D40C),
        "HogwartsUpNight": (0x08E1D40C, 0x08E3237C),
        "MainMenuJp": (0x08E3237C, 0x08E339A4),
        "CoolTrain": (0x08E339A4, 0x08E34D6C),
        "DivinationTeaGraphics": (0x08E34D6C, 0x08E3B034),
        "BuckbeakMinigameGraphics": (0x08E3B034, 0x08E50948),
        "BoggartGraphics": (0x08E50948, 0x08E63D50),
        "KanjiFonts": (0x08E63D50, 0x08E836C4),
        "FontsAndPortraits": (0x08E836C4, 0x08ECA0F0),
        "FamousWizardCards": (0x08EDF36C, 0x08F3C9CC),
    },
}


def remove(path: Path) -> None:
    if path.is_dir():
        shutil.rmtree(path)
    elif path.exists():
        path.unlink()


def walk(ver: str, rom: bytes, known) -> tuple[dict[str, list[runs.Run]], dict[str, int]]:
    """Every group of this version as runs with their starts set, and every
    item's address."""
    found, addresses = {}, {}
    for group in runs.rows(ver, known):
        if group.name not in GROUP_ADDRESSES[ver]:
            raise ValueError(f"{ver}: no address for graphics group {group.name}")
        start, end = GROUP_ADDRESSES[ver][group.name]
        addr, walked = start, []
        for run in group.runs:
            run = copy.copy(run)
            run.start, run.limit = addr, end
            try:
                spans = runs.KINDS[run.kind].walk(rom, ver, run)
            except (ValueError, IndexError) as exc:
                raise ValueError(f"{ver}: {group.name}: {exc}") from None
            addresses.update((name, start) for name, (start, _) in zip(run.names, spans))
            palettes = getattr(runs.KINDS[run.kind], "palettes", None)
            if palettes is not None:
                addresses.update((f"{name}.palette", addr) for name, addr in palettes(rom, ver, run).items())
            walked.append(run)
            addr = spans[-1][1]
        if addr != end:
            raise ValueError(f"{ver}: {group.name} ends at {addr:#010x}, not {end:#010x}")
        found[group.name] = walked
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
