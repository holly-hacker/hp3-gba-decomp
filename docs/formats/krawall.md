# Krawall audio data format

Status: **PROVEN** for boundaries/addressing (deterministic struct parsing,
zero overlaps across 733 regions in both ROMs, cross-version pattern-data
byte-identity confirmed) and now also **PROVEN** for pattern-atom and
module-header field semantics (see Pattern atom encoding and Module header
fields below) -- verified against every atom in all 402 patterns and every
module in both ROMs, not just spans. Remaining unknowns are narrower --
see Open questions.

## Discovery

`unkrawerter` (`MCJack123/UnkrawerterGBA`, pinned in `flake.nix`) locates
candidate structures via a pure data-pattern scan: it
scans the ROM for runs of plausible `0x08xxxxxx`/`0x09xxxxxx` pointers, then
classifies each run as a module/sample/instrument list by dereferencing and
checking the target bytes against the struct shapes below. It does **not**
look at code/instructions at all -- no function signatures were found or
usable from it. This heuristic misses any module whose own pattern-pointer
run is shorter than its match threshold (default 4) -- see "Modules
unkrawerter's heuristic misses" below.

Krawall version matters: our confirmed CVS revision is `2003/09/01` (see
`docs/compiler.md`), which matches `unkrawerter -k` (forces version
`0x20030901`, the pre-2004-07-07 struct layout with a 1-byte pattern row
count). The other option, `-K` (`0x20050421`), uses a 2-byte row count and
will silently misparse this ROM -- always use `-k`.

`tools/krawall/extract_krawall.py` no longer calls `unkrawerter` at all. It was
used early on for the coarse discovery pass (sample-list/module addresses,
scraped from its stdout), with exact byte spans always computed separately
in pure Python (ported from `unkrawerter.cpp`'s
`readSampleFile`/`readModuleFile`/`readPatternFile`). Once discovery was
complete for both ROMs, the confirmed addresses were hardcoded directly
into the script (`SAMPLE_LIST`/`MODULE_ADDRS`) and the heuristic-scan step
was deleted -- the donor ROMs are fixed, pinned binaries (hard rule 1), so
there's nothing left for a scan to adapt to on later runs; hardcoding what's
already been confirmed is simpler and more honest than re-deriving it. See
"Modules unkrawerter's heuristic misses" for how the last 21 module
addresses per ROM were found (`unkrawerter` itself is still used directly,
outside this script, by `just extract-music-xm` for casual `.xm` exports).

Cross-checked against `sebknzl/krawall`'s `krawerter/` (the original
`.xm`-to-assembly compiler) for how it emits these structs -- but per the
compiler-fingerprinting caveat above, that public repo is a *later*
revision than what's embedded in this ROM (e.g. its `Mod.cpp` emits the
pattern `rows` field as `.short`, 2 bytes, unconditionally -- not the
1-byte field our `-k`/pre-2004-07-07 parsing assumes). Where the two
disagree, our own zero-overlap/zero-mismatch validation against the actual
ROM bytes (see Confirmed stats and Trailing padding absorption) is what's
trusted, not the public source -- it's used for API-shape/algorithm
reference only, per `CLAUDE.md`.

This matters beyond spans, too: `Pattern.cpp::compress()`'s *active* code
path (byte-per-field: separate note byte, separate instrument byte, with
an optional 3rd byte when `instrument > 255`) is the **later** revision's
encoding, not ours -- confirmed by decoding real ROM bytes that way and
finding the "note" byte's top bit set on a large, semantically nonsensical
fraction of atoms. The same file has an *unused, commented-out* alternate
encoding right next to it (a packed 16-bit word: `note_word = (note &
0x7f) << 9 | (instrument & 0x1ff)`), which is what our confirmed
2003-09-01 revision actually emits -- see Pattern atom encoding below.
`unkrawerter.cpp`'s reader is byte-count-correct for our revision either
way (its `use2003format` gate matches how many bytes to consume), which is
why span/boundary validation never caught this; only decoding actual
field *values* and checking they're sane did.

## Struct layouts (packed, little-endian)

```c
typedef struct PACKED {
    uint32_t  loopLength;
    uint32_t  size;          // see "size field" below -- NOT a byte count
    uint32_t  c2Freq;
    signed char   fineTune;
    signed char   relativeNote;
    unsigned char volDefault;
    signed char   panDefault;
    unsigned char loop;       // 0 = none, 1 = forward loop, 2 = ping-pong
    unsigned char hq;         // see "hq flag" below -- authoring artifact,
                               // not a runtime format property
    signed char   data[1];   // PCM sample data follows inline -- despite the
                              // C type, actual bytes are offset-binary
                              // (128=silence), confirmed empirically, see
                              // "data/audio/samples" below
} Sample;                     // 18-byte header + PCM

typedef struct PACKED {
    unsigned short samples[96];  // note -> sample index map
    Envelope envVol;              // 12 EnvNode{coord,inc} + max/sus/loopStart/flags = 52 bytes
    Envelope envPan;               // same, 52 bytes
    unsigned short volFade;
    unsigned char vibType, vibSweep, vibDepth, vibRate;
} Instrument;                 // 302 bytes fixed

typedef struct PACKED {
    unsigned short index[16];  // jump table: index[n] = byte offset into
                                // data[] of row 4*n, for rows 0,4,8...60 --
                                // lets playback seek without decoding from
                                // the start (see krawerter's Mod.cpp: only
                                // the first 16 of a 64-entry table are ever
                                // emitted, one per 4 rows, matching the
                                // format's 64-row-per-pattern ceiling)
    unsigned char  rows;       // 1 byte if Krawall < 0x20040707 (us), else 2
    unsigned char  data[1];    // compressed row stream, variable length
} Pattern;                    // 32-byte header (index[16]) + rows-field + data

typedef struct PACKED {
    unsigned char channels;
    unsigned char numOrders;
    unsigned char songRestart;
    unsigned char order[256];    // pattern index per song position;
                                  // 254 = skip marker (see Module header
                                  // fields below); only order[0..numOrders)
                                  // meaningful, rest zero-padded
    signed char   channelPan[32]; // only channelPan[0..channels) meaningful
    unsigned char songIndex[64];  // DERIVED from order[], not authored --
                                   // see Module header fields below
    unsigned char volGlobal, initSpeed, initBPM;
    unsigned char flagInstrumentBased, flagLinearSlides, flagVolSlides;
    unsigned char ___unused0, ___unused1, ___unused2;  // always 0 in every
                                  // module emitted by krawerter's
                                  // outputFile() -- not real flags (earlier
                                  // guessed names flagVolOpt/flagAmigaLimits
                                  // retracted, see Module header fields)
    const Pattern* patterns[1];  // variable-length, one ptr per pattern used
} Module;                     // 364-byte fixed header + 4 bytes/pattern
```

## Layout in ROM

- One global **sample list**: flat array of 4-byte ROM pointers to `Sample`
  structs. Our US/JP ROMs: 278 samples.
- No **instrument list** was found in either ROM -- `Module.flagInstrumentBased`
  suggests this game plays samples directly (S3M-style), not through
  instrument envelope mapping. Not fully confirmed; just an absence, not
  actively verified as "correctly absent."
- Each **module** (song) is its own 364-byte header immediately followed by
  a variable-length array of pattern pointers. Our ROMs: 52 modules each
  (see "Modules unkrawerter's heuristic misses" for where the last 21 came
  from -- 31 is what `unkrawerter` itself finds).
- **Patterns are NOT colocated with their module** -- they live in a
  separate region of the ROM, addressed only via the module's pointer
  array (except for the 21 modules described below, whose patterns
  precede rather than follow them, but are otherwise addressed the same
  way). 402 unique patterns across both ROMs, each owned by exactly one
  module -- checked directly by counting every pattern-pointer reference
  across all 52 modules' pointer tables: 402 references, 402 unique
  addresses, zero collisions. Patterns are NOT shared/reused across
  modules in this game (an earlier version of this doc claimed otherwise;
  that was wrong -- `extract_krawall.py`'s `seen_patterns` dict-based dedup
  is a no-op safety net in practice, not something that ever actually
  triggers here).

## Modules unkrawerter's heuristic misses

`unkrawerter`'s discovery only recognizes a module by seeing its
`patterns[]` array as a run of at least `-t`/threshold (default 4)
consecutive ROM-pointer dwords immediately after a header-shaped preamble.
21 modules per ROM fail that in two ways at once: they only have 1-3
patterns (below the default threshold), and -- per krawerter's
`Mod.cpp::outputFile()` -- a module writes its own patterns *before* its
header, ending the header with a pointer table that points backward at
them, so there's no forward-pointing pointer run at a module's start
address to find in the first place; only modules with enough patterns to
need their own dedicated storage break that pattern (no pun intended) and
get a separate forward-referenced pattern block, which is what
`unkrawerter`'s scan actually locates.

Lowering the threshold (`-t`) surfaces some of them (`-t 2`/`-t 3` find
the 2-3-pattern ones without incident), but `-t 1` -- needed for the
1-pattern ones -- **segfaults on the JP ROM** partway through its scan and
is not usable. All 21 addresses per ROM were instead found by direct
structural validation: starting right after each already-known module's
end address, checking whether a well-formed `[pattern...][364-byte
header+pointer table]` chain starts there (rows ≤ 64, valid ROM pointers,
plausible channel/order counts), and confirming the chain tiles the
*entire* remaining gap with zero leftover bytes -- proven exactly, in both
ROMs, at four addresses each (see git history for the working session that
found these, and `tools/krawall/extract_krawall.py`'s `MODULE_ADDRS` for the
addresses themselves).

### Sample size field

`Sample.size` (offset +4) does not store a byte count. Per krawerter's
`Sample.cpp` `output()`, it's written as the address of the `Lsample{i}_end`
label -- i.e. the address right after this sample's own real PCM data ends,
*before* its trailing overrun buffer (see Trailing padding absorption). A
sample's true PCM span is `(size_field & 0x1FFFFFF) - this_addr`. Confirmed
working across all 278 samples in both ROMs (zero overlaps).

### Pattern size

Not stored anywhere explicit. `data[]` is a compressed per-row stream:
each row is a sequence of channel entries, each starting with a `follow`
control byte (`0` terminates the row). The low bits of `follow` are the
channel column index; the high bits say which fields come next:
- bit `0x20`: note+instrument follow (2 bytes, see Pattern atom encoding --
  never a 3rd byte in our confirmed revision, verified against
  `unkrawerter.cpp`'s `use2003format`-gated reader)
- bit `0x40`: volume byte follows (1 byte, raw)
- bit `0x80`: effect+effectop follow (2 bytes, raw -- see Effect values)

True pattern length is only knowable by walking this stream to its end
(`rows` iterations of "read follow bytes until 0"). Ported directly in
`extract_krawall.py::pattern_span`.

### Pattern atom encoding (note/instrument)

**PROVEN** -- decoded and sanity-checked against all 402 patterns / 30,566
note+instrument atoms in the US ROM (every value lands in range, zero
anomalies). The 2 bytes following a `0x20` `follow` bit are **one packed
16-bit big-endian word**, not two independent byte fields:

```
word = (byte1 << 8) | byte2
note       = word >> 9        // 7 bits: 1-96 = XM note, 127 = note-off/cut, 0 = none
instrument = word & 0x1FF     // 9 bits: 1-based sample index (0 = no change), 0-511 range
```

This is `Pattern.cpp::compress()`'s *commented-out* alternate encoding
(sitting right next to the active, byte-per-field code that the current
public `krawall` repo actually uses) -- our confirmed 2003-09-01 revision
emits this older packed form instead. Confirmed by decoding every atom in
the US ROM this way: notes cluster sanely across 19-92 (real XM note
range) with 3,753 occurrences of exactly `127`, matching `ModXM.cpp`'s
confirmed note-off remap (`if (note==97) note=127`); instruments range
0-278, exactly matching the ROM's real sample count, with `0` (no
instrument change) the single most common value. No atom decodes outside
sane range. `Mod::countReferences()` confirms `instrument - 1` indexes
directly into the sample array when `flagInstrumentBased` is false (our
case, per "No instrument list" above) -- so `instrument` is a plain,
1-based sample reference, not indirected through anything.

The active byte-per-field encoding (separate note byte + instrument byte +
optional 3rd byte when `instrument > 255`) is the *later* krawerter
revision's format and does **not** apply to this ROM -- decoding our real
bytes that way produces a nonsensical, frequently-set "note high bit" with
no format-level meaning. Not currently load-bearing for `extract_krawall.py`
(span math only needs the byte *count*, which both encodings agree on: 2
bytes, no extension), but load-bearing for any future work that decodes or
regenerates pattern *content* (e.g. the JSON module/pattern format).

### Effect values

`effect` is a 1-byte enum (not a raw XM/S3M effect letter) with `effectop`
as its 1-byte operand; 50 named constants are given in `krawall/krawerter/
effects.h` (`EFF_SPEED`, `EFF_PORTA_UP_XM`, `EFF_RETRIG`, `EFF_NOTE_CUT`,
etc). Not yet cross-checked against real ROM `effect` byte values (only
note/instrument were verified this pass) -- treat the enum *values* as a
naming reference, not yet confirmed to match this ROM's revision the way
the note/instrument decode above was.

### Module header fields

**PROVEN**, from `Mod.cpp`'s `outputFile()`/`optimizePatterns()`:

- **`order[]` sentinel**: `254` marks a skip/empty position.
  `optimizePatterns()` actually treats `order[i] >= 254` as sentinel (not
  just `== 254`), so `255` is presumably also reserved (standard XM
  end-of-song marker), even though it was never observed in either ROM's
  real order lists (only `254` occurs -- checked directly across all 52 US
  modules). `extract_krawall.py::module_header_span`'s `max_pattern`
  computation currently only excludes `== 254`; harmless today since `255`
  never appears in practice, but worth guarding as `< 254` if this is ever
  revisited, since a stray `255` would currently be mistaken for a real
  pattern index.
- **`songIndex[64]`** is *derived*, not independently authored: walk
  `order[]`; every position immediately following a `254` marker gets
  recorded into `songIndex[1]`, `songIndex[2]`, ... in order (index `0`
  implicitly means "start of song" at order position 0). This lets game
  code jump to sub-song boundaries (e.g. an intro/loop split, or multiple
  jingles bundled into one module) without re-scanning `order[]`. Fully
  regenerable from `order[]` alone -- doesn't need independent storage in
  an editable format.
- **Trailing 3 header bytes** (previously guessed as `flagVolOpt`/
  `flagAmigaLimits`/padding): `outputFile()` emits these as a literal
  `0, 0, 0` unconditionally. Only `flagInstrumentBased`, `flagLinearSlides`,
  and `flagFastVolSlides` (our struct's `flagVolSlides`) are ever real,
  non-zero flags for this format.
- **`hq` flag** (`Sample` struct, not `Module`): `hq = (fileName[0] == '~')
  ? 1 : 0` in `Sample.cpp::output()` -- a source-WAV-filename convention
  from the original authoring pipeline, not a decodable runtime property.
  No way to recover its original semantic meaning from ROM bytes alone;
  round-trip it as an opaque bool.

### Module header+pointer-table size

`364 + 4 * (highest pattern index referenced in order[], + 1)`. The pointer
array's actual *content* (where each pattern lives) is elsewhere in ROM;
this size only covers the module's own fixed header and its own pointer
table, not the patterns themselves (those are separate, deduplicated
regions, since multiple modules can reference the same pattern).

## Confirmed stats (both ROMs, `-k` version)

- 733 regions each (1 sample list + 278 samples + 52 module headers + 402
  patterns), zero overlaps detected, zero unexplained gaps -- every byte
  of Krawall data in both ROMs is accounted for.
- 2,763,052 bytes total each (~16% of the 16MB ROM) -- includes the absorbed
  trailing padding described below.
- All 402 pattern regions are **byte-identical between US and JP** --
  confirms genuinely shared music content, not coincidence. Module headers
  and samples differ only in pointer-valued fields (which correctly reflect
  each version's own relocated addresses), not underlying content.

## Build integration

**Superseded the old raw-`.bin` model** (kept below, in "Old model", for
context) with a curated, editable JSON+WAV format under `data/audio/`.
This exists to support a future moddable build (add/remove/edit tracks),
which raw opaque binary can't. Per hard rule 2, `data/audio/` is
**gitignored, same footing as the baserom, never committed**. Bootstrap
it locally with `tools/krawall/krawall_migrate.py` before building -- see below.

- **`data/audio/modules/<Name>.json`**: one module (song) plus its own
  patterns inlined (patterns are never shared between modules in this
  game, confirmed above, so no separate pattern files/references are
  needed). Fields: `channels`, `songRestart`, `volGlobal`, `initSpeed`,
  `initBPM`, the three real flags (`flagInstrumentBased`,
  `flagLinearSlides`, `flagFastVolSlides`), `channelPan` (array, length
  `channels`), `order` (array, `null` for the `254` skip marker), and
  `patterns` (array, index `i` = the pattern `order` refers to as `i`).
  Not stored: `songIndex` (derived from `order`, see Module header fields)
  and the trailing 3 always-zero header bytes. Each pattern is
  `{"rows": [...]}`, one entry per row, each row a sparse list of
  `{channel, note?, instrument?, volume?, effect?, effectop?}` -- `note`
  is `1-96` or `"off"`; `instrument` is a **sample name string**
  (resolved to a 1-based index at pack time); fields are omitted when
  absent, matching the sparse `follow`-byte format.
- **`data/audio/samples/<Name>.json` + `<Name>.wav`**: `loopLength`,
  `c2Freq`, `fineTune`, `relativeNote`, `volDefault`, `panDefault`,
  `loop` (`"none"`/`"forward"`/`"pingpong"`), `hq` (opaque bool, see
  Module header fields), and **`index`** -- the sample's 0-based position
  in the ROM's global sample list, i.e. what `instrument` (minus one)
  resolves to. This is the *authoritative* ordering `pack_krawall.py`
  packs samples in (and thus each sample's real instrument-index/pointer-
  table position) -- not the filename, since names are user-renamable
  (see Future work) and needn't stay numeric or sorted. Every sample's
  `index` must together cover exactly `0..count-1` with no gaps/dupes.
  PCM as a **standard playable WAV**, not raw
  headerless PCM -- mono, **8-bit**, sample rate = `c2Freq`.
  **Despite the struct field being C-declared `signed char data[1]`, the
  actual stored bytes are offset-binary (128 = silence/zero-crossing, not
  0)** -- confirmed empirically, not assumed: reading raw ROM bytes as
  unsigned gives a 5-9x smoother waveform (far smaller consecutive-sample
  deltas, checked across several samples) than reading them as two's
  complement signed. This is *exactly* WAV's own native 8-bit PCM
  convention (unsigned, 128=silence), so the raw bytes go in/out as-is, no
  transform at all -- confirmed round-trip byte-identical against the ROM
  via both `tools/krawall/pack_krawall.py`'s own decoder and independently via
  `ffmpeg`. (An earlier revision of this format stored 16-bit instead, on
  the theory that some players mishandle 8-bit WAV's unsigned convention
  -- dropped for lack of a real source backing that claim; 8-bit is
  spec-compliant and halves the local disk footprint.) See
  `tools/krawall/krawall_migrate.py`/`tools/krawall/pack_krawall.py`.
- Sample **index** (the 1-based number patterns reference via
  `instrument`, before name resolution) comes from each sample JSON's own
  `index` field (0-based there), not the filename -- see above. Patterns
  reference samples by *name*, so renaming a sample (see Future work)
  doesn't require touching any pattern.
- `regions.<ver>.txt` uses two directives instead of per-pattern/
  per-sample/per-module rows: `krawall-module <start> <end> <json-file>
  <name>` (one row per module -- covers that module's own patterns, which
  are contiguous and immediately precede its header) and `krawall-samples
  <start> <end> <dir> <name>` (one row for the *entire* sample set --
  confirmed to be one contiguous run together with the pointer list, see
  Confirmed stats). `tools/krawall/gen_krawall_regions.py <ver>` computes these
  rows from the baserom and re-verifies both contiguity assumptions,
  refusing to emit if a future baserom's layout doesn't match.
- `tools/krawall/pack_krawall.py <ver>` (the `pack-krawall` recipe, which `just
  build` depends on) reads `data/audio/` plus those manifest rows and
  writes real assembly -- not raw bytes -- to `build/<ver>/audio/...`
  (gitignored, like the rest of `build/`): real labels at the right
  addresses (e.g. `Module0`, `Sample12`), with pointer fields (a module's
  pattern table, the sample size field's copy of the address after
  `Lsample_end`, the sample list) emitted as `.word <label>` and resolved
  by the normal linker step, not precomputed. This means a matched game
  function can eventually reference `Module0`/`Sample12` directly like
  any other extracted symbol, and mirrors how `krawerter` itself emitted
  `.S` text rather than raw binary. `tools/krawall/krawall_codec.py` holds the
  shared encode/decode logic (pattern row compression, `songIndex`
  derivation, sample trailing-buffer generation) used by both the packer
  and the one-time `tools/krawall/krawall_migrate.py` bootstrap script (ROM ->
  `data/audio/`, US only -- content is version-independent, see Confirmed
  stats). Round-trip verified: both US and JP rebuild byte-identical to
  their donor ROMs from this JSON, sourced from the US ROM alone.

### Old model (superseded)

`tools/krawall/extract_krawall.py` still exists (discovery/debugging aid only,
not part of the build) -- it writes one raw binary file per region to
`asm/krawall/<ver>/...` (gitignored -- game's actual copyrighted content)
and prints the old per-pattern/per-sample/per-module manifest rows. Useful
for diffing against `pack_krawall.py`'s output while touching
`tools/krawall/krawall_codec.py`.

`.xm` export (`just extract-music-xm`) is a completely separate,
non-authoritative path for actually listening to/viewing the music --
lossy (effect remapping, optional pattern-rewriting for playback accuracy),
never touches the build, and still reads the baserom directly rather than
`data/audio/`.

### Trailing padding absorption

Both samples and patterns are followed by a small run of bytes before the
next region starts that the struct-parsing math above doesn't account for.
Confirmed by reading `sebknzl/krawall`'s `krawerter/Sample.cpp` and
`Pattern.cpp` (see the version caveat above -- this only needed to explain
mechanism/shape, not exact bytes, so the revision mismatch doesn't matter
here) and then verifying byte-for-byte against both ROMs:

- **Samples**: krawerter appends a fixed `SAMPLES_ADD = 17*4+1 = 69` byte
  overrun buffer after the real PCM data -- its own comment: "the max inc
  in the mixer can be (rounded up) 17 and we go 4 samples over the end in
  the worst case, +1 for interpolation". The fill content depends on
  `Sample.loop`: constant `0x80` if non-looping, a copy of the data
  starting at the loop point if forward-looping, or the PCM mirrored from
  its end if ping-pong looping. Verified exactly (not just size, full byte
  content per the loop-mode formula) against all 278 samples in both ROMs,
  zero mismatches. The observed 69-72 byte gap is this fixed 69-byte buffer
  plus 0-3 bytes of `.align`-driven padding before the next 4-byte-aligned
  struct.
- **Patterns**: krawerter emits `.align` (GNU `as`, effectively 4-byte on
  this target) before every `Pattern` label. Verified the 0-3 byte gap
  after every one of the 402 patterns in both ROMs is all-zero, consistent
  with `.align`'s default zero-fill.

`find_regions` computes each region's end directly from this: pattern end
= `align4(addr + span)`, sample end = `align4(addr + span + SAMPLES_ADD)`
(`SAMPLES_ADD = 69`). No heuristic threshold -- these are exact formulas
derived from the krawerter mechanism above, and `find_regions` asserts
(refusing to generate otherwise) that every sample/pattern region's
computed end lands exactly on the next region's start in both ROMs. This
is a hard invariant check, not an absorption guess: if a future baserom
version's layout doesn't match, generation fails loudly instead of quietly
leaving a fallback `.incbin` gap. The much larger unclaimed gaps after some
module headers (see below) are unrelated and left alone -- they're not
sample/pattern trailing padding at all.

## Open questions

- [ ] `effect`/`effectop` values (see Effect values) aren't cross-checked
      against real ROM bytes yet -- only note/instrument were decoded and
      verified this pass. `Instrument`/`Envelope` field interpretation is
      also still undecoded (moot while "no instrument list" holds, see
      below).
- [ ] Whether `krawerter` (Krawall's own `.xm`-to-assembly compiler, in the
      LGPL `krawall` source, not this repo) can reproduce byte-identical
      output from an extracted `.xm` was investigated but never verified --
      moot for now since the build path doesn't use it at all, but would
      matter if this project ever wants real, editable, committed source
      for music (analogous to `asm/rt/`) instead of raw `.incbin`.
- [ ] The "no instrument list" finding is an absence, not a confirmed
      negative -- worth a second look if sample-only playback ever seems
      wrong.
- [ ] `order[]` value `255` (see Module header fields) has never been
      observed in either ROM -- `module_header_span`'s `!= 254` check is a
      latent gap (should be `< 254`) but not yet known to matter in
      practice.
- [ ] **The `PlaySoundById` message-id -> sample lookup tables aren't fully
      bounded yet.** `PlaySoundById` (US `0x0803FC68`, see
      `../formats/object_script.md`) resolves a `stringId` through a 4-byte
      config-row table at `0x08FB09F8` (`mode`, `resourceIndex`), then:
      `mode == 1` looks up a 4-byte `(sampleIndex, param)` record in a table
      at `0x08FB0588`; `mode == 2` rolls `Mt19937RandMax2(7)` to pick one of
      several 4-byte variant records (32-byte stride per `resourceIndex`
      row) in a table at `0x08FB0818`. Either way, `sampleIndex` indexes
      `g_apKrawallSamples` (`0x08D229F4`, `void*[278]`, already typed in
      Ghidra -- confirmed exactly 278 entries, matching "Confirmed stats"
      below). The `0x08FB0588` table's real row count is unknown -- reading
      its first 32 rows shows coherent, sensible data (small sample
      indices paired with round hex params like `0x2000`/`0x3000`/`0x4000`,
      plausibly a fixed-point volume/pitch scalar), so it's real, not
      garbage, but its only known bound is that it must end before
      `0x08FB0DB0` (`kramInstall`'s copied-to-IWRAM driver source, already
      proven separately) -- the row count implied by the gap to
      `0x08FB0818` (164) is not reliable, since a table of that size would
      itself overlap `kramInstall`'s source. Needs either a bounds-check
      constant found in the reading code or a real sentinel value in the
      table itself before either table's true extent can be marked in
      Ghidra.

## Future work

Not started, just recorded so the reasoning behind it isn't lost:

1. **Done**: modules and samples can be given human-readable names (which
   `.xm` track/instrument they came from) via a shared `krawall_names.txt`
   at the repo root (`<module|sample> <index> <Name>` lines,
   version-independent -- see `krawall_codec.py`'s `load_krawall_names`/
   `resolve_names`). `tools/krawall/krawall_migrate.py` picks it up on re-run,
   using the custom name for the `.json`/`.wav` filenames and (for
   samples) the name patterns reference via `instrument`; it also removes
   the superseded default-named `Module<N>`/`Sample<N>` file(s) from a
   prior run. `tools/krawall/gen_krawall_regions.py` resolves module names the
   same way, so its output rows can be spliced into `regions.<ver>.txt`
   to match. Not automated: renaming *again* (custom name -> a different
   custom name) doesn't clean up the now-stale previous name -- delete it
   by hand; a dedicated rename helper that also patches
   `regions.<ver>.txt` in place would close this. Names must be valid
   assembler identifiers (letters/digits/underscore, not starting with a
   digit) since `pack_krawall.py` emits them as real labels.
2. **Done**: the raw `.bin` extraction under `asm/krawall/` is replaced by
   the curated, editable JSON+WAV format under `data/audio/`, packed back
   to byte-identical ROM bytes at build time -- see Build integration.
   Both US and JP verified byte-identical against their donor ROMs.
3. `effect`/`effectop` values aren't decoded to symbolic names yet (see
   Open questions) -- would make pattern JSON more readable.
4. Once the `PlaySoundById` lookup tables (`0x08FB09F8`/`0x08FB0588`/
   `0x08FB0818`, see Open questions) and `g_apKrawallSamples` are fully
   bounded, they're real curated game content (a message/event ->
   sound-effect mapping) and should move to `data/audio/` under the same
   curated, editable, gitignored model as modules/samples, packed back to
   byte-identical bytes at build time -- not left as permanent raw
   `.incbin`, per the project's general extraction convention.
