# Dialog/UI text format

Status: **SOLVED end-to-end, PROVEN by direct content verification.** The
real dialog/UI string table is located, its Huffman-style compression
format is fully decoded, and it is confirmed genuinely per-language (all
8 languages, not the previously-assumed 7 -- see `CLAUDE.md`): decoding
the same string ID from each of the 8 language blobs produces distinct,
correct, grammatical text in the right language every time. Found by
static tracing alone, starting from a real, already-known ASCII string
table -- the dynamic-analysis approach previously recommended here was
never needed. See "The real dialog string table, decoded" below for the
full derivation, and `tools/decode_dialog_text.py` for a working
decoder. The VWF text-*rendering* engine (glyph draw/word-wrap) was
found first, as the path that led here -- see "The text engine, found".
The full charmap (every code any real string actually uses, across all
8 languages, including several repurposed printable-ASCII positions) is
also decoded -- see "The extended charmap, decoded". A curated,
build-integrated extraction pipeline exists too -- see "The extraction
pipeline, built and build-integrated". Remaining gaps (the macro/escape
code system, the font-descriptor per-language question) are listed
under "What's NOT yet known".

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
- This is a US/EU multi-language cart (English US, English UK, French,
  German, Spanish, Italian, Dutch, Danish -- 8 languages in one ROM image,
  see `CLAUDE.md`), which is the leading theory for *why* text isn't
  plain ASCII even in English: a common design for single-ROM
  multi-language GBA games is to encode text as indices into a **custom,
  per-language-swappable glyph/character table**, not literal ASCII
  codepoints. If true, even a correctly-located and correctly-decompressed
  text blob won't look like readable ASCII without also knowing the
  charmap -- printable-ASCII-ratio filtering is the wrong test to find it.
  **Update**: the "indices into a swappable table" half of this is now
  PROVEN (see "The text engine, found" below) -- glyph codes are looked
  up through a RAM-resident font-descriptor pointer, not a fixed ROM
  table. The "per-language" half is still unconfirmed -- the pointer
  being RAM-resident doesn't by itself prove it changes per language;
  see that section's "What this actually proves, and what it doesn't."

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

## The text engine, found (PROVEN for the encoding scheme; static tracing, no live session)

Superseded the "dynamic analysis only" conclusion above: static tracing
*forward* from the one piece of ground truth this doc already had (a
real ASCII string genuinely read by code, not just present in the ROM)
led directly to the VWF engine, without needing mGBA at all.

**Anchor**: of the two known plaintext tables, `sFamousWizardCardNames`
(`0x0804CEC4`) is actually read by code -- `0x0800BBEC` in
`build/us/full_disasm.s` loads it, computes a 32-byte-stride entry index
from a counter at `0x03002238+4`, and calls
`sub_08020FF8(len=0x1a0, entry_ptr, 1, x=0x78, y=0x10, attr=0xe0)`.
(`sPlayableCharacterNames` at `0x0804C4F6`, by contrast, has **zero**
literal-pool references anywhere in the disassembly -- likely dead/debug
data, not a useful anchor.)

**`sub_08020FF8`** (`0x08020FF8`): word-wraps and dispatches per
character -- loops `ldrb r0,[str]`, calls `sub_08020714` once per
iteration, stops on a null byte. This is the string-consuming outer
loop of a real text renderer.

**`sub_08020714`** (`0x08020714`): the actual per-glyph decode loop.
Reads one byte at a time and branches on its value:

- `byte == 0x40`: **escape/macro prefix**. The next byte (`code - 0x31`,
  `*4`) indexes a table of pointers at `0x03003170` (RAM -- runtime
  content, not yet traced to its ROM source) to a macro/format string,
  which is itself walked char-by-char and recursed into (nested escapes
  inside a macro are handled: same `0x40` check, same `0xef`-threshold
  glyph split, calling `sub_08020E40`/`sub_0802136C` for width). Plausibly
  something like "insert player name" / inline icon / color-code macros
  -- not yet individually decoded.
- `byte <= 0xef`: **direct single-byte glyph code** -- looked up via
  `[0x03003110]` (a RAM pointer to a "font descriptor", see below).
- `byte > 0xef`: **two-byte glyph code** -- combined as `(byte0<<8)|byte1`
  and looked up via `[0x03003110 + 4]` (a *second*, distinct font
  descriptor pointer -- presumably an extended-character-set table for
  accented/non-Latin glyphs the 8-language cast needs, e.g. `é`, `ü`,
  `ñ`, `å`; not yet decoded).
- `byte == 0x20` (space) or `byte == 0xf0` followed by `0x00`: marks the
  current position as a valid word-wrap break point (`sb` register).
- `byte == 0x2d` (`-`, hyphen): also a wrap-break candidate, conditional
  on whether the line width budget (`sl`, the caller's `len` arg) is
  already exceeded.

**`sub_0802136C`** (`0x0802136C`): the glyph-width lookup, called with
`(fontDescriptor, glyphCode)`. Font descriptor struct (partial, offsets
confirmed by this function's field accesses):

```
+0x00      ? (unused by this function)
+0x02  u16 firstCode   -- first glyph code this font covers
+0x04  u16 lastCode    -- (last_code, from range check: codeRange = lastCode - firstCode)
+0x0c  u32 widthTable  -- pointer to a byte-per-glyph width array, widthTable[glyphCode-firstCode]
```

If `glyphCode` falls outside `[firstCode, lastCode]`, returns
`widthTable[1]` instead (a "missing glyph"/fallback width) --
`widthTable[0]` is presumably the default/space width by the same
convention. This is a genuine variable-width-font width table, not
guessed: the arithmetic (`glyphCode - firstCode`, bounds-checked against
`lastCode - firstCode`, byte-indexed) is exactly the shape of a classic
VWF glyph-width lookup.

**What this actually proves, and what it doesn't**: `0x03003110`/
`0x03003110+4` are RAM pointers to (at least) two font descriptors,
populated at runtime rather than being fixed ROM literals -- that part
is PROVEN, directly from the load-through-pointer instructions. The
split itself (`<=0xef` vs `>0xef`) is a base-charset/extended-charset
split, not necessarily a language split -- plausibly the extended range
covers accented characters (needed by French/German/Spanish/etc, not by
English). **What is NOT proven**: that these pointers actually change
value per selected language. That's still just the doc's original
theory, unverified -- a single shared table covering the union of every
glyph any of the 8 languages needs would fit everything observed so far
equally well, with no swapping at all. Confirming an actual per-language
swap would need watching `0x03003110` change value across a language
setting, or finding the write site(s) that set it and seeing whether
they're conditioned on a language variable -- neither done yet. The
`0x080205F8` dispatch table below is a separate, likewise-unconfirmed
candidate for where such switching might happen, not corroboration of
this one.

The actual glyph *codes* used by ASCII debug strings like
`"Muggle Harry"` pass straight through as their raw byte values (`'M'` =
`0x4D` <= `0xef`, single-byte path) -- meaning **for values in this
range, the charmap for English text at this call site is plain ASCII**,
just routed through a font-descriptor indirection rather than a fixed
table. Whether this holds for real dialog text (as opposed to this one
debug/UI string) is not yet confirmed.

**A likely per-language dispatch table, found but not fully decoded**:
an unlabeled Thumb code blob at `0x080205F8` (no seed in
`functions.us.cfg` -- `gbadisasm` never split it out, same
undetected-function issue noted elsewhere in this repo) contains a
`byte-field -> mov pc,r0` computed jump: reads a byte at
`structPtr+0x8D`, and if `<= 5`, indexes a 6-entry function-pointer
table at `0x08020610` (`{0x08020614, 0x08020660, 0x0802062C, 0x08020660,
0x08020642, 0x08020636}` -- entries 1 and 3 are identical, so only 5
distinct handler addresses). Two of the handlers (`0x0802062C`,
`0x08020642`/`0x0802064C`) call out to other unlabeled functions
(`0x080203F0`, `0x08001E7C`, `0x0802042C`) passing two `u16` values read
from `structPtr+0x2e`/`+0x32` -- plausibly per-language font/layout
parameters, but not traced further. **Only 6 dispatch values for 8
languages is a mismatch worth resolving** -- either this dispatches on
something coarser than language ID (e.g. a font *family* shared by
several languages, English US/UK plausibly sharing one), or this isn't
the language-select table at all and the resemblance is coincidental.
Not yet confirmed either way -- flagged STRUCTURAL MATCH, not PROVEN.

**Tools used**: no new script -- this was direct reading of
`build/us/full_disasm.s` plus one-off `capstone` disassembly (Thumb
mode) of the unlabeled blob via a short inline Python snippet (not
checked in; trivial to redo: `capstone.Cs(CS_ARCH_ARM, CS_MODE_THUMB)`
over `baserom.us.gba` bytes at the target address).

## The real dialog string table, decoded (PROVEN -- full round-trip against real content)

Continuing from the two open threads above (`sub_08020FF8`'s other
callers, and what actually reaches the codec dispatchers), grepping for
all callers of `sub_08020FF8` (not just the one wizard-card-name site)
found the real mechanism.

**Every other caller** (`build/us/full_disasm.s` lines ~39482, 53976,
53993, 54637, 54680, 56486, 57079, 57120) passes a string pointer that
is the **return value of `bl sub_080425E4`**, called with a small
integer argument (`0x412`, `0x4A2`, `0x4E6`, `0x592`, `0x478`, `0x12D`,
`0x90C`, ...) -- the shape of a string-ID lookup, not a literal ROM
pointer. This is the real text-loading path; the wizard-card-name call
site (direct literal-table pointer) turns out to be the outlier, not
representative of how dialog/UI text works.

**`sub_080425E4(id)`** (`0x080425E4`): loads `r1 = [0x03005D08]` (a RAM
pointer to a fixed 0x400-byte output buffer) and calls
`sub_08024DC8(id, r1, 0x400)`; returns that buffer pointer on success,
`NULL` on failure. A thin wrapper -- the real work is in
`sub_08024DC8`.

**`sub_08024DC8(id, outBuf, maxSize)`** (`0x08024DC8`): a **Huffman-style
bitstream decompressor**, decoding directly into `outBuf` up to
`maxSize` bytes, terminating on a decoded `0x00` byte (matching the
`0x40` recursion in `sub_08020714`'s string-length role -- ordinary
C-string semantics). Reads three RAM globals as its working state:

- `0x030033C0`: base pointer of the current language's compressed blob.
- `0x030033C4`: pointer to a `u32[]` offset table, indexed by `id`;
  `offsetTable[id]` is a byte offset from the blob base to that string's
  compressed bitstream.
- `0x030033C8`: pointer to the Huffman tree's node table.

Tree walk, precisely as implemented (each node is 4 bytes: `u16
zeroChild @+0`, `u16 oneChild @+2`): starting at node `0x100`, each
input bit selects a child; a child value `<= 0xFF` is a decoded output
byte (leaf), `> 0xFF` is the next node's index, computed as `treeBase +
(child - 0x100) * 4`. Bits are read LSB-first out of each input byte,
refilling one byte at a time. This is a from-scratch project-specific
scheme (not GBA BIOS Huffman, which is bit-tree-shaped differently and
already ruled out for this content in approach 2 above) -- reimplemented
directly from the disassembly, not guessed.

Decoded bytes above `0xEF` are handled with the same 2-byte-glyph
pairing logic seen in `sub_08020714` (a byte `>0xEF` starts a pending
extended code, the next decoded byte completes it) -- the Huffman
decoder's output is literally the same glyph-code byte stream the
renderer consumes, confirming these are the same charmap/encoding on
both ends, not two independent systems that happen to share a threshold.

**`sub_08024EB8(blobBase)`** (`0x08024EB8`): the init function that
populates the three globals above from a single base pointer:
`0x030033C0 = blobBase`; `0x030033C8 = blobBase + 4` (tree table starts
right after a 4-byte header); `0x030033C4 = blobBase +
*(u32*)blobBase` (the header word is the byte offset, from the blob
base, to the per-string offset table). So each language blob's layout
is: `[u32 header][Huffman tree][per-string u32 offset table][compressed
bitstreams]`.

**`sub_08042588(langId)`** (`0x08042588`): the language-select entry
point, and the final piece -- **PROVEN, resolves the doc's original
"is the charmap per-language" open question for real**:

```
0x03005D0C = langId                                  // stored current language
blobBase = *(u32*)(0x0806BD78 + langId * 4)           // per-language ROM pointer table
sub_08024EB8(blobBase)                                // switch the active string blob
```

`0x0806BD78` was read directly: **exactly 8 valid ROM pointers**
(`0x08EAC798, 0x08EBFE84, 0x08ED3574, 0x08EE88CC, 0x08EFC504,
0x08F0FB84, 0x08F24704, 0x08F37D1C`), followed by non-pointer garbage at
index 8 -- matching the cart's 8 languages exactly (not 7; corrected in
`CLAUDE.md`: English US, English UK, French, German, Spanish, Italian,
Dutch, Danish). Decoding the same string IDs from each of the 8 blobs
produces genuinely distinct, real, grammatically correct text in what
reads as the right language for each slot in order -- e.g. id `0x12D`:
English "The Gryffindor common room is on the seventh floor. Just like
last year.", French "La salle commune de Gryffondor est au 7e étage,
comme l'an dernier.", German "Der Gryffindor-Gemeinschaftsraum ist im 7.
Stock, genau wie letztes Jahr.", and so on through all 8 -- this is
about as strong a confirmation as static analysis can give without
running the game.

(The rest of `sub_08042588`, not text-related: sets `0x03005D0D` to a
locale-specific thousands-separator byte -- `' '` for French, `'.'` for
Italian/Dutch, `','` otherwise -- ordinary number-formatting
localization, unrelated to the glyph charmap.)

**`tools/decode_dialog_text.py`** (new, checked into the repo):
reimplements this whole chain (language table lookup, blob init, tree
walk) directly in Python from the ROM, verified byte-for-byte against
manual disassembly tracing for several IDs across all 8 languages.
Usage: `decode_dialog_text.py us <lang 0-7> <string id>`. Note this
decodes *content* (real dialog/UI text) -- per `CLAUDE.md` hard rule 2,
that content itself must never be committed to the repo (same footing as
Krawall audio); only the format knowledge and this decoder tool are
committed.

**String ID scale**: scanning the English (lang 0) offset table for
sequentially-valid entries found **2767 entries** (IDs `0`-`0xACE`) --
matching a `cmp r?, #0xACF` boundary check seen near one of the
`sub_08020FF8` call sites, an independent cross-check that this is the
real, complete string count, not an arbitrary scan cutoff.

## The extraction pipeline, built and build-integrated (PROVEN -- full-ROM byte-exact)

Mirrors Krawall's `data/audio/` + `tools/pack_krawall.py` model (see
`CLAUDE.md`): curated, editable, gitignored source that a pack step
turns into byte-exact assembly before `stitch`, verified by the same
`just compare`/`just check-all` full-ROM sha1 oracle every other region
already has to pass.

**`tools/text_codec.py`**: the shared codec. Beyond decode (see above),
it implements a real **encoder**, which needed one non-obvious fix to
get byte-exact: the tree contains structurally-reachable **duplicate
leaves** (the same output byte reachable via more than one bit path) --
confirmed real, not a decode bug, by walking the tree naively (raised on
the very first duplicate, e.g. byte `0x65` = `'e'`). Re-deriving the
encode table *empirically* from real decode traces (capturing the exact
bit path each symbol actually used, across every string in a language)
instead of a structural tree walk found **zero path conflicts** across
all 8 languages' full string sets -- i.e. each symbol has exactly one
real path in practice, just not a structurally-unique one, so an
encoder has to learn it from data rather than the tree alone. See
`build_encode_map_from_corpus()`'s docstring.

Also empirically confirmed (not assumed) before trusting the encoder:
each string's compressed bitstream is **byte-aligned** -- `offset[id+1]
- offset[id] == ceil(bits_used(id) / 8)` held exactly for every ID
checked -- and each language's whole blob is **padded to 4-byte
alignment** with zero bytes to reach the next language's base address
(verified: `base[i] + align4(blob_len[i]) == base[i+1]` for all 7
consecutive pairs, and the actual pad bytes present in the ROM are all
`0x00`).

**Full validation**: re-encoding every real string (unmodified) in all 8
languages and reassembling the blob (header + tree + offset table +
bitstreams + alignment padding) reproduces the **exact original ROM
bytes**, base to base, for all 8 languages -- checked directly against
`baserom.us.gba`, not inferred. This is what makes the pipeline safe to
wire into the actual build rather than just a research decoder.

**`tools/text_migrate.py`** (the `migrate-text` recipe, one-time per
clone, like `migrate-krawall`): decodes all 8 languages from
`baserom.us.gba` into `data/text/<lang>.json` (gitignored -- real game
text content, same footing as the baserom and `data/audio/`, per hard
rule 2). Each string is stored via `text_codec.bytes_to_editable()`:
plain, directly-editable ASCII for the common case, Private-Use-Area
placeholder characters for anything not yet mapped to a real character
(control codes, and the not-yet-decoded extended/accented two-byte
codes -- see "What's NOT yet known"). Each file also carries the raw
Huffman tree and the empirically-captured encode map, so packing never
needs the baserom again.

**`tools/pack_text.py`** (the `pack-text` recipe, wired into `build` and
therefore `compare`/`check-all`): reads `regions.<ver>.txt`'s
`dialog-text`/`dialog-text-table` rows, rebuilds each language's blob
from `data/text/`, and writes real labeled `.s` files to
`build/<ver>/text/` (gitignored), erroring loudly on any size mismatch
against the row's declared end address -- same discipline as
`pack_krawall.py`. Confirmed end-to-end: `just check-all` passes for
both US (dialog text now genuinely part of the assembled ROM, not just
`.incbin`) and JP (`pack_text.py` no-ops cleanly when a version's
manifest has no `dialog-text` rows yet, rather than erroring -- JP
dialog text isn't located, see below).

**`functions.us.cfg`**: named the whole chain (`DrawTextLine`,
`GetGlyphWidth`, `PrintTextBox`, `DecompressDialogText`,
`InitDialogTextTable`, `GetLanguage`, `GetDialogText`, `SetLanguage`),
plus the three OBJ tile loaders from `docs/formats/graphics.md`
(`LoadObjTile`, `LoadObjTileAt`, `LoadObjTileSheet`) -- all were already
reachable via ordinary `bl` spidering, so this is a pure rename, not a
new seed; reconfirmed `just disasm-compare` still matches after adding
them.

**Regenerating regions.us.txt's addresses**: the 8 `dialog-text` rows'
start/end addresses and the `dialog-text-table` row were computed
directly from the validated pipeline (language base from the 8-entry
pointer table, end = base + aligned real blob length), not guessed --
see `tools/pack_text.py`'s own validation (it would refuse to pack on a
mismatch) as the standing check that they stay correct.

## The extended charmap, decoded (PROVEN -- cross-validated by structure and content)

The "not yet known" charmap gap above is now closed for every code any
real string in the ROM actually uses. Found by cross-reading full
strings (not narrow context windows -- an early attempt at this misread
which gap a given placeholder filled when several sat close together)
containing each non-plain-ASCII glyph code across all 8 languages,
using proper nouns repeated verbatim in the credits (`Hernández`,
`Gómez`, `Börjel`, `Steve Vallée`) to pin several codes from one string,
then language grammar/vocabulary for the rest (French `très`, `déjà`,
`très fâché`; Italian `così`/`è`; Spanish `señor`/`añadido`; German
`Überraschung`/`beißendes`; Danish/Dutch `spørgsmål`/`geïnformeerd`).
`tools/text_codec.py`'s `CHARMAP` dict is the authoritative source;
summary:

```
0x0A=\n(line break)  0x7B=(c)  0x7C=oe-ligature  0x7D=inverted-!  0x7E=inverted-?
0x83=A-diaeresis  0x84=A-ring  0x85=AE-ligature  0x87=E-grave  0x88=E-acute
0x8C=I-grave  0x8D=I-acute  0x95=O-diaeresis  0x96=O-stroke  0x98=U-acute
0x99=U-diaeresis  0x9A=sharp-s(ß)
0x9B..0xB5: lowercase a-grave through u-diaeresis, densely packed in
  Latin-1's own relative letter order (skipping unneeded ã/ð/õ)
0xB8=ellipsis  0xB9=trademark  0xBA=OE-ligature(capital)  0xBB=registered-trademark
0xBC=non-breaking space
```

Two findings worth flagging explicitly:

- **Several plain-*printable-ASCII* byte values are also repurposed**,
  not just the >0x7E range originally assumed to be "the" special zone
  -- `{`/`|`/`}`/`~` (`0x7B`/`0x7C`/`0x7D`/`0x7E`) decode to `©`/`œ`/`¡`/`¿`
  respectively, confirmed by content: `}`/`~` only ever appear in
  Spanish, exactly at inverted-punctuation positions (`}NO FUE UNA
  PESADILLA!` -> `¡No fue una pesadilla!`); `{` only appears in the one
  shared legal-disclaimer string, at `"trademarks of and { Warner
  Bros."` -> `(c) Warner Bros.`; `|` only appears in French, in `d'|il`
  -> `d'œil` (a glance). This means `bytes_to_editable()`'s earlier
  "0x20-0x7E passes through as itself" rule was wrong for these four
  values specifically -- now handled via `CHARMAP` taking priority over
  the plain-ASCII passthrough range (narrowed to `0x20-0x7A`).
- **The whole `0x9B-0xB5` accented-letter run's relative ordering
  matches ISO-8859-1/Latin-1's own layout exactly** (a-grave, a-acute,
  a-circumflex, [ã skipped], a-diaeresis, a-ring, ae, c-cedilla,
  e-grave, ...), just renumbered densely to only the letters these 6
  non-English languages actually need. This wasn't assumed going in --
  it fell out of the individually-derived mappings and then served as
  strong independent corroboration for the whole table at once
  (including resolving the one case with only a single, ambiguous real
  occurrence: `0x8C`, pinned by its position in this sequence as
  capital I-grave, fitting `"SÌ"` as an all-caps yes-button label).
- `0xB9` vs `0xBB` (both trademark-family symbols) were disambiguated
  by usage pattern, not decoded content per se: `0xB9` always marks EA's
  own marks (`"Challenge Everything"`, `"EA GAMES"` -- real, documented
  EA taglines using (tm)), while `0xBB` only ever follows `"Game Boy"`/
  `"Game Link"` (Nintendo's registered marks). Flagged as inferred from
  real-world trademark knowledge, not purely from ROM content, in case
  it's ever worth double-checking.

**Confirmed empirically, not just structurally**: the `>0xEF` two-byte
extended-code path described in "The text engine, found" above is
real engine functionality, but **no real string in any of the 8
languages actually uses it** -- every character any real dialog/UI
string needs fits in the single-byte `0x00-0xEF` range. This makes the
earlier "extended charmap not yet decoded" gap moot for this ROM's
actual content, not just closed.

## What's NOT yet known

- **The `0x03003110`/`+4` font-descriptor pointers' own per-language (or
  shared) nature is still genuinely unconfirmed** -- unlike the string
  table above, no write site for these two pointers has been found yet.
  They could be set by a mechanism structurally analogous to
  `0x0806BD78` (an 8-entry font-pointer table somewhere), or there could
  be only one shared font whose extended range simply covers every
  accented glyph any of the 8 languages need. Don't assume either
  answer without finding the actual write site.
- **The `0x080205F8` 6-case dispatch table's purpose is still
  unconfirmed** -- given the language-select mechanism is now fully
  understood and doesn't involve this table at all, its earlier framing
  as a "likely per-language dispatch table" was speculative and is now
  the weaker of the two theories; more likely it's dispatching on
  something else entirely (a dialog window style/variant, a font size
  class, etc.). Not worth pursuing further unless a concrete reason to
  revisit comes up.
- **The `0x40`-prefixed escape/macro system** (macro table at
  `0x03003170`, format/insert codes) is identified as existing but not
  individually decoded -- what each macro code actually does (insert
  player name, color change, icon, etc.) is unknown.
- **The two-byte (`>0xEF`) extended glyph charmap is moot, not
  unsolved** -- see "The extended charmap, decoded" above: no real
  string in any of the 8 languages actually uses it, so there's nothing
  left to decode unless a future find (or a modded string) exercises
  it. `tools/decode_dialog_text.py`'s raw output still prints `\xNN` for
  it since that tool predates the charmap work and reads raw ROM bytes
  directly rather than going through `text_codec.py`'s `CHARMAP` --
  `data/text/*.json` (via `tools/text_migrate.py`) is the place real
  characters actually show up.
- **Done, this session**: a curated content pipeline now exists,
  mirroring Krawall's `data/audio/` + `tools/pack_krawall.py` model --
  see "The extraction pipeline, built and build-integrated" below.
- Whether the type-4/type-6 custom IWRAM codecs (see approach 6 above)
  are used anywhere outside the level-loading dispatcher's 14 known call
  sites remains unconfirmed either way -- moot for text specifically now
  that the real text codec (a third, distinct Huffman-style scheme) has
  been found, but still an open question for the graphics side (see
  `docs/formats/graphics.md`).
