<!--
This file is *not* to be edited by AI agents, it may only be edited by humans.
If changed need to be made to this file, it should be proposed to a human so they can choose what and how to edit it.
--->

> [!IMPORTANT]
> If you are in any way (considering) contributing to The Cutting Room Floor, turn back now.
>
> TCRF has a very clear policy on AI: If AI was used at any point during your reverse engineering process, you may not
> contribute to their wiki. This seems to include _any_ kind of AI usage, which means all information in this repo is
> effectively poisoned. Their wiki page on HP3-GBA containing calls for contribution, missing information or straight-up
> errors does not change this.

# hp3-gba-decomp

This repo holds a heavily AI-assisted decompilation of Harry Potter and the Prisoner of Azkaban for the Gameboy Advance.

The goal of this project is to both explore automated reverse engineering, and to look into a game I've loved as a
child. A very far-off stretch goal is to make a shiftable build allowing for modding, but this seems very unlikely and
expensive. A more realistic goal is to extract assets and some of the code into a form that perfectly reproduces part of
the ROM. Minor mods can be made by appending modified data to the end of the ROM.

Note that while this project contains mostly AI-generated assets, this README is and will always be written by a human.
All code under `src/` and `include/` is at the very least checked over by a human. Files under `doc/` and `tools/` will
almost exclusively be AI-generated and not meant for human consumption.

Current progress:

|        | Game Code | Game Assets | Krawall |
| ------ | --------: | ----------: | ------: |
| **US** |    45-50% |       99.6% |      0% |
| **JP** |    45-50% |       99.6% |      0% |

Note that JP matching may run behind somewhat as it is not the primary focus.

Rough list of current priorities:

| Area                                                    | Reason                              |
| ------------------------------------------------------- | ----------------------------------- |
| Sources of RNG calls                                    | Improve RNG manipulation            |
| Find differences between international and Japanese ROM | Completeness, find patched bugs     |
| Improve understanding of save system                    | Completeness, entrypoint for ACE    |
| Document room scripts                                   | Better understand quest progression |

## Setup

The setup in this repo uses Linux tooling. If you use Windows, you can run these steps inside WSL.

1. Install the `nix` package manager. This will install the specific version of the tooling used.
2. Place the international and Japanese roms at `baserom.us.gba` and `baserom.jp.gba`.
3. Start a nix dev shell using `nix develop`. This may take a few minutes the first time.
4. Test whether the rom files are correct using `just setup`. This should show "OK" for both roms.
5. Extract assets using `just extract-all`.
6. Run the entire build process using `just check-all`.

The built ROMs should now be placed at `build/us/rom.gba` and `build/jp/rom.gba`.

## Attribution

This project was bootstrapped on knowledge found by jogotu and jlun2 from the Harry Potter Handheld Speedrunning
Discord server.

Harry Potter and the Prisoner of Azkaban for the Gameboy Advance (and by extension decompiled code in this repo) uses
code from open source libraries:

- `src/libc` contains code belonging to or based on the [newlib](https://sourceware.org/pub/newlib/) project. All code
  in this folder should be licensed under a BSD-like license.
- the [Krawall](https://github.com/sebknzl/krawall) audio engine, licensed under the LGPL v2.1 license
  - This code is currently not included in this repo, but may be in the future
- the [Pucrunch](https://a1bert.kapsi.fi/Dev/pucrunch/) compression tool, licensed under the LGPL v2.1 license. The code
  referenced was pulled from [the Internet Archive](http://web.archive.org/web/20060925155413id_/http://www.cs.tut.fi/~albert/Dev/pucrunch/pucrunch.c).
  - `tools/graphics/pucrunch_gammalz.py` implements parts of its compression algorithm

Most other code assets in this repo are based on the rom of Harry Potter and the Prisoner of Azkaban, as part of a clean
room reverse engineering effort. Raw art assets are currently not included in this repo.
