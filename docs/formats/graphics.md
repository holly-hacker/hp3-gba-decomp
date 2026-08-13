# Graphics asset format

Status: **PROVEN** for the type-6 codec's decode mechanism (verified by
executing the real ROM code in an emulator, see below) and for one class
of its output (BG tilemap/screen-entry data). **STRUCTURAL MATCH** for
tile data location. **UNCONFIRMED** for palettes, the true tile data the
level table's decoded tilemaps refer to, and (important caveat) the
actual subject matter of any grayscale-rendered content -- everything
rendered with a fake grayscale ramp palette should only be described
structurally, not as depicting specific real-world content. No extractor
is checked into the repo yet.

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

**Not yet in the repo**: a `tools/decode_type6.py` wrapping the
Unicorn-based execution (mirroring `tools/extract_krawall.py`'s style,
callable both as a library function and a CLI) was recommended but not
written/reviewed yet. It would need `unicorn` added as a tool dependency
(e.g. via `pip`/`flake.nix`) -- flagging explicitly since adding a new
dev-shell dependency is a repo-affecting decision, not something to do
silently.

## What's NOT yet known

- **No real palette has been found anywhere.** Automated palette-window
  scanning (16 consecutive bit15=0 halfwords, filtered for color
  diversity/saturation) produced only false positives across the ROM.
  One candidate (`0x08888dc0`) was rendered against tile data and
  produced a uniform-red wash, confirming it's not real. The
  level-table fields that were guessed to be palettes turned out, once
  actually decoded, to be tilemap data instead (see above) -- so the
  "decode type-6 and check the palette fields" plan didn't pan out as
  expected. Where the real palette lives is still open.
- **None of the three candidate art regions (`0x08933000` filigree
  tileset, `0x0888xxxx` region, `0x08a36800` UI panels) have a
  confirmed code reference.** A direct grep of `build/us/full_disasm.s`
  for PC-relative literal-pool loads of these exact addresses found
  **zero** hits for the filigree tileset and the UI-panel region. The
  `0x0888xxxx` region had 3 nearby hits (`0x08882CFC` referenced at
  disasm lines 15979/20385, `0x08886004` at line 16074) but these don't
  exactly match any of the 17 tile-shaped sub-runs identified earlier in
  that region, so they're not confirmed to be the same data -- worth a
  follow-up look, but not proof. This means none of the three regions
  are provably *used* by the game as opposed to unused/leftover
  tile-shaped data; they were found by scanning raw bytes, not by
  tracing from code. A literal-pool grep only catches direct
  `ldr rX, =0x08xxxxxx` loads -- it would miss a pointer computed at
  runtime (e.g. `base + index*stride`, the same pattern the level table
  itself uses), so absence of a hit is suggestive, not conclusive.
- **Tile arrangement for the two tileset-like regions.** No clean
  periodicity was found via autocorrelation on a tile-flatness signature
  across candidate widths 8-64px for the filigree/`0888xxxx` regions --
  consistent with loose tilesets (not a linear framebuffer), meaning a
  separate tilemap/screen-entry array must exist to arrange them. The
  level table's decoded tilemap fields (see above) are a plausible
  source for this, but haven't been matched to either region yet.
- **Type-4 codec** (the LZSS-shaped sibling of type-6) is still only
  structurally characterized, not decoded/verified -- lower priority
  since no confirmed real resource has been found using it yet.
- Standard BIOS LZ77 was explicitly ruled out as the compression for the
  confirmed tile blob (`/tmp/hp3gfx/lz77.py`, an independent decoder: no
  valid LZ77 stream of length >100 bytes found anywhere spanning that
  region).

## Recommended next steps

1. **Land the type-6 decoder as a real repo tool** (`tools/decode_type6.py`,
   Unicorn-based, mirroring `tools/extract_krawall.py`'s style). Needs
   `unicorn` added as a dev-shell dependency -- flag for review before
   touching `flake.nix`.
2. **Trace forward from a decompression call site to its VRAM DMA/CpuSet
   copy.** All observed decompression destinations are EWRAM heap
   buffers, not VRAM -- the actual VRAM upload happens later, untraced.
   Finding that copy would give a real VRAM palette/tile address, useful
   for working backward to the true ROM palette source now that the
   level-table palette guess is known to be wrong.
3. **Connect the three candidate art regions to actual game code.**
   Static literal-pool search came up empty (see above). Next step would
   be dynamic analysis (breakpoint/watch on VRAM writes during actual
   gameplay in mGBA) -- note `CLAUDE.md` already documents this exact
   technique being unreliable when tried for Krawall function ID
   (flaky breakpoint/continue sequencing, root cause never found), so
   this is higher-risk/lower-confidence than steps 1-2.

## Confidence key

Same convention as the rest of `docs/`, see `docs/memory-map/krawall.md`:
**PROVEN** (directly verifiable), **STRUCTURAL MATCH** (shape/behavior
matches strongly but not byte-verified against a spec), **UNCONFIRMED**
(plausible, no independent corroboration yet).
