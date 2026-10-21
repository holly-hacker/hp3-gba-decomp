# Krawall audio data format

The data structs are in `include/3rd_party/krawall/mtypes.h`, and
`3rd_party/krawall/player.c` reads them. This ROM's Krawall revision
(2003-09-01) differs from the public `krawerter` in two ways: `Pattern.rows`
is one byte, and a note and its instrument are packed into one big-endian
word, `note << 9 | instrument`.

## Layout in ROM

The US and JP data is the same apart from pointers. Each ROM has a
278-entry sample list followed by the samples, all in one contiguous run,
and 52 modules. Each module's patterns come right before its header, and no
pattern is shared between modules. `MODULE_ADDRS` in
`tools/krawall/dump_krawall.py` lists the modules.

The original `krawerter` output also contains:

- after each sample's PCM, a 69-byte overrun buffer (`SAMPLES_ADD`). It is
  filled with `0x80` for a non-looping sample, a copy of the data from the
  loop point for a forward loop, or the PCM mirrored from its end for a
  ping-pong loop. Zero padding then aligns the next sample to 4 bytes.
- zero padding after each pattern, up to a 4-byte boundary.
- `Sample.size`, which holds the address where the PCM ends (before the
  overrun buffer), not a byte count.
- `Module.songIndex`, derived from `order`. Each position after a `254`
  skip marker is recorded in turn, starting at index 1.
- three zero bytes at the end of the module header.
- PCM stored unsigned (`128` = silence), which is WAV's 8-bit convention.
- `Sample.hq`, set when the source WAV's filename began with `~`. It is
  kept as an opaque flag.

## Build source

`extract-krawall` writes the ignored `data/audio/` from the US ROM, and
`pack-krawall` turns it into assembly for each version's `krawall-module`
and `krawall-samples` rows. The fields that are derived or always zero
(`songIndex`, the header padding, the overrun buffers) are not stored.

- `modules/<Name>.json` holds a module's header fields, `order` (`null` for
  the 254 marker) and its patterns inline. A pattern row is a sparse list of
  `{channel, note?, instrument?, volume?, effect?, effectop?}`. `note` is
  1-96 or `"off"`, and `instrument` is a sample name.
- `samples/<Name>.json` and `<Name>.wav` hold one sample. `index` is the
  sample's 0-based position in the sample list and sets the pack order. The
  WAV is mono 8-bit at `c2Freq`, with the ROM's bytes stored unchanged.

`krawall_names.txt` overrides the default `Module<N>`/`Sample<N>` names, and
`extract-krawall` applies it. Rename the matching manifest rows by hand. If
an entry is renamed a second time, the file with its previous custom name is
left behind.

## unkrawerter

`dump-music-xm` exports `.xm` files with `unkrawerter -k`. The `-K` option
misreads this revision. The export is lossy and is not used by the build.
`unkrawerter`'s scan misses the 21 modules that have fewer than four
patterns. `-t 1` would find them, but it crashes on the JP ROM.
