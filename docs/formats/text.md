# Dialog/UI text format

Status: **UNCONFIRMED / UNSOLVED**. This doc records what's been ruled out
and why, so future sessions don't re-run the same dead ends. No text has
been located yet.

## What we know

- **No plain ASCII dialog or UI text exists anywhere in the US ROM.**
  Checked exhaustively via `strings` (8-bit) and a UTF-16LE variant, plus
  targeted regex search for character/place names (`Harry`, `Ron`,
  `Hermione`, `Hogwarts`) and common UI words (`Save`, `Load`, `Options`,
  `Quidditch`, `Potion`, etc.). The *only* readable strings in the whole
  16MB ROM are:
  - The two already-extracted name tables (`asm/data/playable_character_names.us.s`,
    `asm/data/famous_wizard_card_names.us.s`).
  - A cluster of multiplayer/link-cable debug strings (`Error: Send
    Overrun`, `Error: Recv CRC`, etc., around `0x08060554`) and a build
    date stamp (`Apr  5 2004` near `0x0806bfc4`).
  - Two short UI/debug strings, `LEVEL PASSED!` and `YOU LOSE!`
    (`0x080693b0`).
  - None of the above are dialog or menu text (character select, item
    names, quest text, etc.) -- that's confirmed absent as plain ASCII.
- This is a US/EU multi-language cart (En,Fr,De,Es,It,Nl,Da in one ROM
  image -- see `CLAUDE.md`), which is the leading theory for *why* text
  isn't plain ASCII even in English: a common design for single-ROM
  multi-language GBA games is to encode text as indices into a **custom,
  per-language-swappable glyph/character table**, not literal ASCII
  codepoints. If true, even a correctly-located and correctly-decompressed
  text blob won't look like readable ASCII without also knowing the
  charmap -- printable-ASCII-ratio filtering is the wrong test to find it.

## Approaches tried and ruled out

### 1. Brute-force GBA BIOS compression header scan

Scanned every byte offset in the ROM for GBA BIOS compression headers
(LZ77 `0x10`, Huffman `0x20`, RLE `0x30` -- byte0 high nibble = type, next
3 bytes LE = decompressed size), with a *validated* decoder (rejects
out-of-bounds LZ backreferences / RLE overruns / Huffman bitstream
overruns) so false structural matches are discarded, not just false
header-byte matches.

Filtered for >60% printable-ASCII output: all resulting matches sat inside
Krawall's PCM audio-sample region (`0x08A9C6D0`-`0x08D3EFFC`, see
`regions.us.txt`) or 4bpp graphics tile data -- coincidental byte-value
runs (audio silence ramps, repeated tile nibbles), not real compressed
streams. **Ruled out as a source of dialog text under an ASCII
assumption.**

### 2. Huffman scan without ASCII filter (charmap-agnostic)

Redid the Huffman decode (GBA BIOS `HuffUnComp` format: tree-size byte,
binary tree of 8-bit nodes with end-flags in bits 6/7 and 6-bit child
offsets, bitstream consumed 32-bits-at-a-time MSB-first) filtering
instead for "natural-language shape" regardless of byte value: one
dominant byte at plausible "space" frequency (5-40%) with regular
word-length gaps, byte-value diversity (20-110 distinct values), entropy
3.0-5.5 bits/symbol.

~6580 structurally-valid decodes found across the ROM; the ~40 that also
passed the shape filter were all false positives sitting in 4bpp
graphics-tile or audio-adjacent regions -- a Huffman tree built from
essentially-random binary data can still produce output that passes loose
statistical shape tests, over a 16MB haystack. **This filter is too weak
to be useful on its own; not pursued further.**

### 3. Sliding-window entropy/frequency scan

16KB windows scanned for "text-shaped" regions (30-140 distinct byte
values, one dominant byte at 8-35% frequency, entropy 3-5.5 bits).
Found only 4bpp graphics tiles (most likely font glyph bitmaps -- see
`0x08937000`-`0x0896b000`, dominant nibble `0x33`, structurally
tile-shaped on inspection) and null-padding regions. **No text found.**

### 4. Pointer-table hunting

Scanned all 4-byte-aligned words for runs of >=8-16 valid ROM pointers
(`0x08000000`-`0x08FFFFFF`) with small monotonic deltas (a classic
string-table signature: consecutive offsets into a blob, delta ==
previous string's length). Every high-confidence run found resolves to
targets clustered within a few hundred bytes of the table itself --
these are Thumb `switch` jump tables in code (confirmed by dumping
targets: valid Thumb instruction bytes, not text), not a language-block
string table. No candidate resembled "7 parallel per-language tables" or
"array of 7-pointer-per-string structs." **No text-table pointer array
found by this method.**

One incidental find: `0x0800BBEC` contains a direct literal-pool pointer
to `sFamousWizardCardNames` (`0x0804CEC4`), confirming ordinary
armcc-style PC-relative literal-pool references are how code reaches
known data -- a viable pattern to search for elsewhere, but not itself a
new lead.

### 5. Font/glyph-width table search

Attempted to find a byte-indexed glyph-width table (typical VWF renderer
support data: 256ish bytes, mostly small values 1-8) near the candidate
font tile graphics from approach 3. Swamped by false positives: any 4bpp
graphics tile block trivially satisfies "values 0-15, moderate distinct
count" (GBA tile pixel nibbles are 0-15 by construction). **Needs a
tighter, tile-structure-aware exclusion filter to be useful; not
resolved.**

### 6. Resource-decompression dispatcher call-site tracing

Found the game's generic resource-decompression dispatcher,
`sub_0801DD90` (`0x0801DD88`, with a near-twin `sub_0801DE5C`). It reads
a 32-bit header word and jump-tables on `(byte0>>4) & 0x7` -- **PROVEN**,
re-derived directly from the actual instructions (a paraphrase in an
earlier version of this doc said "low byte's high nibble", which is
imprecise: bit 3 of that nibble, i.e. `byte0 & 0x80`, is a *separate*
post-processing flag checked later, not part of the type selector --
see `docs/formats/graphics.md`'s "Compression: the level-resource
table" section for the exact instruction sequence). Dispatch:

- type 0: raw `CpuSet` copy (uncompressed)
- type 1: `svc 0x11` (BIOS `LZ77UnCompWram`)
- type 2: `svc 0x13` (BIOS `HuffUnComp`)
- type 3: `svc 0x14` (BIOS `RLUnCompWram`)
- type 4 and 6: a **custom, non-BIOS decompressor**, installed into IWRAM
  at runtime by a function at `0x0801DD40` (not statically reachable by
  `gbadisasm`'s function discovery -- same invisibility issue as
  `kramInstall`, see `docs/memory-map/krawall.md`). Two `CpuSet` (`svc
  0xB`) copies install:
  - type 4's codec from `0x08006108` (504 bytes) to IWRAM `0x030028D4`,
    pointer stashed at `0x030028CC`: a byte-token LZSS-style decoder
    (bit7-set token byte = back-reference with 5-bit length + distance
    byte; bit7-clear = literal-run control).
  - type 6's codec from `0x080005EC` (828 bytes) to IWRAM `0x03002ACC`,
    pointer stashed at `0x030028D0`: a canonical-Huffman-shaped bitstream
    reader (shift-with-carry / word-reload pattern, code-length-like
    header table). **Update**: this codec has since been fully decoded
    (PROVEN, verified by executing the real ROM bytes in an emulator) --
    see `docs/formats/graphics.md`'s "The type-6 codec, decoded"
    section for the algorithm and a working decoder. Every real resource
    decoded with it so far has turned out to be BG tilemap data, not
    text -- but the decoder itself is generic and could decode a text
    resource too, if/when one is found using this compression type.

Both are real, previously-undocumented proprietary compressors -- **but
every one of the dispatcher's 14 static call sites traces to the
level/graphics-loading subsystem** (a 124-byte-stride room/level table at
`0x0806BE38`), not text. `sub_0804A2CC`, which looked promising as a
custom decompressor by name proximity, is actually an unrelated shared
register-indirect-call trampoline (`bx r3`) -- the same interworking-veneer
pattern documented in `docs/memory-map/krawall.md`, reused generically.

**Open door, not closed**: a text-loading caller could still exist
elsewhere in the ~1.1M-line disassembly, reaching either of these two
custom IWRAM codecs (or the BIOS Huffman path) through a call site the
`bl sub_0801DD90` / `bl sub_0801DE5C` grep didn't catch (e.g. a dedicated
text-specific wrapper that was never routed through this dispatcher at
all).

## Recommended next step (not yet attempted)

Static/statistical scanning is exhausted as a productive approach at this
ROM's scale -- everything found so far is graphics or audio coincidentally
matching the filters used. The next step needs **dynamic analysis**:
trace the actual VWF (variable-width font) text-drawing routine at
runtime (e.g. break on writes to the relevant BG tilemap/charblock VRAM
region during a dialog-heavy scene, such as the character-select screen,
whose plaintext name-table addresses are already known and could anchor
where in the scene graph to look) and walk backward from there to find
the real text-loading code path and its data source.

Note: `CLAUDE.md` records that dynamic verification via mGBA's `--gdb`
stub was already attempted for Krawall function identification and was
inconclusive (unreliable breakpoint/continue sequencing, root cause never
identified) -- worth keeping in mind before repeating that exact
approach for text; a different dynamic-analysis technique (e.g. memory
watchpoints on VRAM instead of code breakpoints, or a scripted Lua/Python
harness instead of manual gdb stepping) may be needed.

## Open questions

- [ ] Is text compressed at all, or just charmap-encoded (uncompressed,
      just non-ASCII byte values)? Nothing here distinguishes these
      cases -- both would look identical to every scan attempted.
- [ ] Does the custom charmap (if it exists) differ per language, or is
      it one shared table with per-language font tiles only?
- [ ] Is the type-4/type-6 custom IWRAM codec pair used *anywhere*
      outside the level-loading dispatcher's 14 known call sites? Not
      fully ruled out -- only the statically-traceable dispatcher call
      sites were checked.
- [ ] Where is the font glyph table, definitively? The `0x08937000`-
      `0x0896b000` region is tile-shaped and a plausible font candidate
      but not confirmed (no code cross-reference found pointing directly
      at it -- see approach 5).
