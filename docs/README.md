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

Memory map (live RAM layout and the code that drives it):

- [`memory-map/battle.md`](memory-map/battle.md) — `BattleFighter`,
  `MonsterTable`→fighter field correspondence, turn order, the melee and
  spell damage formulas, the `bStatusFlags` status-effect system and all
  29 `StatusEffect` sub-cases, spell tables and familiarity/leveling,
  and the per-character level-up stat tables.
- [`memory-map/battle-ui.md`](memory-map/battle-ui.md) — the battle
  menu tree (`FightState`'s menu state machine, every screen's confirm
  handler), `ShowBattleMessage`'s case→dialog-text table, Harry's 16
  Folio Universitas cards, and Hermione's/Ron's Special Moves.
- [`memory-map/krawall.md`](memory-map/krawall.md) — the Krawall audio
  engine: locating it in the ROM, the mixer/effect-handler driver code,
  the `MixChannel`/effect-state struct fields, and the IWRAM/EWRAM
  install mechanism.
- [`memory-map/rng.md`](memory-map/rng.md) — the MT19937 PRNG function
  cluster, its two independent draw cursors, and the bounded-random
  helpers gameplay code rolls against.

Data formats (each with its `data/` extraction pipeline, where one exists):

- [`formats/folio_bruti.md`](formats/folio_bruti.md) — `MonsterTable`,
  the 24-byte monster stat record, per-spell effectiveness, and the
  bestiary grid. Pipeline: `tools/monsters/`, `data/monsters/`.
- [`formats/graphics.md`](formats/graphics.md) — the generic
  resource-decompression dispatcher and its four codecs, the room
  resource table, OBJ palette and tile loading. No pipeline yet.
- [`formats/items.md`](formats/items.md) — `g_pItemTable`, the item
  record layout, equipment stats, per-character equip eligibility, and
  categories. Pipeline: `tools/items/`, `data/items/`.
- [`formats/krawall.md`](formats/krawall.md) — the Krawall module /
  pattern / sample on-ROM structs. Pipeline: `tools/krawall/`,
  `data/audio/`.
- [`formats/object_script.md`](formats/object_script.md) — the
  per-`Object` behavior-script bytecode VM, its opcode table, and the
  effect-script pointer table. Pipeline: `tools/objscript/`,
  `data/scripts/`.
- [`formats/save.md`](formats/save.md) — the EEPROM transport, save
  region layout, checksums, and the save-slot serialization stream.
  Tool: `tools/save/parse_save.py`.
- [`formats/text.md`](formats/text.md) — the 8-language dialog/UI string
  table, its Huffman scheme, the charmap, and the VWF text engine.
  Pipeline: `tools/text/`, `data/text/`.

The per-character level-up stat tables (pipeline: `tools/levels/`,
`data/levels/`) have no `formats/` document of their own yet; their
record layout is in [`memory-map/battle.md`](memory-map/battle.md)'s
`bLevel` section and in `tools/levels/level_codec.py`.

## Conventions

- One owner per fact. Where two subsystems touch the same table or
  struct, the document that traced the *reader* owns the semantics and
  the other links to it rather than restating them.
- Document a format here before writing its extractor
  (`CLAUDE.md`, Conventions).
- Cross-document links are relative (`../formats/text.md`), and a
  reference to another document's section names that section in quotes.
