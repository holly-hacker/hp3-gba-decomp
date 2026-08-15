@ Named RAM/ROM addresses referenced (via `ldr rX, =SYMBOL`-style
@ literal-pool loads) from asm/*.s files, so the source reads by
@ meaning rather than raw hex. Assembles to identical bytes either way
@ (.set defines a plain absolute constant) -- purely a readability aid,
@ not something the build depends on for correctness.
@
@ US-side values. Symbols also used from a JP-side extracted file (the
@ MT19937 ones below) have a matching, differently-valued definition in
@ ram_symbols.jp.inc -- that's what lets the identical .s source in
@ e.g. asm/rng/mt19937_regenerate.s assemble correctly for both ROMs.
@ The dialog-text-engine symbols have no JP counterpart at all (that
@ engine isn't present in the JP ROM -- see docs/formats/text.md).

@ --- Dialog/UI text engine (US only) ---
.set gCurrentLanguage,       0x03005D0C  @ byte: language ID (0-7) set by SetLanguage
.set gLocaleThousandsSep,    0x03005D0D  @ byte: locale-specific number-formatting separator
.set sDialogLanguageTable,   0x0806BD78  @ ROM: 8 x u32, one string-table blob pointer per language
.set gDialogTextBlobBase,    0x030033C0  @ active language blob's base pointer (0 = none installed)
.set gDialogTextOffsetTable, 0x030033C4  @ pointer to the active blob's per-string-ID u32[] offset table
.set gDialogTextTreeNodes,   0x030033C8  @ pointer to the active blob's Huffman tree node table
.set gDialogTextScratchBuf,  0x03005D08  @ pointer to the fixed 0x400-byte decode scratch buffer
.set gTextRenderState,       0x03003110  @ struct: font descriptor pointers (+0x00/+0x04) and other
                                          @ text-rendering fields (e.g. +0x11 = line height); not
                                          @ fully mapped, see draw_text_line.s/print_text_box.s
.set sTextMacroTable,        0x03003170  @ ROM: pointer table for 0x40-prefixed escape/macro codes

@ --- MT19937 PRNG (see docs/memory-map/rng.md) ---
@ Names mostly match jogotu's BizHawk script naming, cross-checked
@ against our own disassembly there. Cursor 1 is the one that script
@ tracks; cursor 2 was found independently this session and is
@ undocumented by the script (see rng.md for what's confirmed and
@ what's still open about it).
.set gMt19937StatePtr,           0x0300557C  @ base of the 624-word MT state array
.set gMt19937CurPtr,             0x03005580  @ cursor 1: pointer into the state array
.set gMt19937RemainingIndices,   0x03005584  @ cursor 1: untempered words left before regenerating
.set gMt19937CurPtr2,            0x03005588  @ cursor 2: pointer into the state array
.set gMt19937RemainingIndices2,  0x0300558C  @ cursor 2: untempered words left before regenerating
.set gMt19937DrawIndex,          0x03005578  @ cursor 1: running count of numbers drawn
.set gMt19937LastRollByte,       0x03005574  @ low byte of the last tempered value (purpose unconfirmed)
.set gMt19937SeedValue,          0x03005594  @ accumulating seed value (SetSeed/AutoSeed)
.set gMt19937AutoSeedCallCount,  0x03005590  @ increments each AutoSeed call (purpose unconfirmed)
.set gMt19937SeedSourceStruct,   0x0300356C  @ external struct AutoSeed reads timing/frame data from
                                              @ for auto-seeding (subsystem unconfirmed)
.set gMt19937SeedSourceCounter,  0x030034EC  @ external halfword counter AutoSeed also reads
