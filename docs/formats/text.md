# Dialog/UI text format

The decoder is `DecompressDialogText` (`src/huffman/`). The blob layout and
the tree construction that reproduces the shipped trees are documented in
`tools/text/text_codec.py`. Its `CHARMAP` holds the glyph codes. US/EU has
one blob for each of eight languages, and JP has a single Japanese blob.
`extract-text` writes them to the ignored `data/text/<lang>.json`, and
`pack-text` rebuilds them byte for byte.

## Charmap

The US/EU charmap was derived from content. Credits names repeated verbatim
(`Hernández`, `Gómez`, `Börjel`, `Vallée`) pin several codes, and the grammar
of each language pins the rest. The accented run `0x9B`-`0xB5` follows
Latin-1's letter order, renumbered densely. `0x7B`-`0x7E` are repurposed as
`©`, `œ`, `¡`, `¿`, so the plain-ASCII passthrough stops at `0x7A`.

No shipped string uses a two-byte (`> 0xEF`) glyph code.

## Unconfirmed

- `0xB9` (trademark) and `0xBB` (registered) are told apart by usage
  alone. `0xB9` follows EA's marks and `0xBB` follows "Game Boy" and
  "Game Link".
- The JP charmap is not decoded. `ja.json` stores each code raw
  (`U+E000 + code`).
- The tree builder's dummy symbol `0x100` is a leaf during construction,
  but the decoder reads it as the root. No shipped string reaches it, so
  its purpose is unknown. The authoring tool's behavior on edge cases that
  the shipped data doesn't cover (for example a maximum count exactly
  divisible by 255) is also unknown.
