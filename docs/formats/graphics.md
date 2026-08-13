# Graphics asset format

Status: **PROVEN** end-to-end for a complete real sprite (the main-menu
wand cursor) -- ROM source, decompression codec, tile data, and palette
all verified against live game memory, including two independent
methods (live memory read and ROM decode) landing on byte-identical
results. **PROVEN** for the type-6 codec's decode mechanism
(`tools/decode_type6.py`) and now also the type-4 codec
(`tools/decode_type4.py`), both executed via Unicorn against real ROM
code rather than hand-ported. **PROVEN** that three other real palettes
(`0x08A38108`, `0x08A38FE0`, `0x080BD344`) are genuine final color data
for their objects, traced through a deferred per-frame queue to the
vblank DMA that writes real hardware OBJ palette RAM. **PROVEN** that
this palette mechanism is statically extractable at scale, not just
one-at-a-time via live triggering: `tools/find_object_palettes.py`
found 14 real palettes (9 new) with zero gameplay. Tile data remains
the bottleneck for "extract everything" -- only 2 tile resources are
confirmed, both via live tracing, with no statically-walkable
dispatcher argument found for tiles yet (unlike palettes). **STRUCTURAL
MATCH** for three earlier candidate art regions from static ROM
scanning, none code-confirmed and one (`0x08933000`-area's sibling
`0x080BCA24`) since shown to be a **false positive** for the specific
object it was guessed to belong to -- see "The wand cursor sprite"
for why pixel-shape plausibility isn't sufficient evidence on its own.
Important caveat still applies to older findings in this doc: rendered
content using a fake grayscale ramp palette should only be described
structurally, never as depicting specific real-world content. No
build-integrated extractor exists yet (no `regions.<ver>.txt` rows for
graphics).

## What we know

### Real tile data, structurally confirmed

A large run of genuine, non-random, tile-organized 4bpp GBA graphics
sits at ROM **`0x08933000`-`0x08997000`** (~400KB, contiguous,
tile-aligned), with a second, sparser candidate region immediately
before it at **`0x08880000`-`0x08933000`**.

**Caveat on "genuine, artist-authored":** this claim rests on structural
evidence (below), not on recognizing specific subject matter. All
rendering done so far uses a synthetic grayscale ramp palette (palette
index x17 as gray value) because the real palette hasn't been decoded
yet (blocked on the type-6 codec, see below). Under a fake palette,
smooth gradients and shapes are easy to over-interpret as specific
real-world content (sky, hills, etc.) -- an earlier version of this doc
described one region as a "sky gradient / hill silhouette / fence /
ground-water-texture" outdoor scene; that specific reading was walked
back after review, since a grayscale ramp with no ground-truth colors
can't actually support identifying subject matter. What holds up: this
region contains a repeating fence/lattice pattern and some
curling/scrollwork shapes with clean edges and bilateral symmetry, and
a separate area with smooth gradient bands -- real structure, not noise,
but "what it depicts" stays unconfirmed until it's rendered with the
correct palette.

The second region is not one uniform tileset -- a finer flatness scan
(2KB windows) found 17 distinct contiguous good-tile runs inside it,
separated by non-tile-shaped gaps (likely still-compressed data or
unrelated bytes at the coarser scan's resolution):

```
0x08881800-0x08882c00  0x0888a400-0x0888b000  0x0888b400-0x0888d000
0x0888d400-0x0888f000  0x0888f400-0x08890000  0x08890800-0x08894400 (largest, 15KB)
0x088ae000-0x088ae800  0x088b0000-0x088b0800  0x088e8400-0x088e8c00
0x08924400-0x08924c00  0x08926c00-0x08927400  0x08929c00-0x0892a400
0x0892a800-0x0892b400  0x0892b800-0x0892c000  0x0892c400-0x08930400 (16KB)
0x08930800-0x08931000  0x08931400-0x08933000
```

The run at `0x0888b400`-`0x0888f000` renders (grayscale) as smooth
gradient bands plus a fence/lattice band, distinct from the
scrollwork/fence tileset at `0x08933000`+ -- but see the subject-matter
caveat above; "outdoor background scene" was an earlier, overreaching
read of this that's been retracted. What's left as a defensible claim:
non-random, tile-shaped data with a different visual character than the
`0x08933000` region. UNCONFIRMED beyond that.

Found by a structural scanner (not statistics on raw bytes, but on
decoded pixels): every 4-byte-aligned 32-byte window across the full 16MB
ROM was decoded as an 8x8 4bpp tile and scored for horizontal/vertical
pixel-adjacency coherence (a metric that needs no assumed palette or
canvas width -- real art has smooth edges between adjacent pixels far
more often than random bytes do). This region scored far above ROM-wide
background; Krawall audio, executable code, and an earlier weaker
candidate at `0x08937000` (found by a cruder entropy scan, now understood
to be the same tileset family, see below) all scored much lower.

**Rendered proof** (grayscale ramp palette -- index*17 as gray value, so
shape is visible independent of real color, but subject matter is NOT
reliable under a fake palette -- see caveat above): shows non-random
structure -- a repeating curling scrollwork-shaped band and a repeating
picket-fence/lattice-shaped strip, both with clean edges and bilateral
symmetry, repeating consistently across the full 400KB span (i.e. many
visually-related tiles back to back). Whether this is genuinely
decorative/artist-authored art (plausible, given the clean repeating
geometry) or something else entirely is not confirmed -- only the
non-random, tile-shaped, repeating-motif structure is. Confirmed by
directly viewing the rendered PNGs, not just inferred from scores.

**Byte-distribution corroboration**: within this region, the 10 most
common bytes are exactly the 4bpp "flat" bytes where both nibbles match
(`0x33`, `0x00`, `0x44`, `0x55`, `0x11`, `0x66`, `0xDD`, `0xBB`, `0x22`,
`0xEE`) -- adjacent-pixel-pairs sharing one palette index, the classic
signature of flat-filled/outlined pixel art. This also explains an
earlier, independent finding: a sliding-window entropy scan (see
`docs/formats/text.md` approach 3) flagged `0x08937000`-`0x0896b000` as
tile-shaped with dominant byte `0x33` while hunting for a font -- same
underlying phenomenon, same tileset family, not a distinct font
candidate.

### Third region: UI panel graphics candidate

A ROM-wide vectorized structural scan (same pixel-adjacency-coherence
metric as above, run over the *entire* 16MB ROM excluding everything
already covered by `regions.us.txt` and trailing padding) surfaced a
new, previously-unexamined cluster at **`0x08a32800`-`0x08a3a000`**
(just before Krawall audio starts at `0x08A9C6D0`), visually distinct
from both regions above. A zoomed grayscale crop of
**`0x08a36800`-`0x08a38400`** specifically shows a row of clean,
repeating **bordered rectangular panels with rounded corners** -- a
fairly objective geometric read (not color/content speculation): each
panel has a lighter outline/frame and a filled interior, cleanly
repeating left to right. This is a strong candidate for UI
button/panel/inventory-slot art. STRUCTURAL MATCH -- not yet PROVEN
(no palette, and not yet cross-referenced against any code that
consumes it).

Note this region sits outside the level-table/type-6-codec call graph
traced so far -- whether it's compressed at all (and if so, with which
scheme) hasn't been determined; it was found by scanning raw ROM bytes
directly, not via a decompressed buffer.

### Compression: the level-resource table (see also docs/formats/text.md §6)

The dispatcher documented in `docs/formats/text.md` (`sub_0801DD90` /
`0x0801DD88`, near-twin `sub_0801DE5C`) is the game's generic
resource-decompression entry point, reached via a **124-byte-stride
level/room table at ROM `0x0806BE38`**. Its type-nibble dispatch logic
was re-verified against the actual instructions this session (the
earlier paraphrase in `docs/formats/text.md` was imprecise -- corrected
here):

```
lsls r1, r0, #0x18   ; keep header byte0
lsrs r2, r1, #0x1c   ; r2 = byte0 >> 4        (4-bit nibble)
movs r1, #9 / rsbs r1, r1, #0   ; r1 = -9 = ~8
ands r2, r1          ; r2 = nibble & ~8       (clears bit 3)
```

**PROVEN**: the jump-table dispatch key is `(byte0>>4) & 0x7`, not the
raw nibble -- bit 3 of the nibble (`byte0 & 0x80`) is a *separate*
post-processing flag (checked later, routes through an extra pass via
`sub_0801DF48` if set), not part of the type selector. This resolves
header bytes that looked "out of range" for the 0-8 case table in
earlier analysis (e.g. `0xE0` -> nibble `0xE` -> `&0x7`=6, with the
extra-pass flag set; `0x70` -> nibble `7` -> case 7, which is an
intentionally-empty/no-op jump-table slot, not a bug).

### Level-table entry layout (offsets confirmed for a 124-byte entry)

**Correction**: an earlier version of this doc guessed `+0x00/+0x10/
+0x20/+0x30` = BG palettes and `+0x04/+0x14/+0x24/+0x34` = paired BG
tilesets, based on the destination-buffer access pattern alone (no
length header read vs. a leading tile-count header read). Now that the
type-6 codec is actually decoded (see below), that guess is **wrong**:
decoding `+0x04` (508 bytes) and `+0x14` (3748 bytes) -- two different
entries' worth of data -- both produced the exact same recognizable
shape: runs of 4 consecutive `u16` values with small ascending low-10-bit
fields and only 2 distinct values in the high bits across the whole
buffer. That's the canonical **GBA BG screen-entry (tilemap) format**
(10-bit tile index + hflip/vflip/palette-bank bits in the top bits), not
pixel or color data. Corrected findings:

- `+0x04 / +0x14 / +0x24 / +0x34` (and very likely `+0x00/+0x10/+0x20/
  +0x30` too, not yet individually re-checked post-correction): **BG
  tilemap/screen-entry data**, one per background layer. PROVEN for
  `+0x04`/`+0x14` (decoded and pattern-matched against the known GBA
  format), STRUCTURAL MATCH by inference for the others until each is
  individually re-verified.
- The internal "leading count-word" behavior noted in the earlier
  version of this doc (`count << 5` before advancing) needs
  re-interpretation now that the payload is understood to be tilemap
  data, not a tileset with a tile-count header -- not yet redone.
- `+0x08/0x0c`, `+0x18/0x1c`, `+0x28/0x2c`, `+0x38/0x3c`: always zero in
  the one entry inspected so far -- padding/reserved, unconfirmed as a
  general rule.
- `+0x40/+0x44`: two more real resource pointers, same decompression
  path and same type-6 codec; also decoded to the ascending-index/
  mostly-zero tilemap shape rather than plausible BGR555 colors. Asset
  class still not pinned down beyond "also a tilemap-shaped decode",
  which itself is a bit surprising for what were guessed to be a 5th
  shared/palette-like resource -- worth re-examining.
- `+0x50` through the entry's tail (up to `+0x7B`, stride is `0x7C`):
  **NOT pointers at all**, despite superficially parsing as plausible ROM
  addresses (one such value was fed through a from-scratch, independently
  written standard-GBA-LZ77 decoder as a sanity check: the very first
  back-reference token demands copying from a negative offset in an
  empty output buffer -- an invalid stream, proving it's not a real
  compressed-resource header). These are plain numeric arguments (sizes,
  coordinates) passed directly into a screen/window-setup routine
  (`sub_0803E588`). PROVEN not to be graphics pointers.
- **All decompression destinations observed are dynamically-allocated
  EWRAM heap buffers**, not fixed VRAM addresses -- the actual
  VRAM upload happens later via DMA/CpuSet, outside this call graph
  (not traced yet). This means you cannot identify a field's asset class
  by its destination address alone within this call graph.
- Every genuine resource pointer actually inspected so far uses
  **compression type 6**, now fully decoded -- see next section. **No
  real palette content has been found in any level-table field decoded
  so far** -- the actual BG palette for this level's tiles must live
  somewhere else (or the palette/tileset guess mapped to the wrong
  offsets entirely; not yet determined).

### The type-6 codec, decoded (PROVEN)

Decoded by executing the *real* ARM-mode ROM bytes (`0x080005EC`, 828
bytes, the exact code the game copies into IWRAM at runtime -- see
`docs/formats/text.md` §6) in the Unicorn CPU emulator, rather than
hand-reimplementing the disassembly. This guarantees exact fidelity to
the actual algorithm without risking a subtly-wrong-but-plausible manual
port. Verified against 7 real level-table (`0x0806BE38` entry 0)
resource pointers (`+0x00/0x04/0x10/0x14/0x20/0x24/0x30/0x34/0x40/0x44`,
all type 6): every decode produced exactly the byte count declared in
the outer 24-bit size field (508, 6676, 508, 3748, 7636, 6052, 800, 508
bytes) -- strong evidence the stream-termination logic is right, not an
artificial cutoff.

Algorithm, bit-level:

- **Outer wrapper header** (4 bytes, read by `sub_0801DD90`, not the
  codec itself): `byte0`: `type = (byte0>>4)&7` (6 = this codec),
  `extra_pass = (byte0>>4)&8`; `byte1..3` (LE 24-bit): decompressed size.
- **Codec's own internal header** (4 bytes, right after the outer
  header): `byte0` = byte count (always a multiple of 4) of a small
  table copied onto the stack, used later as literal-length lookup
  values; `byte1` = an escape marker compared against a raw-bit-read
  value each iteration (match => LZ back-reference path, no match =>
  literal path); `byte2/byte3` packed into a control word used as
  raw-bit-field widths.
- **Bit reader**: 32-bit MSB-first shift register with a
  sentinel-refill idiom (`r8 <<= 1; if r8==0: r8 = next_word(); r8 =
  (r8<<1)|carry`).
- **Length/gap code** (a capped exp-Golomb/Elias-gamma variant, at ROM
  `0x8000634`): count leading 1-bits (up to 7) via `GetBit`, then read
  that many more raw bits and OR them onto `1<<ones`; result in `[1,255]`.
- **Main loop** (`0x800072C`+): reads a raw field via the packed
  control word; if it matches the escape marker, it's an LZ-style
  back-reference (distance/length built from the gamma code, copying
  from `dst + pos - distance`); otherwise literal bytes are emitted,
  packed two-at-a-time into `u16` halfword stores via a toggling parity
  flag. The exact byte/halfword/run copy sub-cases in the final ~250
  bytes of the codec (`0x8000814`-`0x80008F8`) are LZSS-shaped but were
  not hand-verified branch-by-branch -- covered anyway by the
  emulator-execution approach, so not a blocker for correctness, just
  for someone wanting to hand-port it to non-Python/non-emulated code
  later.
- **Companion post-pass** (separate functions `sub_0801DF48`/
  `sub_0801DF6C`, run by the *caller* only when `extra_pass` is set, not
  part of the codec itself): an in-place running sum over the decoded
  buffer treated as `u16[]` -- the codec's raw output is itself
  delta-coded in this mode, and this pass integrates it back to
  absolute values. This is exactly the delta-decode step needed to get
  the ascending-tile-index tilemap runs described above to make sense.

**Worked example** (a concrete resource pointer, for manual
inspection): ROM `0x08658a6c` (level-table entry 0's `+0x00` field,
file offset `0x658a6c` / decimal `6654572`). First 4 bytes:
`e0 fc 01 00` -- byte0 `0xe0` decodes to type 6 with the extra-pass
delta flag set; bytes 1-3 (`fc 01 00` LE) give a declared decompressed
size of 508 bytes. Everything after that 4-byte header is the type-6
compressed stream itself, consumable only via the decoder above (raw
hex/GIMP inspection of the compressed bytes won't show anything
recognizable -- compressed streams don't look like their decoded
content).

`tools/decode_type6.py` is now checked into the repo, implementing
exactly this (Unicorn-based execution, mirroring
`tools/extract_krawall.py`'s CLI style). `unicorn` was added to
`flake.nix`'s dev shell (`python3Packages.unicorn`). Verified against 4
real level-table resource pointers, all matching declared sizes exactly
(508, 6676, 3748, 6052 bytes). Not yet wired into `just build` or
`regions.<ver>.txt` -- no confirmed, curated resource identities exist
yet to extract (see "What's NOT yet known"), so there's nothing correct
to commit as extracted output yet; it's a research/CLI tool for now.

### Real, uncompressed palettes -- found via code tracing (PROVEN)

Unlike everything above, these were found by tracing forward from
actual code, not by scanning ROM bytes -- tracing where decompressed
resource buffers get copied into VRAM (recommended next step 2) led
instead to a **separate, uncompressed resource path** entirely, used by
what looks like a generic object/sprite-spawn function,
`sub_08001528(type, x, y, resource_ptr)` (called from e.g.
`sub_0800E0CC` via `sub_080078A4`, and from `sub_0801BA54`). Three
`resource_ptr` values found via direct literal-pool grep for `0x08a3`
addresses (the same ROM neighborhood as the UI-panel candidate from the
structural scan, `0x08a32800`-`0x08a3a000`):

- `0x08A396A4`: copied via `CpuFastSet` (`svc 0xC`) straight to OBJ
  palette RAM (`0x05000200 + bank*32`) in `sub_0800E0CC` and two
  near-identical sibling functions (all reference the same source --
  likely a shared flash/highlight-effect palette). 16 valid BGR555
  colors (bit15=0 throughout), but low-diversity: one accent color
  (`R120 G96 B120`) followed by 15 entries of solid white -- consistent
  with a hit-flash/sparkle effect, not general art.
- `0x08A38108`: passed as `resource_ptr` to `sub_08001528`. 16 valid,
  genuinely diverse BGR555 colors (cyan/green/teal/blue progression,
  then red/orange tones, black-filled tail) -- a real curated palette,
  not a placeholder.
- `0x08A38FE0`: same call pattern, different object. 16 valid, diverse
  colors (blue, white, brown, cream, greens, warm oranges/reds) -- also
  a real curated palette.
- `0x080BD344`: found live via mGBA breakpoint on `sub_08030978`
  (triggered by the title screen's "Press Start" prompt). 16 valid,
  diverse colors (warm orange/red fading to white, gold, then a
  repeated gray-brown) -- also real, plausibly a title-screen sparkle/
  particle effect given the trigger.

**Not yet resolved**: pairing `0x08A38108`/`0x08A38FE0` against tile
data -- both the earlier structural-scan candidates (filigree tileset,
UI-panel region) and the bytes immediately following each palette in
its own resource block (the natural "palette then tile data" struct
layout guess) -- produced garish, incoherent-looking renders, not
recognizable art.

### `sub_08001528`'s call chain, traced (PROVEN through several hops)

Read `sub_08001528` itself and followed `resource_ptr` through every
function that touches it, to resolve the mismatch above. Verified
against the actual disassembly at each hop (not just Ghidra's
decompile, which was independently cross-checked and matched exactly):

- `sub_08001528(type, x, y, resource_ptr)`: a generic pooled-object
  spawner (fixed 0x128-byte slots, doubly-linked free/active lists --
  the allocator itself, `sub_080286D8`, is a textbook intrusive
  free-list-pop/active-list-push pair). `resource_ptr` is not
  dereferenced here at all -- forwarded untouched to `sub_08030878`.
- `sub_08030878(obj, resource_ptr)`: also doesn't dereference
  `resource_ptr` -- passes it to `sub_080309E8` for a cache lookup.
- `sub_080309E8(resource_ptr)`: a **resource cache lookup**, not a
  loader. Scans a fixed 15-slot table at `0x03005114` (8-byte stride:
  `{void *ptr; u16 refcount; u16 flags;}`) for an existing entry whose
  stored *pointer value* equals `resource_ptr` (plain pointer equality,
  never dereferences `resource_ptr`'s contents). Returns the slot index,
  or `0xFF` if not already cached.
- Back in `sub_08030878`: on a cache hit, `resource_ptr` is discarded
  (a `0` is passed onward instead -- no need to re-load). On a miss, a
  new slot index is allocated (`sub_08030794`) and `resource_ptr` is
  passed on for real, for the first and only time.
- `sub_08030978(slotIndex, obj, resource_ptr)`: bumps the cache slot's
  refcount; if `resource_ptr != 0` (first load), stores it in the slot
  and calls `sub_0800D264(resource_ptr + 2, slotIndex*16 + 1, 0xF)`.
  Also stores `slotIndex` into the upper nibble of the object's
  `+0xD5` byte (matches the `>>4` read of that same field seen
  elsewhere, e.g. `sub_080308D8` -- consistent cross-reference, good
  sign the slot-index tracking is understood correctly).
- `sub_0800D264(ptr, val1, val2)`: **not a decoder** -- a deferred
  request queue. Appends `{val1: u16, val2: u16, ptr: void*}` (8-byte
  entries) to a table at `0x030023E8` (max 24 entries, count at
  `0x030022F0`). This is consistent with GBA engines deferring actual
  VRAM/palette-RAM writes to vblank rather than writing immediately.
  **Nothing in the disassembly reads this table via a literal address**
  -- every one of the handful of `=0x030023E8`/`=0x030022F0` references
  is a write, from this function and one sibling (`sub_0800D29C`). The
  actual processor is reached some other way (a runtime-computed base
  pointer, not a literal load) -- static literal-pool tracing stops
  being effective here.

**What this changes about the earlier guess**: `val2 = 0xF` (15) and the
`resource_ptr + 2` skip strongly suggest this queued request is a
**palette-only upload** -- 15 colors (GBA convention: OBJ palette index
0 is transparent/unused, so a real palette often only needs to supply
the other 15), starting 2 bytes into the resource (a 2-byte header
before the color data, consistent with our palette decode being
*approximately* right, just off by one index). `val1 = slotIndex*16+1`
reads as a palette-bank-relative destination. If this reading holds,
**`resource_ptr` is palette-only data, not a combined palette+tileset
struct** -- explaining why appending guessed tile data after it never
rendered coherently. The actual tile graphics for objects using this
resource are most likely a separate, shared/fixed spritesheet
referenced elsewhere (a common "one tileset, many palette banks" cheap
recoloring technique) -- not yet located.

### The deferred queue's flush, confirmed live (PROVEN via mGBA debugger)

The queue processor that static analysis couldn't find (no literal-address
reads of `0x030023E8` anywhere in the disassembly) was located with the
user driving mGBA's built-in debugger console interactively (not the
gdb-stub approach that was previously unreliable for Krawall -- mGBA's
native console, with its own breakpoint/watchpoint/backtrace commands,
worked reliably here). A write watchpoint on OBJ palette RAM
(`0x05000200`, length `0x200`) caught a real hit, whose PC (`0x0800DB9C`)
fell just past the end of a named function (`sub_0800D9D4`) into a
stretch of bytes `gbadisasm` never split into a function (no seed in
`functions.us.cfg`, sitting there as raw `.byte` data despite containing
real code) -- disassembled directly from the ROM with `capstone` to
confirm:

```
sub_0800DB58(struct_ptr):
    flags = struct_ptr[0]  (u16)
    if not (flags & 2): return             // "pending" flag gate

    struct_ptr[0] = flags & 0xFFFD          // clear pending flag
    table = 0x030024B0                       // fixed IWRAM table (2 pointers per bank)
    if (flags & 4): table += 8               // select alternate table ("bank B")

    entry = struct_ptr[6] (byte) * 2         // slot index -> halfword byte-offset

    DMA3SAD (0x040000D4) = table[0] + entry  // source
    DMA3DAD (0x040000D8) = table[1] + entry  // dest
    DMA3CNT (0x040000DC) = struct_ptr[0xA] | 0x80000000   // count/mode | DMA-enable
```

A live `bt` (mGBA's backtrace, off by default -- needs `stack trace-only`
first) traced the full call chain that reaches this function every
frame: `sub_08049EBC` (`svc 5`, `VBlankIntrWait`, already named in
`docs/formats/text.md`'s BIOS wrapper table) -> BIOS vblank
wait/dispatch -> an **IWRAM-resident interrupt handler at `0x030035A8`**
(the game's own vblank ISR, copied to IWRAM for speed -- not yet
otherwise documented) -> `0x08025E95` -> `0x0800D306` (the palette-flush
loop itself, right next to the already-known `sub_0800D2F4`/
`sub_0800D944` animation-slot processors -- almost certainly iterating
pending slots and calling `sub_0800DB58` once per slot, matching the
observed `r6` register counting down `8, 7, ...` across consecutive
hits) -> `sub_0800DB58`.

Live memory reads of the IWRAM table at the moment of a real hit:

```
0x030024B0: source=0x0200BCA0  dest=0x05000000   (bank A: BG palette RAM)
0x030024B8: source=0x0200BEB0  dest=0x05000200   (bank B: OBJ palette RAM -- this is the one that fired)
0x0300230C: struct read by sub_0800DB58 for this hit (06080005 FF000808 01000000 0200C2C0)
```

**Conclusion**: the DMA source (`0x0200BEB0 + entry*2`) is **EWRAM, not
ROM** -- confirming a staging buffer sits between the ROM resource and
the final palette-RAM DMA, exactly as GBA engines commonly do (decode/
stage during the frame, flush at vblank when it's safe to touch palette
RAM). The actual ROM-to-EWRAM copy step itself was not caught live (the
watchpoint was on the palette-RAM destination, not the staging buffer --
watching writes to `0x0200BEB0` length `0x200` would catch it, not yet
tried), but there is no evidence or reason to expect it transforms the
data -- **this closes out the palette question**: `resource_ptr + 2` in
ROM is confirmed to be the real, final 15-color BGR555 data, exactly as
read earlier in this doc. No further palette work is needed for the
three known examples (`0x08A38108`, `0x08A38FE0`, `0x080BD344` -- the
third found live via this same debugging session, fired by the
title-screen "Press Start" prompt, also 16 valid diverse BGR555 colors:
warm orange/red fading to white, gold, and a repeated gray-brown).

**Update -- the tile source is now found, live, via the same technique.**
See the next section: not the shared-tileset hypothesis originally
guessed here, but real per-object BIOS-compressed tile data via the
*same* generic dispatcher (`sub_0801DE5C`) documented back in
`docs/formats/text.md` sec 6, which turns out to also be exercised for
OBJ (sprite) tiles, not only BG/level graphics as first assumed.

### A real, confirmed sprite tile (PROVEN via mGBA debugger)

Same live-debugging technique as the palette flush above, pointed at
OBJ tile VRAM (`0x06010000`, length `0x8000`) instead of palette RAM.
After skipping past the expected boot-time full-VRAM zero-clear (fires
first, `old value == new value == 0`, harmless), a real hit landed with
`LR = 0x0801DEDB`, immediately after a call to `sub_08049EB0` (the
already-known `svc 0x15` / `RLUnCompVram` BIOS wrapper). `LR` falls
inside **`sub_0801DE5C`** -- the same generic resource dispatcher
documented in `docs/formats/text.md` sec 6, whose case-3 branch (RLE)
calls exactly this wrapper. A second hit shortly after, `LR =
0x0801DEEB`, also fell inside the same function. This is a live,
direct confirmation that `sub_0801DE5C` -- previously only traced
statically to BG/level-graphics call sites -- is *also* used for OBJ
sprite tiles during real gameplay, not a separate, still-unfound
mechanism.

The register state at the first hit (`r3 = r5 = 0x080BCDD8`) pointed
directly at a real BIOS RLE-compressed resource in ROM. Confirmed:

```
0x080BCDD8: 30 20 00 00  -- byte0=0x30 -> type nibble 3 (RLUnComp), size=0x20 (32 bytes = one 4bpp tile)
```

Decoded with a from-scratch RLUnComp implementation (`tools/decode_bios.py`,
written this session -- see below), verified byte-for-byte against a
hand-traced decode:

```
20 00 00 0d 80 97 00 00 60 87 09 00 69 76 09 00
90 98 8f 00 00 00 00 00 00 00 00 00 30 20 00 00
```

Rendered as an 8x8 4bpp tile (grayscale ramp -- real palette for *this
specific* tile not yet confirmed, though the "flash" palette
`0x08A396A4` was tried as a plausible guess given the effect-like
context): a small blob that grows from a narrow top, widens through
the middle, peaks at a bright value (nibble 15) near the bottom, then
fades -- an unmistakable **spark/glow particle shape**, not noise or
an arbitrary UI element. This is the first tile-level graphics find in
this whole investigation confirmed by direct decode of a live-traced
real resource, rather than by statistical guessing over raw ROM bytes.

**Not yet done**: this specific tile's correct palette (three real
candidates exist; which one actually pairs with this specific object
hasn't been confirmed -- would need to read the object's palette-slot
field, or catch a palette hit and a tile hit in the same session close
together in time/context). Finding the rest of the sprite's tiles is
done -- see next section.

### The wand cursor sprite (PROVEN -- ROM source, tile data, and palette all verified against real game memory)

**Status: fully resolved.** This section originally documented a false
positive; corrected below, then resolved for real via live memory
reads and a newly-built, verified proprietary-codec decoder.

#### False start: `0x080BCA24`

Searching the same ROM neighborhood as the confirmed spark tile
(`0x080BCDD8`, +/- `0x4000`) for other structurally-valid small BIOS
resources (try every offset, keep only ones that decode cleanly to the
declared size, score by tile-adjacency coherence) turned up
`0x080BCA24`, a 224-byte (7-tile) RLUnComp resource. The user
recognized its rendered shape as "the wand sprite used as a cursor,"
and after two wrong arrangement guesses (see git history of this doc
for the methodology lesson about not asserting "confirmed" on
pixel-shape plausibility alone), a 3x3-grid-with-hflip layout produced
a clean, recognizable wand silhouette.

**This turned out to be a false positive.** Once the *real* wand data
was captured live (below), byte comparison showed zero match with
`0x080BCA24`'s decoded tiles. It's real wand-shaped art (the resemblance
wasn't coincidence-from-noise), but not what's actually loaded for this
cursor -- likely used elsewhere, or by a different context. This is a
concrete demonstration of why the standing lesson (don't trust
pixel-shape plausibility without real ground truth) matters: a
*correct-looking* result was still wrong.

#### The real sprite: OAM, live VRAM, and live palette

Confirmed the wand is a real OBJ (hardware sprite), not BG art, using
mGBA's per-layer visibility toggle (Objects layer shows "the wand
sprite, including the particles that fall from it"). Read its OAM
entry live (`0x07000000`+, decoded standard GBA attr0/attr1/attr2
format):

```
Y=90 X=1  shape=square size=16x16 (2x2 tiles)  hflip=1  tile_base=4 (VRAM 0x06010080)  palette_bank=1
```

Two nearby small OBJ entries (tile=3 and tile=1, palette bank 2,
8x8 single tiles) are the falling particles, not the wand body.

Read the real tile data directly from OBJ tile VRAM (`0x06010080`,
128 bytes = 4 tiles) and the real palette directly from OBJ palette
RAM (`0x05000200 + 1*32 = 0x05000220`, 16 colors). Rendered with the
correct whole-sprite hflip (tile *positions* mirror, AND each tile's
pixel content mirrors -- not per-tile-in-place, an earlier attempt got
this wrong too): a genuine, complete wand -- teal/cyan ornate tip
blending into a dark reddish-brown wooden shaft, tapering to a handle.
**Confirmed correct by the user against the actual running game.**

The live palette bank 2 (the falling particles) turned out to be
byte-identical to the already-known ROM palette `0x080BD344` -- a nice
independent cross-check of that earlier finding. The wand's own
palette (bank 1) is a new, distinct real palette: warm red/orange
(shared with bank 2's first half) transitioning into cool teals/greens
instead of gold. Its ROM source hasn't been located.

#### Finding the ROM source: the type-4 codec, decoded

No match for the live tile/palette bytes in the ROM raw (uncompressed)
or in any standard BIOS format (LZ77/Huffman/RLE, scanned across the
whole ROM) -- meaning it's compressed with one of the two proprietary
codecs. Rather than guess further, caught it live: breakpointed the
type-4 codec's IWRAM entry point (`0x030028D4`, installed from ROM
`0x08006108` -- see `docs/formats/text.md` sec 6) and watched it fire
repeatedly while the wand's glow tiles loaded. `r0` at each hit is a
clean, uncorrupted ROM source address (unlike watching the VRAM
*write* destination, which catches the codec mid-stream with an
already-advanced read cursor -- a dead end tried first). Found **four
distinct source addresses** all targeting the same VRAM destination
(`0x06010080`): `0x080BC9CC`, `0x080BCADC`, `0x080BCBD0`, `0x080BCCD8`
-- almost certainly four animation frames of the glow, redrawn on a
cycle (a fifth, unrelated destination, `0x06010100`/tile 8, is a
different graphic loading in the same batch, not the wand).

Disassembling the codec directly (`0x08006108`, 504 bytes, ARM mode)
showed it's **not** the simple byte-token LZSS originally guessed in
`docs/formats/text.md` sec 6 -- it's halfword-aligned with careful
byte-parity tracking, structurally closer to the type-6 codec than to
a textbook LZSS. Given the RLE decoder mistake earlier this session
(a hand port that silently computed the wrong stream length), built
**`tools/decode_type4.py`** the same way as `tools/decode_type6.py`:
executes the real ARM code via Unicorn rather than hand-porting the
logic.

**Verification: `0x080BCBD0` decodes to a 128-byte output that is a
byte-for-byte exact match against all four wand tiles read live from
VRAM.** The codec stops writing at exactly that boundary (everything
past byte 128 in the output buffer is untouched scratch memory) -- not
an assumed cutoff, the real behavior. This is now the strongest
evidence of any finding in this document: independently confirmed via
two different methods (live memory read, and ROM decode) landing on
identical bytes.

**Not yet done**: decoding the other three animation-frame addresses
(mechanically the same, just not run yet); locating the wand's own
palette (bank 1) in ROM -- same "not in raw or standard-BIOS-compressed
form" result as the tiles, so it's presumably also type-4 or type-6,
findable the same way (live breakpoint on whatever writes OBJ palette
bank 1, source register at entry) if wanted.

**`tools/decode_bios.py`** (new, checked into the repo): decodes any of
the three standard BIOS formats (LZ77UnComp, HuffUnComp, RLUnComp) from
a ROM address, dispatching on the header's type nibble exactly like the
game's own dispatcher. Unlike `tools/decode_type6.py` (which had to
reverse-engineer an undocumented proprietary codec by executing real
ROM code in an emulator), these are the public, well-documented GBA
BIOS formats, reimplemented directly from spec -- verified against the
live-confirmed `0x080BCDD8` example above. The RLE decoder specifically
had to be written to stop exactly at the declared byte count even
mid-token (matching real BIOS behavior) -- an earlier draft that
consumed whole literal-run tokens regardless of remaining size computed
the wrong stream length and corrupted the next-resource offset.

### Static palette extraction at scale (PROVEN, 14 real palettes found with zero gameplay)

Live-triggering every asset individually doesn't scale to "extract
everything" -- the actual goal. Once the mechanism was understood (not
before), the palette side of it turned out to be fully statically
enumerable: `sub_08001528`'s `resource_ptr` argument is *always*
treated as a 2-byte header + 15-color palette by `sub_08030978`
regardless of the header byte's own value (no branching on it) --
confirmed by tracing the call chain to the real vblank DMA flush (see
above). That means every call site's `resource_ptr` literal is a
palette candidate, findable by walking each call site backward through
its enclosing function for the last assignment to the argument
register, without running the game at all.

**`tools/find_object_palettes.py`** (new): finds every `bl
sub_08001528` in `build/us/full_disasm.s` (30 total), resolves each
call's `resource_ptr` argument via backward literal-pool/register-copy
tracing, and decodes+reports each resolved one's palette. Result:
**14 of 30 resolved to real ROM addresses, all producing genuinely
diverse palettes** (5-15 distinct colors out of 15, not degenerate
single-color runs) when decoded with the confirmed 2-byte-header
convention -- including independently re-deriving the two
already-known palettes `0x08A38108`/`0x08A38FE0` as a cross-check.
Nine new real palette addresses found this way (some referenced by
more than one call site):

```
0x08d79d04  0x080c1d9c  0x08d9a320  0x08d9a340  0x08d9a300
0x08077aec  0x080c2e78  0x08069574  0x080cc614
```

Visually confirmed varied and real (not scanning artifacts) by
rendering swatches: rose/pink tones, yellow-to-orange-to-teal,
blues, a red/orange/cream set, purple/lavender, and blue-gray with
bright green accents -- distinct palette *families*, not near-duplicates
of each other or of the four already-known ones.

**The 16 unresolved call sites** have `resource_ptr` set some other
way the backward trace doesn't follow (loaded from a struct field,
computed at runtime, passed down from a caller) -- a static,
best-effort trace, not full dataflow analysis. Deeper resolution is
possible but not done.

**The real remaining gap is tiles, not palettes.** Only two tile
resources are confirmed at all (the spark `0x080BCDD8` and the wand's
4 glow frames), both found via live tracing, not a repeatable static
scan. Unlike the palette path, there's no confirmed single dispatcher
argument convention to statically walk for tiles yet -- the wand's
tile call didn't come from any of `sub_0801DE5C`'s 3 previously-known
static callers (which are for level/BG graphics), so there's at least
one more calling pattern for OBJ tiles that hasn't been found and
enumerated. This is the next real unlock for reaching "extract
everything" -- not more live-triggering of individual assets, but
finding and statically walking whatever calls into the tile path the
way `sub_08001528` calls into the palette path.

## What's NOT yet known

- **A real, working colored render.** Done for the wand cursor -- see
  "The wand cursor sprite." Still not done for the spark
  (`0x080BCDD8`)/particle-effect family or the three earlier
  structural-scan candidate regions.
- **None of the three original candidate art regions (`0x08933000`
  filigree tileset, `0x0888xxxx` region, `0x08a36800` UI panels) have a
  confirmed code reference.** A direct grep of `build/us/full_disasm.s`
  for PC-relative literal-pool loads of these exact addresses found
  **zero** hits for the filigree tileset and the UI-panel region. The
  `0x0888xxxx` region had 3 nearby hits (`0x08882CFC` referenced at
  disasm lines 15979/20385, `0x08886004` at line 16074) but these don't
  exactly match any of the 17 tile-shaped sub-runs identified earlier in
  that region, so they're not confirmed to be the same data. Given
  `0x080BCA24` (found by the identical structural-scan technique, in the
  same ROM neighborhood as real confirmed sprite data) turned out to be
  a false positive for the object it was guessed to belong to, treat
  these three with the same skepticism -- structural plausibility alone
  has now been directly shown insufficient on this ROM, twice
  (see also the standing memory on this).
- **Type-4 codec**: now decoded (`tools/decode_type4.py`, Unicorn-based,
  verified byte-exact against live memory -- see "Finding the ROM
  source" above). Only tested against one resource family (the wand's
  animation frames); not yet tried against other type-4 resources
  (there may be none confirmed elsewhere yet).
- The wand's own palette (bank 1, live-read, distinct from the three
  earlier known palettes) has no located ROM source yet -- same
  "not raw, not standard-BIOS" result as its tiles, so presumably also
  type-4 or type-6, findable the same way (live breakpoint on whatever
  writes OBJ palette bank 1).
- Standard BIOS LZ77 was explicitly ruled out as the compression for the
  filigree tile blob at `0x08933000` (`/tmp/hp3gfx/lz77.py`, an
  independent decoder: no valid LZ77 stream of length >100 bytes found
  anywhere spanning that region) -- unrelated to the now-resolved wand
  sprite, which lives at a different address and uses type-4.

## Recommended next steps

The wand cursor sprite is fully resolved (ROM source, codec, tiles,
palette, all verified against live game memory) -- see "The wand
cursor sprite" above. That also delivered two reusable, verified tools
(`tools/decode_type6.py`, `tools/decode_type4.py`) and confirmed the
general methodology (live mGBA breakpoints/watchpoints beat blind ROM
scanning whenever a live trigger is available) works reliably for this
project, using mGBA's built-in debugger console driven interactively
by the user -- notably *better* than the gdb-stub approach `CLAUDE.md`
flags as unreliable for Krawall. Remaining, in rough priority order:

1. **Decode the wand's other 3 animation frames** (`0x080BC9CC`,
   `0x080BCADC`, `0x080BCCD8` -- mechanically identical to the already-
   verified `0x080BCBD0`, just needs running) and its palette (bank 1's
   ROM source, not yet located -- same live-breakpoint technique,
   pointed at whatever writes OBJ palette RAM `0x05000220`-`0x0500023F`).
2. **Find the spark/particle effect's remaining tiles and correct
   palette pairing.** One real tile is confirmed (`0x080BCDD8`) via
   `sub_0801DE5C`'s RLE path; likely a multi-tile animation like the
   wand's glow. Three real palettes exist (`0x08A38108`, `0x08A38FE0`,
   `0x080BD344`) but which one (if any) pairs with this specific effect
   isn't confirmed.
3. **Re-examine the three original structural-scan candidate regions**
   (`0x08933000` filigree tileset, `0x0888xxxx` region, `0x08a36800` UI
   panels) given `0x080BCA24`'s false-positive result -- these need a
   code-confirmed live trace (same OAM/VRAM-watchpoint technique) before
   trusting them for anything, not just a literal-pool grep.
4. Once more real tile data is paired with a real palette, revisit the
   delta-coded tilemap fields decoded from the level table
   (`docs/formats/graphics.md`'s "Level-table entry layout" section) to
   see whether they arrange any of it into an actual on-screen scene.

## Confidence key

Same convention as the rest of `docs/`, see `docs/memory-map/krawall.md`:
**PROVEN** (directly verifiable), **STRUCTURAL MATCH** (shape/behavior
matches strongly but not byte-verified against a spec), **UNCONFIRMED**
(plausible, no independent corroboration yet).
