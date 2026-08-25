# Graphics asset format

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

Status: **PROVEN** end-to-end for a complete real sprite (the main-menu
wand cursor) -- ROM source, decompression codec, tile data, and palette
all verified against live game memory, including two independent
methods (live memory read and ROM decode) landing on byte-identical
results. **PROVEN** for the type-6 codec's decode mechanism
(`tools/graphics/decode_type6.py`) and now also the type-4 codec
(`tools/graphics/decode_type4.py`), both executed via Unicorn against real ROM
code rather than hand-ported. **PROVEN** that three other real palettes
(`0x08A38108`, `0x08A38FE0`, `0x080BD344`) are genuine final color data
for their objects, traced through a deferred per-frame queue to the
vblank DMA that writes real hardware OBJ palette RAM. **PROVEN** that
this palette mechanism is statically extractable at scale, not just
one-at-a-time via live triggering: `tools/graphics/find_object_palettes.py`
found 14 real palettes (9 new) with zero gameplay. **PROVEN and
extracted end-to-end for one whole tile-data-consuming resource class**:
every real item's icon (`ItemEntry.pPalette/pTileData/pFrameData`, see "Item
icons" below) is now statically decoded, extracted verbatim to
`data/images/items/*.bin`, and packed into a real, byte-verified
`regions.us.txt` region -- the first build-integrated
(`just extract-item-icons`) image extractor in this repo, also
rendered for viewing to `extracted/items/*.png`. Tile data otherwise
remains the bottleneck for "extract everything" beyond items -- only 2
non-item tile resources are
confirmed, both via live tracing, with no statically-walkable
dispatcher argument found for the general case yet (unlike palettes).
**STRUCTURAL MATCH** for three earlier candidate art regions from
static ROM scanning, none code-confirmed and one (`0x08933000`-area's
sibling `0x080BCA24`) a **false positive** for the object it resembles
-- see "The wand cursor sprite" for why pixel-shape plausibility isn't
sufficient evidence on its own. Standing caveat throughout this doc:
rendered content using a fake grayscale ramp palette must only be
described structurally, never as depicting specific real-world content
(item icons are the one exception -- their real, decoded palette makes
identifying content legitimate). No build-integrated extractor exists
yet for graphics data outside item icons.

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
real-world content (sky, hills, etc.). A grayscale ramp with no
ground-truth colors cannot support identifying subject matter at all --
readings like "sky gradient / hill silhouette / fence /
ground-water-texture" are not defensible from these renders. What holds
up: this region contains a repeating fence/lattice pattern and some
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
caveat above: calling this an "outdoor background scene" overreaches what
a grayscale render can show. The defensible claim is non-random,
tile-shaped data with a different visual character than the `0x08933000`
region. UNCONFIRMED beyond that.

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
[`text.md`](text.md)'s approach 3) flagged `0x08937000`-`0x0896b000` as
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

### The resource-decompression dispatcher

**PROVEN.** `sub_0801DD90` (`0x0801DD88`, with a near-twin
`sub_0801DE5C`) is the game's one generic resource-decompression entry
point, used for BG/level graphics, OBJ sprite tiles, and anything else
stored compressed. It reads a 4-byte wrapper header off the resource and
jump-tables on the type nibble:

```
lsls r1, r0, #0x18   ; keep header byte0
lsrs r2, r1, #0x1c   ; r2 = byte0 >> 4        (4-bit nibble)
movs r1, #9 / rsbs r1, r1, #0   ; r1 = -9 = ~8
ands r2, r1          ; r2 = nibble & ~8       (clears bit 3)
```

The dispatch key is `(byte0 >> 4) & 0x7`, **not** the raw nibble: bit 3
of the nibble (`byte0 & 0x80`) is a separate post-processing flag,
checked later and routing through an extra pass via `sub_0801DF48`. So
`0xE0` is type 6 with the extra pass set, and `0x70` is type 7, an
intentionally-empty jump-table slot. The remaining 3 header bytes are
the decompressed size (LE 24-bit).

| Type | Codec |
|---|---|
| 0 | raw `CpuSet` copy (uncompressed) |
| 1 | `svc 0x11`, BIOS `LZ77UnCompWram` |
| 2 | `svc 0x13`, BIOS `HuffUnComp` |
| 3 | `svc 0x14`, BIOS `RLUnCompWram` |
| 4 | proprietary, IWRAM-installed -- see "the type-4 codec" below |
| 6 | proprietary, IWRAM-installed -- see "The type-6 codec, decoded" below |

Both proprietary codecs are installed into IWRAM at runtime by a
function at `0x0801DD40` (not statically reachable by `gbadisasm`'s
function discovery -- the same invisibility issue as `kramInstall`, see
[`../memory-map/krawall.md`](../memory-map/krawall.md)), via two
`CpuSet` (`svc 0xB`) copies:

- type 4: ROM `0x08006108`, 504 bytes, to IWRAM `0x030028D4`; entry
  pointer stashed at `0x030028CC`.
- type 6: ROM `0x080005EC`, 828 bytes, to IWRAM `0x03002ACC`; entry
  pointer stashed at `0x030028D0`.

The dispatcher's 14 static call sites all sit in the level/graphics
loading subsystem, reached via a **124-byte-stride level/room table at
ROM `0x0806BE38`** (see the entry layout below); `sub_0801DE5C`'s 3 call
sites are OBJ tile loaders (see "There is no missing 4th caller").
Dialog/UI text does **not** go through this dispatcher -- it has its own
separate Huffman scheme, see [`text.md`](text.md).

### Level-table entry layout (offsets confirmed for a 124-byte entry)

These offsets hold **decompressed payloads, not palettes or tilesets**.
Decoding `+0x04` (508 bytes) and `+0x14` (3748 bytes) with the type-6
codec (see below) -- two different entries' worth of data -- both produce
the same recognizable shape: runs of 4 consecutive `u16` values with
small ascending low-10-bit fields and only 2 distinct values in the high
bits across the whole buffer. That's the canonical **GBA BG screen-entry
(tilemap) format** (10-bit tile index + hflip/vflip/palette-bank bits in
the top bits), not pixel or color data. Note that the destination-buffer
access pattern alone (no length header read vs. a leading tile-count
header read) does *not* distinguish a palette/tileset pair from this --
only decoding the payload settles it.

- `+0x04 / +0x14 / +0x24 / +0x34` (and very likely `+0x00/+0x10/+0x20/
  +0x30` too, not individually checked): **BG tilemap/screen-entry
  data**, one per background layer. PROVEN for `+0x04`/`+0x14` (decoded
  and pattern-matched against the known GBA format), STRUCTURAL MATCH by
  inference for the others until each is individually verified.
- The internal "leading count-word" behavior (`count << 5` before
  advancing) is undecoded against a tilemap payload -- it is not a
  tileset tile-count header, since the payload isn't a tileset.
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
bytes, the exact code the game copies into IWRAM at runtime -- see the
dispatcher section above) in the Unicorn CPU emulator, rather than
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

`tools/graphics/decode_type6.py` is now checked into the repo, implementing
exactly this (Unicorn-based execution, mirroring
`tools/krawall/dump_krawall.py`'s CLI style). `unicorn` was added to
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

`val2 = 0xF` (15) and the `resource_ptr + 2` skip strongly suggest this
queued request is a **palette-only upload** -- 15 colors (GBA convention:
OBJ palette index 0 is transparent/unused, so a real palette often only
needs to supply
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
[`text.md`](text.md)'s BIOS wrapper table) -> BIOS vblank
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
*same* generic dispatcher (`sub_0801DE5C`) documented above, which
turns out to also be exercised for
OBJ (sprite) tiles, not only BG/level graphics as first assumed.

### A real, confirmed sprite tile (PROVEN via mGBA debugger)

Same live-debugging technique as the palette flush above, pointed at
OBJ tile VRAM (`0x06010000`, length `0x8000`) instead of palette RAM.
After skipping past the expected boot-time full-VRAM zero-clear (fires
first, `old value == new value == 0`, harmless), a real hit landed with
`LR = 0x0801DEDB`, immediately after a call to `sub_08049EB0` (the
already-known `svc 0x15` / `RLUnCompVram` BIOS wrapper). `LR` falls
inside **`sub_0801DE5C`** -- the same generic resource dispatcher
documented above, whose case-3 branch (RLE)
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

Decoded with a from-scratch RLUnComp implementation
(`tools/graphics/decode_bios.py`, see below), verified byte-for-byte
against a hand-traced decode:

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

#### `0x080BCA24` is NOT the cursor sprite

`0x080BCA24` is a 224-byte (7-tile) RLUnComp resource in the same ROM
neighborhood as the confirmed spark tile (`0x080BCDD8`), found by
scanning for structurally-valid small BIOS resources (try every offset,
keep only ones that decode cleanly to the declared size, score by
tile-adjacency coherence). Rendered in a 3x3-grid-with-hflip layout it
gives a clean, recognizable wand silhouette -- real wand-shaped art, not
coincidence-from-noise -- so it is easy to mistake for the cursor.

It is not: its decoded tiles have **zero byte match** against the wand
data captured live from VRAM (below). Whatever `0x080BCA24` is used for,
it isn't this cursor. Treat it as a worked example of why pixel-shape
plausibility is not evidence without ground truth -- a correct-*looking*
result here was still the wrong resource.

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
pixel content mirrors -- not per-tile-in-place): a genuine, complete
wand -- teal/cyan ornate tip blending into a dark reddish-brown wooden
shaft, tapering to a handle.
**Confirmed correct by the user against the actual running game.**

The live palette bank 2 (the falling particles) is byte-identical to the
statically-extracted ROM palette `0x080BD344` -- an independent live
cross-check of that palette. The wand's own
palette (bank 1) is a new, distinct real palette: warm red/orange
(shared with bank 2's first half) transitioning into cool teals/greens
instead of gold. Its ROM source hasn't been located.

#### Finding the ROM source: the type-4 codec, decoded

No match for the live tile/palette bytes in the ROM raw (uncompressed)
or in any standard BIOS format (LZ77/Huffman/RLE, scanned across the
whole ROM) -- meaning it's compressed with one of the two proprietary
codecs. Rather than guess further, caught it live: breakpointed the
type-4 codec's IWRAM entry point (`0x030028D4`, installed from ROM
`0x08006108` -- see the dispatcher section above) and watched it fire
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
showed it is not a simple byte-token LZSS -- it's halfword-aligned with careful
byte-parity tracking, structurally closer to the type-6 codec than to
a textbook LZSS. **`tools/graphics/decode_type4.py`** therefore works the
same way as `tools/graphics/decode_type6.py`: it executes the real ARM
code via Unicorn rather than hand-porting the logic, which is what a
codec this fiddly needs (cf. the hand-ported RLE decoder below, where a
mid-token cutoff detail silently produced the wrong stream length).

**Verification: `0x080BCBD0` decodes to a 128-byte output that is a
byte-for-byte exact match against all four wand tiles read live from
VRAM.** The codec stops writing at exactly that boundary (everything
past byte 128 in the output buffer is untouched scratch memory) -- not
an assumed cutoff, the real behavior. This is now the strongest
evidence of any finding in this document: independently confirmed via
two different methods (live memory read, and ROM decode) landing on
identical bytes.

**`tools/graphics/decode_bios.py`** (new, checked into the repo): decodes any of
the three standard BIOS formats (LZ77UnComp, HuffUnComp, RLUnComp) from
a ROM address, dispatching on the header's type nibble exactly like the
game's own dispatcher. Unlike `tools/graphics/decode_type6.py` (which had to
reverse-engineer an undocumented proprietary codec by executing real
ROM code in an emulator), these are the public, well-documented GBA
BIOS formats, reimplemented directly from spec -- verified against the
live-confirmed `0x080BCDD8` example above. The RLE decoder specifically
had to be written to stop exactly at the declared byte count even
mid-token (matching real BIOS behavior). Consuming whole literal-run
tokens regardless of remaining size computes the wrong stream length and
corrupts the next-resource offset.

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

**`tools/graphics/find_object_palettes.py`** (new): finds every `bl
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
argument convention to statically walk for tiles yet.

**There is no missing 4th caller.** `grep -c "bl sub_0801DE5C"` against
`build/us/full_disasm.s` gives **exactly 3** static call sites, and no
indirect/literal-pool references to its address exist anywhere else in
the disassembly, so the wand's live-traced call necessarily went through
one of these 3. They are not all level/BG-only:

- `sub_080454BC(objStruct, resourcePtr)` (`0x080454BC`): computes
  `dest = 0x06010000 + tileIndexField(objStruct)*32` and calls
  `sub_0801DE5C(resourcePtr, dest)` -- a **generic single-resource OBJ
  tile loader**, keyed off a tile-index field read from the object
  struct, not level-table data.
- `sub_080454DC(resourcePtr, ...)` (`0x080454DC`): same shape, dest
  computed from an argument rather than an object-struct field.
- `sub_08045588(objStruct, ...)` (`0x08045588`): a **loop** over a
  per-object sub-resource table (entries read at `objStruct[6]`'s
  struct, fields include `w:u8, h:u8` tile-dimensions and a `u16`
  source-blob offset), computing per-entry VRAM destinations
  cumulatively and calling `sub_0801DE5C` once per entry -- i.e. a real,
  generic **multi-tile sprite-sheet loader**, exactly the missing
  "many tiles per object" mechanism.

Both `sub_080454BC` and `sub_080454DC` are called from deep inside
object-update/animation code (`build/us/full_disasm.s` around line 5156/
5183, inside a large unnamed function reading per-object animation-frame
fields) -- not the 124-byte level table at all. This is a genuine,
reusable, generic OBJ tile-loading path, analogous to `sub_08001528` for
palettes, but **the resource pointer's own source within that caller
hasn't been traced back to a literal/statically-walkable form yet** --
unlike the palette path where `sub_08001528`'s `resource_ptr` argument
is always a clean literal at the call site. Doing that trace (find every
caller of `sub_080454BC`/`sub_080454DC`/`sub_08045588`, and where each
one's `resourcePtr` argument ultimately comes from -- likely an
animation-frame table entry, given the surrounding code reads per-frame
struct fields) is the next real unlock for reaching "extract everything"
for tiles -- the calling pattern is found; what's left is tracing its
argument dataflow.

### Item icons (PROVEN, extracted)

`ItemEntry.pPalette/pTileData/pFrameData` (`docs/formats/items.md`'s item
table, `+0x04/+0x08/+0x0C`) is a second, fully statically-walkable instance of
the OBJ tile-loading path described above -- found by decompiling
`FUN_08026bcc` (`0x08026bcc`, called by `FUN_08027384`, an item-spawn
function), which reads exactly these 3 fields and hands them to
`SpawnObject` (`0x08001528`, the same generic pooled-object spawner
documented above) as `resource_ptr`, then to `LoadObjTile`/
`LoadObjTileSheet` (`0x080454BC`/`0x08045588`). Unlike the general case,
every item's `resourcePtr` is a clean literal at its own table entry, so
this closes out "extract everything" for this one resource class
without needing a live trace:

- **`pPalette`: a 32-byte palette.** 2-byte header (unidentified, ignored)
  + 15 BGR555 colors, exactly the `sub_08001528` convention already
  proven above (`resource_ptr + 2` = 15 real colors; index 0 is the GBA
  OBJ transparent color, not stored in the resource).
- **`pFrameData`: a frame/layout header**, the same generic per-object
  animation-frame format `LoadObjTileSheet`/`FUN_080023b4` (renders the
  in-world sprite these items also spawn) read from `objStruct+0xe0`.
  Fixed 12-byte part; `+0x06` is a `u16` frame count (every one of the
  79 real items has exactly 1). One `u16` offset per frame follows at
  `+0x0C`, relative to that same `+0x0C` base, pointing at a small
  record: pixel width (`+0x02`, `u8`), height (`+0x03`, `u8`), and a
  `u16` source offset (`+0x04`) into `pTileData`.
  - Corroborates open thread 1 below (`sub_08045588`'s per-object
    sub-resource table): its `w:u8, h:u8, source-blob-offset:u16`
    fields are exactly what's decoded here, now against 79 real,
    named, concrete instances rather than one traced dataflow guess.
- **`pTileData`: the tile pixel data**, at `pTileData + source_offset`, header
  -prefixed like any generic resource (`byte0`'s nibble = type,
  `byte1..3` LE = decompressed size, matching `width*height/2` exactly
  in all 79 real items -- an independent structural check that the
  frame-header field identities above are right). Two nibbles appear:
  type 3 (BIOS `RLUnComp`, 11 of 79) and type 7 -- `sub_0801DE5C`'s
  *own* nibble for the type-4 proprietary codec (`0x0804a2cc` via the
  `0x030028CC` IWRAM entry), distinct from `sub_0801DD90`'s nibble 4 for
  that same codec (two different dispatchers, two different
  nibble-to-codec mappings, same underlying decoder already proven
  above under "The type-4 codec, decoded"). No other nibble appears
  among the 79 real items.

**Type 3's real stream starts 8 bytes past the outer header, not 4 --
confirmed against raw disassembly, not just decompile.** `sub_0801DE5C`'s
case-3 branch (disassembled directly: `add r0,r3,#0x4` then
`bl sub_08049eb0`, which is a bare `svc 0x15` / `RLUnCompVram` wrapper)
passes the resource address plus 4 straight into the real BIOS RLE
routine -- but that BIOS call needs its *own* self-contained 4-byte
type+size header at whatever address it's given, distinct from the
generic dispatcher header `sub_0801DE5C` already consumed at
`pTileData + source_offset + 0`. Every type-3 icon's data has that same
header duplicated verbatim at `+ 0x4` (`icon_codec.py` asserts this on
every decode, since it's a real invariant of the format, not an
assumption), so the real token stream starts at `+ 0x8`. Skipping only
the outer header (the correct convention for type 7, which has no such
duplicate) is a dead end for type 3: it feeds the duplicate header's
own bytes into the decoder as real tokens, visibly corrupting the
rendered icon while still producing *a* plausible-sized image -- not
something a byte-count or size check catches, only a look at the
rendered PNG.

**Verified by decoding and rendering real ROM data, not just reading
the struct shape**: "Ordinary Belt" (32x32, type-7/type-4 tiles) decodes
to a recognizable belt with a gold buckle; "Antidote to Common Poisons"
(16x32, type-7) decodes to a recognizable potion bottle; "Wiggenweld
Potion" and "Trevor" (both type-3, post-fix) decode to a recognizable
potion bottle and toad respectively. All confirmed by direct visual
inspection of the rendered PNG, matching their item names unambiguously.

**Extraction and packing**: `tools/items/icon_codec.py` implements the
decode (palette + frame-header parsing directly, tile data via
`tools/graphics/decode_bios.py`/`tools/graphics/decode_type4.py`).
`tools/items/extract_item_icons.py` (`just extract-item-icons`, part of
`just extract-all`) verifies all 79 real items' icon data forms one
fully contiguous ROM span with zero gaps between items, in table order
-- confirmed by sorting every `pPalette`/`pTileData`/`pFrameData` address and
checking each one's extent against the next, with the span's end
independently corroborated by `FUN_08026bcc`'s own `id==0x86` literal
(`&DAT_080ac6a0`, the next icon resource: an equip-slot placeholder
outside this table). It then extracts each item's 3 pieces verbatim to
`data/images/items/<Name>.{palette,tiles,frames}.bin` (3 separate
files, not one concatenated blob -- the frame-header's length isn't a
fixed format constant the way the palette's is, and nothing in the
preceding compressed tile data declares its own compressed byte length,
so only the filesystem boundary reliably separates them) and renders
each to a human-viewable `extracted/items/<Name>.png` (gitignored,
never build input -- see the justfile). `regions.us.txt`'s single
`item-icon-data` row claims that whole span as one real, byte-verified
extracted region -- like `item-table` and the Krawall rows, not
anonymous `.incbin` from the baserom -- packed by
`tools/items/pack_item_icons.py`, which just copies each `.bin`'s bytes
back out under a label (`gItemIcon<Name>Palette/Tiles/Frames`). There
is no re-encode step: no type-4 codec encoder exists (only the
Unicorn-executed decoder), so packing is a literal copy-through, not a
transformation -- editing these `.bin` files isn't meaningful, they
exist so this region can be claimed and byte-verified rather than left
as unclaimed `.incbin`. `tools/items/pack_items.py` (the item-table
packer) references those same labels by name instead of packing
literal addresses, so no ROM address is stored in `items.json` or
`data/images/` at all -- only in `regions.us.txt`'s one `item-icon-data`
row. See `docs/formats/items.md` for the JSON shape (`sIconPath`
replacing the 3 raw pointers for real items).

## Open threads

In rough priority order. The palette side of this subsystem is solved
and statically enumerable; **tiles are the remaining gap**, and item 1
is what unlocks them at scale.

1. **Trace `sub_080454BC`/`sub_080454DC`/`sub_08045588`'s callers** (see
   "There is no missing 4th caller" above). These are the real, generic,
   statically-confirmed OBJ tile loaders -- the tile-side analogue of
   `sub_08001528` for palettes. Finding every caller and tracing each
   one's `resourcePtr` argument back to its source (likely an
   animation-frame table, given the surrounding object-update code)
   would let a scanner enumerate real tile resources without running the
   game, the way `tools/graphics/find_object_palettes.py` already does
   for palettes.
2. **The wand's remaining pieces**: its other 3 animation frames
   (`0x080BC9CC`, `0x080BCADC`, `0x080BCCD8` -- mechanically identical
   to the verified `0x080BCBD0`, just not run), and its own palette
   (bank 1), which has no located ROM source. Bank 1 is neither raw nor
   standard-BIOS-compressed, so it is presumably type-4 or type-6 and
   findable by a live breakpoint on whatever writes OBJ palette RAM
   `0x05000220`-`0x0500023F`, reading the source register at entry.
3. **The spark/particle effect's remaining tiles and its palette
   pairing.** One real tile is confirmed (`0x080BCDD8`, via
   `sub_0801DE5C`'s RLE path); it is likely a multi-tile animation like
   the wand's glow. Three real palettes exist (`0x08A38108`,
   `0x08A38FE0`, `0x080BD344`); which one pairs with this effect isn't
   confirmed.
4. **The three structural-scan candidate regions** (`0x08933000`
   filigree tileset, `0x0888xxxx` region, `0x08a36800` UI panels) have
   **no confirmed code reference**. A grep of `build/us/full_disasm.s`
   for PC-relative literal-pool loads of these addresses found zero hits
   for the filigree tileset and the UI-panel region; the `0x0888xxxx`
   region had 3 nearby hits (`0x08882CFC` at disasm lines 15979/20385,
   `0x08886004` at line 16074) that don't match any of the 17
   tile-shaped sub-runs identified there. All three need a code-confirmed
   live trace (OAM/VRAM watchpoint) before being trusted -- a
   literal-pool grep is not enough, and neither is pixel-shape
   plausibility (see `0x080BCA24` under "The wand cursor sprite":
   found by this same technique, in the same ROM neighbourhood, and
   demonstrably not the sprite it resembles). Standard BIOS LZ77 is
   ruled out for the filigree blob specifically -- no valid LZ77 stream
   longer than 100 bytes exists anywhere spanning that region.
5. **The type-4 codec is decoded but barely exercised**
   (`tools/graphics/decode_type4.py`, verified byte-exact against live
   memory). Only tested against the wand's animation frames; no other
   type-4 resource is confirmed anywhere yet.
6. Once more real tile data is paired with a real palette, revisit the
   delta-coded tilemap fields decoded from the level table
   ("Level-table entry layout" above) to see whether they arrange any of
   it into an actual on-screen scene.

The general methodology this subsystem settled on: **live mGBA
breakpoints/watchpoints beat blind ROM scanning whenever a live trigger
is available**, driven interactively through mGBA's built-in debugger
console.
