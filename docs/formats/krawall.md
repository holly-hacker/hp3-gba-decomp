# Krawall audio data format

Status: **PROVEN** for boundaries/addressing (deterministic struct parsing,
zero overlaps across 733 regions in both ROMs, cross-version pattern-data
byte-identity confirmed). Field-level semantics beyond what's needed for
byte-accurate boundaries are not fully decoded yet -- see Open questions.

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

`tools/extract_krawall.py` no longer calls `unkrawerter` at all. It was
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
    unsigned char loop;
    unsigned char hq;
    signed char   data[1];   // PCM sample data follows inline
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
    unsigned char order[256];
    signed char   channelPan[32];
    unsigned char songIndex[64];
    unsigned char volGlobal, initSpeed, initBPM;
    unsigned char flagInstrumentBased, flagLinearSlides, flagVolSlides,
                   flagVolOpt, flagAmigaLimits, ___padding;
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
found these, and `tools/extract_krawall.py`'s `MODULE_ADDRS` for the
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
control byte (`0` terminates the row):
- bit `0x20`: note+instrument follow (2 bytes; +1 more if `note & 0x80` and
  not the old/2003 format -- not applicable to our confirmed version)
- bit `0x40`: volume byte follows
- bit `0x80`: effect+effectop follow (2 bytes)

True pattern length is only knowable by walking this stream to its end
(`rows` iterations of "read follow bytes until 0"). Ported directly in
`extract_krawall.py::pattern_span`.

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

`tools/extract_krawall.py` writes one raw binary file per region to
`asm/krawall/<ver>/...` (gitignored -- this is the game's actual
copyrighted audio content, same footing as `baserom.<ver>.gba`, never
committed) and prints the corresponding manifest rows, which ARE committed
into `regions.<ver>.txt` -- addresses and names are curated knowledge
(confirmed via deterministic parsing) even though the underlying bytes
aren't. `just build` depends on the `extract-krawall` recipe, so the `.bin`
files are regenerated automatically before every build; addresses/names are
deterministic given the same baserom, so the committed manifest rows stay
valid across reruns. `gen_rom_s.py` `.incbin`s a `.bin`-suffixed asm-file
directly (no wrapper `.s` needed) -- see its handling of that extension.

`.xm` export (`just extract-music-xm`) is a completely separate,
non-authoritative path for actually listening to/viewing the music --
lossy (effect remapping, optional pattern-rewriting for playback accuracy),
never touches the build.

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

- [ ] Field-level semantics beyond what's needed for boundaries (effect
      byte meanings, exact `Instrument`/`Envelope` field interpretation)
      aren't decoded -- only enough to compute accurate spans.
- [ ] Whether `krawerter` (Krawall's own `.xm`-to-assembly compiler, in the
      LGPL `krawall` source, not this repo) can reproduce byte-identical
      output from an extracted `.xm` was investigated but never verified --
      moot for now since the build path doesn't use it at all, but would
      matter if this project ever wants real, editable, committed source
      for music (analogous to `asm/rt/`) instead of raw `.incbin`.
- [ ] The "no instrument list" finding is an absence, not a confirmed
      negative -- worth a second look if sample-only playback ever seems
      wrong.

## Future work

Not started, just recorded so the reasoning behind it isn't lost:

1. Let modules be given human-readable names (which `.xm` track they came
   from), with patterns inheriting the parent module's name --
   e.g. `BattleTheme` -> `BattleTheme_Pattern1`.
2. Consider a higher-level storage format instead of raw `.bin` --
   e.g. samples as `.wav` plus a JSON sidecar header.
