<!--
This file is *not* to be edited by AI agents, it may only be edited by humans.
If changed need to be made to this file, it should be proposed to a human so they can choose what and how to edit it.
--->

# hp3-gba-decomp

This repo holds a heavily AI-assisted decompilation of Harry Potter and the Prisoner of Azkaban for the Gameboy Advance.

The goal of this project is to both explore automated reverse engineering, and to look into a game I've loved as a
child. A very far-off stretch goal is to make a shiftable build allowing for modding, but this seems very unlikely and
expensive. A more realistic goal is to extract assets and some of the code into a form that perfectly reproduces part of
the ROM. Minor mods can be made by appending modified data to the end of the ROM.

Note that while this project contains mostly AI-generated assets, this README is and will always be written by a human.
All code under `src/` and `include/` is at the very least checked over by a human. Files under `doc/` and `tools/` will
almost exclusively be AI-generated and not meant for human consumption.

Currently, between 15% to 20% of the game's code has been decompiled.

## Setup

To be documented. See `flake.nix` and `Justfile`.

TL;DR: place your roms at `rom.us.gba` and `rom.jp.gba`, start a dev shell with `nix develop` (this will build/fetch
required tools) and run `just check-all` to execute the entire extraction and build process.

## Attribution

This project was bootstrapped on knowledge found by jogotu and jlun2 from the Harry Potter Handheld Speedrunning
Discord server.

Harry Potter and the Prisoner of Azkaban for the Gameboy Advance (and by extension decompiled code in this repo) uses
code from open source libraries:
- `src/libc` contains code belonging to or based on the [newlib](https://sourceware.org/pub/newlib/) project. All code
in this folder should be licensed under a BSD-like license.
- the [Krawall](https://github.com/sebknzl/krawall) audio engine, licensed under the LGPL v2.1 license
  - This code is currently not included in this repo, but may be in the future

Most other code assets in this repo are based on the rom of Harry Potter and the Prisoner of Azkaban, as part of a clean
room reverse engineering effort. Raw art assets are currently not included in this repo.
