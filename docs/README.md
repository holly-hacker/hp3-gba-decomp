# Documentation index

Reverse-engineering findings for the *Harry Potter and the Prisoner of
Azkaban* (GBA) decompilation. Addresses are US-ROM (`baserom.us.gba`)
unless a document says otherwise; see each document's own JP note.

## Confidence key

Every finding in these documents is marked:

- **PROVEN** — directly verifiable fact (string bytes, instruction bytes,
  cross-referenced addresses, a byte-exact round-trip, a live debugger
  observation). Re-running the same check reproduces it.
- **STRUCTURAL MATCH** — behavior/shape observed in disassembly matches a
  documented convention or reference source closely, but is not confirmed
  against exact source, so the specific name is a working label rather
  than a proven identity.
- **UNCONFIRMED** — plausible but with no independent corroboration found
  yet; flagged explicitly so it doesn't get mistaken for something
  stronger.

Names carrying a `_candidate` suffix are at STRUCTURAL MATCH or weaker;
dropping the suffix is what promoting an identification to PROVEN looks
like in `functions.<ver>.cfg` and in Ghidra.

## Documents

Engine and toolchain:

- [`compiler.md`](compiler.md) — the toolchain: GCC `2.9-arm-000512`
  (agbcc) + binutils + newlib, the byte-exact libgcc/libc block that
  proves it, and the flags each half of the ROM was built with.
- [`c.md`](c.md) — writing C: the pipeline, what agbcc accepts, the
  constraints that affect matching, and `just diff-region`.

Other:

- [`link_peers.md`](link_peers.md) — what a modified game on the other end
  of a card-trade or GameCube link can do.

Data formats (each with its `data/` extraction pipeline, where one exists):

- [`formats/folio_bruti.md`](formats/folio_bruti.md) — `MonsterTable`,
  the 24-byte monster stat record, per-spell effectiveness, and the
  bestiary grid. Table lives as committed C in `src/combat_fighter/monsters.c`.
- [`formats/graphics.md`](formats/graphics.md) — the generic
  resource-decompression dispatchers and codec inventory, the room
  resource table, OBJ palette and tile loading, PNG sprite banks, and actor
  animation command streams. Pipeline: `tools/graphics/`, `data/graphics/`.
- [`formats/items.md`](formats/items.md) — `g_pItemTable`, the item
  record layout, equipment stats, per-character equip eligibility, and
  categories. Committed as `src/items/items.c`; icons are the `ItemIcons`
  image bank in `data/graphics/menus/`.
- [`formats/krawall.md`](formats/krawall.md) — the Krawall module /
  pattern / sample on-ROM structs. Pipeline: `tools/krawall/`,
  `data/audio/`.
- [`formats/battle_scripts.md`](formats/battle_scripts.md) — the
  battle-script bytecode VM, its opcode table, and the effect-script
  pointer table. Scripts are C: `src/combat_fx/effect_scripts/`, `include/combat_fx.h`.
- [`formats/room_scripts.md`](formats/room_scripts.md) — the room-script
  bytecode VM (a second, unrelated interpreter): its byte format,
  pause/resume/nested-call state machine, and known opcodes. Scripts are
  Assembly: `asm/room/blobs/`, `asm/room_script.inc`; opcode numbers in
  `include/overworld/room_script_bytecode.h`.
- [`formats/room_graphics.md`](formats/room_graphics.md) — the 14 resources per
  room (maps, blocks, collision, tilesets, palettes): ROM layout, tileset codec,
  and how they are extracted and built. Tools: `tools/room_graphics/`.
- [`formats/graphic_blob.md`](formats/graphic_blob.md) — the palette, tilemap
  and tile-stream blob loaded by `LoadGraphicBlobTiles`; battle backgrounds use it.
- [`formats/special_scene_frames.md`](formats/special_scene_frames.md) — the 128 raw
  tile frames and animation tables of the special scene effect.
- [`formats/fonts.md`](formats/fonts.md) — the ten 2 bpp text fonts, their
  header and bitmap layout, and how they are selected.
- [`formats/help_pages.md`](formats/help_pages.md) — the Help / HelpTopicScreen
  page scripts: opcode format, the 91 pages and their menus, and the engine state.
- [`formats/save.md`](formats/save.md) — the EEPROM transport, save
  region layout, checksums, and the save-slot serialization stream.
  Tool: `tools/save/parse_save.py`.
- [`formats/text.md`](formats/text.md) — the 8-language dialog/UI string
  table, its Huffman scheme, the charmap, and the VWF text engine.
  Pipeline: `tools/text/`, `data/text/`.

## Conventions

- One owner per fact. Where two subsystems touch the same table or
  struct, the document that traced the *reader* owns the semantics and
  the other links to it rather than restating them.
- Document a format here before writing its extractor
  (`AGENTS.md`, Assets).
- Cross-document links are relative (`../formats/text.md`), and a
  reference to another document's section names that section in quotes.
