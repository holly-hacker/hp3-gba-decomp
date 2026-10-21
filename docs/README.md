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

- [`formats/graphics.md`](formats/graphics.md) — the codecs and their
  encoders (GammaLz is Pucrunch 1.11), the graphics build format, and PNG
  sprite images. Pipeline: `tools/graphics/`, `data/graphics/`.
- [`formats/krawall.md`](formats/krawall.md) — how the Krawall music data
  is laid out in ROM, and its JSON/WAV source. Pipeline: `tools/krawall/`,
  `data/audio/`.
- [`formats/room_graphics.md`](formats/room_graphics.md) — the 14 resources per
  room and their editable source. Tools: `tools/room_graphics/`.
- [`formats/graphic_blob.md`](formats/graphic_blob.md) — what the graphic blobs
  hold (battle and effect backgrounds, rain tiles) and their extraction.
- [`formats/special_scene_frames.md`](formats/special_scene_frames.md) — the train
  window scenery frames and how to view them.
- [`formats/fonts.md`](formats/fonts.md) — the text fonts and their glyph
  atlases.
- [`formats/text.md`](formats/text.md) — the dialog string tables and how
  the charmap was derived. Pipeline: `tools/text/`, `data/text/`.

## Conventions

- One owner per fact. Where two subsystems touch the same table or
  struct, the document that traced the *reader* owns the semantics and
  the other links to it rather than restating them.
- Document a format here before writing its extractor
  (`AGENTS.md`, Assets).
- Cross-document links are relative (`../formats/text.md`), and a
  reference to another document's section names that section in quotes.
