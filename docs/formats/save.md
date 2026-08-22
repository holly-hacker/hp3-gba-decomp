# Save data format

The game's battery save lives on a GBA EEPROM chip (64Kbit / 8KB), not
SRAM/Flash. This document covers the EEPROM transport, the fixed-size
regions the game divides it into, and the per-block checksum scheme. See
`docs/memory-map.md` for the confidence-key legend used below.

## Backup type: 8KB EEPROM

**PROVEN.** `baserom.us.sav` (and `baserom.jp.sav`) are exactly 8192 bytes,
matching the 64Kbit EEPROM variant exactly (1024 blocks of 8 bytes). No
`SRAM_V`/`FLASH_V`/`EEPROM_V`-style Nintendo backup-ID string is present in
either ROM (`search_strings` over both found nothing), so this game doesn't
use the standard SDK auto-probe convention -- the backup type has to be
read out of the driver code itself, not a string.

EEPROM is accessed at `0x0D000000` via DMA3, one 16-bit serial-protocol word
at a time. The driver never loads that address from a literal pool; it's
built in two Thumb instructions (`movs r4, #0xD0` / `lsls r4, r4, #0x14`),
which is why a literal-pool search for the constant doesn't find it.

### Driver call stack (all in `asm`/on-disk `full_disasm.s`, US ROM)

| Function | Address | Role |
|---|---|---|
| `EepromDma3Transfer` | `0x08049F0C` | Generic DMA3 word transfer (`src`, `dst`, `ctrl`). Used only by the two functions below. |
| `EepromReadBlock` | `0x08049F8C` | Reads one 8-byte block: sends a 2-bit READ opcode + address bits, clocks 64 data bits back via DMA. |
| `EepromWriteBlockRaw` | `0x0804A050` | Writes one 8-byte block: sends a 2-bit WRITE opcode + address bits + 64 data bits + a stop bit, then busy-waits (polling `VCOUNT`, `0x04000006`, as a timeout clock) for the EEPROM's internal write cycle. |
| `EepromVerifyBlock` | `0x0804A1B0` | Reads a block back and compares it against a caller-supplied 8-byte buffer. |
| `EepromWriteBlockGuarded` | `0x0804A248` | Refuses to write if the selected geometry table is the 512B one (dead code path in practice -- see below); otherwise calls `EepromWriteBlockRaw`. |
| `EepromWriteBlockVerified` | `0x0804A280` | Write-guarded, then verify; retries up to 3 times total. |
| `EepromSelectInterface` | `0x08049EC4` | Sets `g_pEepromInterface` to `g_stEepromInterface512B` (size class 4) or `g_stEepromInterface8KB` (size class 0x40), based on its argument. |
| `EepromTransferBegin` / `EepromTransferEnd` | `0x0803C378` / `0x0803C3A8` | Save/clear `DISPSTAT`+`IF`, enable only the VBlank IRQ (needed by the write busy-wait), always select the 8KB interface; restore `DISPSTAT` afterward. |
| `EepromReadBlocks` | `0x0803C318` | `(startBlock, count, dst)` -- `EepromTransferBegin`, loop `EepromReadBlock` per 8-byte block, `EepromTransferEnd`. |
| `EepromWriteBlocks` | `0x0803C348` | Same shape, writing via `EepromWriteBlockVerified`. |

`EepromTransferBegin` always requests the 8KB geometry
(`EepromSelectInterface(0x40)`); there is no runtime size probe in this
call path. `g_stEepromInterface512B`/`g_stEepromInterface8KB`
(`EepromInterface { u32 totalBytes; u16 blockCount; u16 unused; u8
addrBits; }`, at ROM `0x08FAA7DC`/`0x08FAA7E8`) hold `{512, 64, ?, 6}` and
`{8192, 1024, ?, 14}` respectively -- the 512B table exists in the driver
but this game only ever selects the 8KB one.

## Byte order in `.sav` files

**PROVEN**, cross-checked against `baserom.us.sav`. Each 8-byte EEPROM
block is stored **byte-reversed** in the `.sav` file relative to the
logical layout the game code addresses (the emulator captures the serial
bit stream in the order the hardware shifts it out, which reverses byte
order per block when flattened to a file). A parser must reverse every
8-byte block before interpreting its contents, and re-reverse before
writing back.

## Region layout (1024 blocks total = 8192 bytes)

| Blocks | Bytes | Region | Written by |
|---|---|---|---|
| 0-1 | 0-15 | **SaveHeader** | `WriteDefaultSaveHeader` / game code via `SyncSaveHeaderIfDirty` |
| 2-6 | 16-55 | **SaveOptions** | `WriteDefaultSaveOptions` / `SyncSaveOptionsIfDirty` |
| 7-345 | 56-2767 | **Save slot 0** | `WriteSaveSlot(0)` |
| 346-684 | 2768-5479 | **Save slot 1** | `WriteSaveSlot(1)` |
| 685-1023 | 5480-8191 | **Save slot 2** | `WriteSaveSlot(2)` |

Each save slot is `0x153` blocks (339 blocks = 2712 = `0xA98` bytes); slot
`N` starts at block `7 + N*339`. `0xA98` is also the size of the
heap-allocated slot-transfer buffer (`g_SaveManager.pSlotBuffer`,
`sub_0802C2EC(0xA98)`) that every slot is staged through one at a time --
only one slot's data is resident in RAM at once.

### Checksum scheme (all three region kinds)

**PROVEN**, verified against `baserom.us.sav`: summing every little-endian
`u16` word of each region (including its own trailing checksum word), mod
0x10000, gives 0 for the header, the options block, and each save slot.
`Sum16` (`0x0803C1E0`) computes this running sum; the checksum word itself
is always written as `-sum` of the rest of the region, so a valid region
sums to zero as a whole. The checksum word is the **last** halfword of its
region (header: byte 14-15; options: byte 38-39; each slot: its last two
bytes).

### SaveHeader (16 bytes, blocks 0-1)

Default contents at ROM `g_abDefaultSaveHeader` (`0x0806B80C`):
`48 50 50 4F 41 30 30 31 00 0A 0A 01 00 00 00 00`.

| Offset | Size | JSON key | Notes |
|---|---|---|---|
| 0x0 | 8 | `szMagic` | ASCII `"HPPOA001"` (US) / `"HPPOA004"` (JP) -- confirmed against `baserom.us.sav`/`baserom.jp.sav`. `ValidateSaveHeader` checksum-checks the whole header, then byte-compares these 8 bytes against the ROM default; either check failing triggers `WriteDefaultSaveHeader`. |
| 0x8 | 1 | `flLanguageConfigured` + `bLanguageIndex` | Both packed into one byte: bit 7 = `flLanguageConfigured` (set by `SetSaveLanguageFlag` via `GetLanguage()\|0x80`); bits 0-6 = `bLanguageIndex`, passed to `SetLanguage()` during `InitSaveSystem`. Default `0x00` (unconfigured, language 0). |
| 0x9-0xD | 5 | `abUnknown0` | `0A 0A 01 00 00` in both the ROM default and the one real save sampled (`baserom.us.sav`) -- consistent with these bytes being unused, but not confirmed: `ValidateSaveHeader`/`WriteDefaultSaveHeader`/`InitSaveSystem` never read them as scalars, but no ROM-wide search for other readers/writers of this offset has been done. |
| 0xE | 2 | `wChecksum` | `u16`, `-Sum16(header, 16)`. |

### SaveOptions (40 bytes, blocks 2-6)

Default is all zero (`g_abDefaultSaveOptions`, `0x0806B81C`), and
`baserom.us.sav`'s copy is still all zero -- no field inside it has been
identified yet. `ValidateSaveOptions`/`WriteDefaultSaveOptions` treat it
with the same checksum-then-content-compare pattern as the header, with
the checksum word at local offset 0x26 (global offset 0x36 within
`g_SaveManager`).

### Save slots (2712 bytes each)

A slot's `0xA98` bytes are not a flat data copy -- they're a serialized
**bit/byte stream**, built field-by-field by `SerializeGameStateToSaveBuffer`
(`0x08021498`) through `PackBytesToSaveStream`/`PackBitsToSaveStream`
(`0x0803C00C`/`0x0803C050`), which append to a cursor
(`g_SaveManager.streamCursor`/`streamBitPos`) rather than writing at fixed
offsets. `PackAndChecksumSaveSlot` (`0x0803BF9C`) resets that cursor to
the slot buffer's start, calls `SerializeGameStateToSaveBuffer`, then
`Sum16`s the whole `0xA98` bytes and writes `-sum` as the slot's trailing
checksum. `SaveGameToSlot` (`0x0803BF20`) is the save-to-EEPROM operation
for slot `N`: pack + checksum, `WriteSaveSlot`, reload + `ValidateSaveSlot`,
then mark the slot active. The read side (`UnpackBytesFromSaveStream`/
`UnpackNibblesFromSaveStream`/`UnpackBitsFromSaveStream`, `0x0803BDDC`/
`0x0803BE10`/`0x0803BEE4`) is not traced -- `tools/save/parse_save.py`
implements its own decoder/encoder pair instead of mirroring those
functions (see "Parsing" below).

**Confirmed serialized fields**, in `SerializeGameStateToSaveBuffer`'s
emission order (byte-exact, verified by round-tripping `tools/save/parse_save.py`
against both `baserom.us.sav` and `baserom.jp.sav`):

| Source | JSON key | Contents |
|---|---|---|
| `0x03003180` | `dwMoney` | **money** (`u32`) |
| `0x03003186` | `bPlaytimeHours` + `bPlaytimeMinutes` + `bPlaytimeSeconds` + `bUnknown1` | **playtime**, one byte each. Per the user, their save's in-game HH:MM display reads "05:13"; the decoded bytes are exactly `5, 13, 17, 14` -- the first two match the display exactly, and the third is a plausible seconds value (0-59) the HH:MM display doesn't show. The 4th byte (`bUnknown1`, also 0-59 in this one sample) isn't confirmed -- a frames/VBlank sub-second counter is plausible but unverified. |
| `0x03003B50` | `bUnknown2` | unidentified |
| `0x0300318C` | `bSaveFlags` | Per the user: bit 0 clear makes the slot unrecognized (invalid, presumably a redundant check alongside the checksum); bit 1 set loads to the start of the game. Other bits: no observed effect. |
| `0x030027B9` | `bMainMenuObjectiveIndex` | Per the user: an index (with an offset) into the current-objective string table shown on the main menu. Editing it changes that main-menu text but not the pause menu's quest text, and gets overwritten back to its real value on the next save -- not confirmed to be the actual current-quest tracker, just something that feeds this one display. |
| `g_pPartyMasterStats_candidate[0].bLevel + 1` | `bPartyLeaderDisplayLevel` | derived value (party leader's display level, not a raw field) |
| `0x0300338C`-`0x0300338E` | `bOverworldSprite0`-`bOverworldSprite2` | Per the user: which overworld sprite each party slot's follower uses. Observed values: `3` = Harry (Lumos, headless -- likely rendered as a separate overlay), `4` = Harry (GBC), `5` = Harry, `7` = Ron, `8` = Buckbeak; `9` is out of bounds (severe graphical corruption, crashes the game). |
| `0x03002614` | `flOverworldMonstersDisabled` | Per the user: disables overworld random encounters with regular monsters (bosses still trigger). Packed as a single bit, not a byte. |
| `0x0300338F` | `bSelectedOverworldSpell` | Per the user: the currently-selected spell in the overworld (as opposed to in battle). |
| `0x030037B0`, 38x4 bytes | `abUnknown9` (152 bytes) | unidentified table (`FUN_08026da0`'s loop is a signed `do {...} while (-1 < i)` counting `0x25` down to `-1` inclusive, i.e. 38 iterations) |
| **party stats** (`SerializePartyStats`, `0x080187EC`) | `partyStats` | 3 x 28 = 84 bytes, see below |
| **inventory/quest data** (`0x0802A570`), variable-length | `inventoryQuestData` | data-dependent, see below |
| `0x03002240` | `abUnknown10` (32 bytes) | unidentified |
| `0x030027A0` | `abUnknown11` (256 bytes) | unidentified |
| **monster-dex levels** (`SerializeMonsterDexLevels`, `0x080370A0`) | `a3FolioBrutiLevels` + `a3BossMonsterLevels` | per-monster 3-bit value, one `g_abMonsterDocLevel_candidate[i]` entry per monster, LSB-first bit order. Per the user: split into the first 53 entries (`a3FolioBrutiLevels`, matching `docs/formats/folio_bruti.md`'s already-established `FOLIO_BRUTI_COUNT` grid boundary) and the remaining 16 (`a3BossMonsterLevels`, indices 53-68) -- in the one save sampled the 53 bestiary entries read `3` and the 16 boss entries read `0`, and the boss entries are never visible in game. |
| `0x030031D8`, 51 nibbles (`FUN_08037FB8` via `PackNibblesToSaveStream`/`0x0803BAF4`) | `anFolioUniversitasCounts` (51 nibbles) | Per the user: Folio Universitas (Harry's card collection) per-card count, one nibble per card. A card is only shown in-game once its count reaches at least 1. |
| `0x0300320B` | `a1FolioUniversitasUnlocked` (51 bits, stored as 7 bytes, LSB-first) | Per the user: parallel per-card unlocked/seen flag; all-unlocked is stored as `ffffffffffff07`. Confirmed against a real (non-test) save (`bak.sav`): `a1FolioUniversitasUnlocked[i] == 1` exactly where `anFolioUniversitasCounts[i] > 0`, for all 51 cards. |
| `0x03003212` | `abUnknown14` (7 bytes) | unidentified |
| `0x0300321C`, 4 nibbles (`FUN_08022EA8`) | `anUnknown15` (4 nibbles) | unidentified |
| `0x03003220` | `abUnknown16` (3 bytes) | unidentified |
| `0x03003226` | `abUnknown17` (6 bytes) | unidentified |
| `0x03003224` | `abUnknown18` (2 bytes) | unidentified |
| `0x0300322C` | `abUnknown19` (2 bytes) | unidentified |

After this sequence, whatever bytes remain before the slot's trailing
checksum are never written by any pack call -- leftover content from
whatever was previously staged through the shared `pSlotBuffer` heap
buffer. `tools/save/parse_save.py` captures this span verbatim as
`abTailPadding` for exact round-tripping; it carries no game-read
meaning.

`PackNibblesToSaveStream` (`0x0803BAF4`) is a third stream primitive
alongside the byte/bit ones: it packs each source byte's low nibble into
consecutive 4-bit slots (2 nibbles/byte), realigning to a nibble boundary
first if the cursor isn't already on one.

**Party stats** (`SerializePartyStats`): loops the 3 party members
(`g_pPartyMasterStats_candidate[0..2]`, `BattleFighter`-shaped, `0x48`
stride) and packs `BattleFighter+8`..`+0x23` (28 contiguous bytes) for
each. This links `BattleFighter`'s already-documented fields
(`docs/memory-map/battle.md`) directly to the save format, with the
following JSON keys per party member (each name below its `BattleFighter`
field):

| JSON key | `BattleFighter` field | Notes |
|---|---|---|
| `wHp` | `wHp` | current HP -- saved directly |
| `wMp` | `wMp` | current MP -- saved directly |
| `wXpToNextLevel` | `wRewardXp` | per the user, the character's XP remaining until their next level, not a running total. `LevelUpFighter_candidate` overwrites it wholesale from the level table's delta column on every level-up, consistent with a to-next-level distance rather than an accumulator; whatever compares accumulated XP against that distance to trigger a level-up (`ApplyPendingLevelUps_candidate`, `0x0801D308`) still has no located caller in either disassembly. |
| `bLevel` | `bLevel` | character level -- saved directly |
| `bUnknown0` | `bUnk_0x0F` | saved, unidentified |
| `abSpellCastLevel` (10 bytes) | `aSpellCastLevel[10]` | per-spell mastered level -- **`aSpellUsageProgress`/`aSpellCastLevel`, the game's actual "spells level up with use" mechanic (see `docs/memory-map/battle.md`, `TrackSpellFamiliarity`), is the thing that actually gets saved as character progression** |
| `abSpellUsageProgress` (10 bytes) | `aSpellUsageProgress[10]` | progress toward each spell's next level-up |

`wHp_max` and `wMp_max` are *not* saved -- both are pure functions of
`bLevel` (recomputed from the per-character level table on load), so
persisting them would be redundant. Equipment/`bStat_speed`/`bAccuracy`/
defense are likewise not saved here, consistent with
`ApplyEquipmentStatModifiers_candidate` recomputing them from
equipped-item data at battle entry.

**Inventory/quest data** (`0x0802A570`): reads a base pointer
`DAT_03003B68` and, for up to 7 independent counts stored at
`DAT_03003B68[0..7]` (skipping index 0), packs `count[i]` fixed-size
records from 7 separate sub-tables (record sizes `0x6C`, `0xC`, `0x34`,
`0xC`, `4`, `4`, `4`, at fixed offsets `0x14`, `0xD94`, `0xF14`, `0x1594`,
`0x1714`, `0x1794`, `0x17D4` from the base pointer) -- the shape of a
variable-length list-of-lists (inventory slots, quest/event flags, or
similar), not decoded further.

## `SaveManager` (IWRAM, `0x03005598`)

Applied in Ghidra as struct `SaveManager` (naming blocked by a tool-side
Hungarian-prefix checker bug on `st`-prefixed struct globals -- the type is
applied at the address even though the label is still `DAT_03005598`):

| Offset | Field | Notes |
|---|---|---|
| 0x00 | `header` | RAM copy of SaveHeader (16 bytes) |
| 0x10 | `options` | RAM copy of SaveOptions (40 bytes) |
| 0x38 | `pSlotBuffer` | heap pointer, the 0xA98-byte slot-transfer buffer |
| 0x3C | `slotPreview` | 3x 12-byte per-slot preview/summary records (cleared via `memset` when a slot fails validation) |
| 0x60 | `slotInvalid[3]` | `u32` per slot, set by `ValidateSaveSlot` (0 = valid) |
| 0x6C | `activeSlot` | `u32`, set by `SaveGameToSlot` |
| 0x70-0x83 | stream state | cursor pointer, bit position, and progress-percent fields driving the bit/nibble/byte pack-unpack helpers (`UnpackBytesFromSaveStream`/`UnpackNibblesFromSaveStream`/`UnpackBitsFromSaveStream`/`PackBytesToSaveStream`/`PackBitsToSaveStream`, `0x0803BDDC`-`0x0803C094`). This is the general-purpose stream used to serialize the entire save-slot payload (see "Save slots" above), not just a save-select preview. |

## `InitSaveSystem` flow (`0x0803BC9C`)

1. Allocate the `0xA98`-byte slot-transfer buffer.
2. `ValidateSaveHeader`; if invalid, `WriteDefaultSaveHeader` +
   `WriteDefaultSaveOptions` + `ClearSaveSlotBuffer`, then write all three
   slots as zeroed/default via `WriteSaveSlot`. If valid, `ValidateSaveOptions`
   alone (repairing just the options block if needed).
3. Apply the header's language byte via `SetLanguage`.
4. `LoadOrResetSaveSlots`: for each of the 3 slots, `LoadSaveSlot` +
   `ValidateSaveSlot`; an invalid slot's preview record is registered as
   empty, a valid one's preview is built from its data.

## Parsing

```
parse_save.py decode <in.sav> [out.json]     (default: stdout)
parse_save.py encode [in.json] <out.sav>     (default: stdin)
```

`decode` parses a raw `.sav` into JSON: block-reversal, checksum
verification, and the full field breakdown above (header, options, and
each slot's bitstream). `encode` reverses this exactly, recomputing all
three checksums. Round-trips byte-for-byte against both `baserom.us.sav`
and `baserom.jp.sav` (decode then encode reproduces the original file
exactly, including the two currently-unused/erased slots in each).
Human-readable per-region status lines go to stderr in both directions,
keeping stdout pure JSON/binary for piping.

The encoder/decoder are a self-contained reimplementation of the pack
stream's alignment rules (`SaveWriter`/`SaveReader` in the script) rather
than a port of the game's own Unpack functions -- what matters for
round-tripping is that this tool's own reader is the exact inverse of its
own writer, not that it replicates `UnpackBytesFromSaveStream` et al.
line-for-line.

**JSON shape.** Each field is a plain named key on its containing object
(header, options, a slot, or `inventoryQuestData`'s `tables`), in
on-disk order -- no separate index/wrapper object. Every non-struct
field's key carries a Hungarian-notation type/size prefix, the same
convention already used for this ROM's globals (`wHp`, `bLevel`,
`g_abDefaultSaveHeader`):

| Prefix | Meaning |
|---|---|
| `b` | 1-byte scalar (JSON int) |
| `w` | 2-byte scalar / u16 (JSON int) |
| `dw` | 4-byte scalar / u32 (JSON int) |
| `fl` | 1-bit flag (JSON bool) |
| `sz` | fixed-length ASCII string |
| `ab` | byte array/blob -- size given by its JSON length (hex string or list of ints) |
| `an` | nibble array (each element 0-15) -- size given by list length |
| `a3` | array of 3-bit values (each element 0-7) -- size given by list length |
| `a1` | array of 1-bit values (each element 0/1), unpacked LSB-first from its packed byte storage -- size given by list length |

Struct-shaped fields (`partyStats`, `inventoryQuestData`, `tables`)
carry no prefix, since a single type/size doesn't describe them. Fields
whose real name/meaning isn't identified are named `<prefix>UnknownN`,
where `N` is that field's 0-based position among its immediate siblings
sharing that prefix (top-level slot fields are indexed separately from,
e.g., the inventory sub-tables nested inside `inventoryQuestData`) --
not a global counter across the whole file.

A region's `wChecksum` key is present only when that region is actually
invalid (holding the bad stored value); a valid region has no checksum
key at all, since encoding always recomputes it fresh. A slot's
`abTailPadding` key is likewise omitted when it's all zero (the common
case) -- encoding zero-fills a missing tail-padding key back out to the
slot's fixed size. A slot whose own checksum doesn't validate (both
unused slots in the two save files sampled so far) is decoded as a raw
hex blob (`wChecksum` + `abRaw` keys only) instead of through the field
sequence, matching the game's own `ValidateSaveSlot`, which never trusts
a slot's content past its checksum.

## Further work

- Decode SaveOptions' 40 bytes (all-zero in the one real save sampled so
  far, so its field boundaries aren't visible from data alone).
- Confirm `bUnknown1` (the 4th playtime-adjacent byte) against a save
  with a nonzero, independently-known seconds/sub-second value.
- Identify the remaining unlabeled globals `SerializeGameStateToSaveBuffer`
  packs directly (`0x03003B50`, `0x0300318C`,
  `0x030027B9`, `0x0300338C`-`0x0300338F`, `0x03002614`, `0x030037B0`,
  `0x03002240`, `0x030027A0`, and the fields inside `FUN_08037FB8`/
  `FUN_08022EA8` other than the Folio Universitas ones: `0x03003212`,
  `0x0300321C`, `0x03003220`, `0x03003226`, `0x03003224`, `0x0300322C`).
- Decode the variable-length inventory/quest-list structure read from
  `DAT_03003B68` (`0x0802A570`) -- its 7 record tables' individual field
  layouts aren't decoded, just their record sizes/counts.
- Trace where `slotPreview` (`g_SaveManager+0x3C`) gets built from a
  loaded slot, for the save-select UI.
- Locate the running XP accumulator that `ApplyPendingLevelUps_candidate`
  (`0x0801D308`) is presumably driven by against `wXpToNextLevel` --
  neither disassembly currently shows a caller for it.
- JP-side addresses are not yet matched from these US ones (see
  `tools/match_functions.py` / `just match-functions`).
