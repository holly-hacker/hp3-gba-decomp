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
- [`c.md`](c.md) — adding a `c-file` region: the pipeline, what agbcc
  accepts, the constraints that affect matching, and `just diff-region`
  for iterating on one that doesn't.

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
- [`memory-map/heap.md`](memory-map/heap.md) — the heap allocator
  (`MemPool`/`MemBlock`, first-fit alloc/free) and the object pool built
  on top of it; the two ARM-mode object-list functions and why they're
  blocked on the toolchain, not on matching difficulty.
- [`memory-map/krawall.md`](memory-map/krawall.md) — the Krawall audio
  engine: locating it in the ROM, the mixer/effect-handler driver code,
  the `MixChannel`/effect-state struct fields, and the IWRAM/EWRAM
  install mechanism.
- [`memory-map/rng.md`](memory-map/rng.md) — the MT19937 PRNG function
  cluster, its two independent draw cursors, and the bounded-random
  helpers gameplay code rolls against.
- [`memory-map/input.md`](memory-map/input.md) — controller input:
  `UpdateKeyInput`/`ResetKeyInput`, the held/pressed/released key masks
  and their standard GBA `KEYINPUT` bit layout, and the serial-link
  per-player input path.
- [`memory-map/scanline_effects.md`](memory-map/scanline_effects.md) — the
  VCount-interrupt callback list: entry format, live/staging tables, and the
  `InitScanlineEffects`/`QueueScanlineEffectTable`/`CommitScanlineEffects` API.
- [`memory-map/frame_systems.md`](memory-map/frame_systems.md) — the
  per-frame `TickFrameSystems` sequence and the BG-layer, window, palette
  and tile-animation ticks it runs.
- [`memory-map/link.md`](memory-map/link.md) — the link-cable layer
  (multiplayer SIO, Timer3 ISR pump, handshake) and the card-trade
  session (mode `0x15`, `CardTradeState`, offer/lock/compare/commit).
- [`memory-map/gcn-link.md`](memory-map/gcn-link.md) — the GameCube link
  (JOYBUS slave for owl races, mode `0x41`, `JoybusLinkState`, wire
  protocol and link commands).

Data formats (each with its `data/` extraction pipeline, where one exists):

- [`formats/folio_bruti.md`](formats/folio_bruti.md) — `MonsterTable`,
  the 24-byte monster stat record, per-spell effectiveness, and the
  bestiary grid. Table lives as committed C in `src/data/monsters.c`.
- [`formats/graphics.md`](formats/graphics.md) — the generic
  resource-decompression dispatchers and codec inventory, the room
  resource table, OBJ palette and tile loading, and PNG sprite banks.
  Pipeline: `tools/images/`, `data/images/`.
- [`formats/items.md`](formats/items.md) — `g_pItemTable`, the item
  record layout, equipment stats, per-character equip eligibility, and
  categories. Committed as `src/data/items.c`; icons are an image bank in
  `data/images/items/`.
- [`formats/krawall.md`](formats/krawall.md) — the Krawall module /
  pattern / sample on-ROM structs. Pipeline: `tools/krawall/`,
  `data/audio/`.
- [`formats/battle_scripts.md`](formats/battle_scripts.md) — the
  battle-script bytecode VM, its opcode table, and the effect-script
  pointer table. Pipeline: `tools/battle_scripts/`, `data/battle_scripts/`.
- [`formats/room_scripts.md`](formats/room_scripts.md) — the room-script
  bytecode VM (a second, unrelated interpreter): its byte format,
  pause/resume/nested-call state machine, and known opcodes. Dump only
  (no pack yet): `tools/room_scripts/`, `extracted/room_scripts/`.
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
  (`AGENTS.md`, Assets).
- Cross-document links are relative (`../formats/text.md`), and a
  reference to another document's section names that section in quotes.
