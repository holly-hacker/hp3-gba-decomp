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
| 0x9 | 1 | `bMusicVolume` | Options-menu **Music** volume, 0-10 scale (`0x0a` default). `g_bMusicVolume`/`SaveManager_03005598.aHeader[9]`, read by `ApplyAudioVolumeSettings` (`0x0803FF98`, scaled `*25`). Confirmed against a real save with Music set to off (`0x00`). |
| 0xA | 1 | `bSoundVolume` | Options-menu **Sound** volume, 0-10 scale (`0x0a` default). `g_bSoundVolume`/`SaveManager_03005598.aHeader[0xa]`, read by `ApplyAudioVolumeSettings` (scaled `*12`). Confirmed against a real save with Sound set to off (`0x00`). |
| 0xB-0xC | 2 | `abUnknown0` | `01 00` in both the ROM default and every real save sampled. Exhaustive xref search on both this field's file offset (RAM `0x030055A3`-`0x030055A4`, `SaveManager+0xB`) and the containing `SaveManager` base (`0x03005598`) finds no code that reads or writes these two bytes individually. `ValidateSaveHeader` (`0x0803C244`) checksums the full 16-byte header but only byte-compares the first 8 bytes (`szMagic`) against `g_abDefaultSaveHeader` -- it does **not** cover this field, confirmed in-game: a real save with `abUnknown0` changed away from its `01 00` default still validates and loads normally. Consistent with these bytes being genuinely unused padding, though a reader reached only through a function boundary auto-analysis missed can't be fully ruled out by static search alone. |
| 0xD | 1 | `flHeaderBit0` + `flMinigame1Unlocked`-`flMinigame4Unlocked` + `flHeaderBit5` + `flTeaLeafDivinationIntroShown` + `flGammaHigh` | Bitmask (`g_bHeaderFlags`/`SaveManager_03005598.aHeader[0xd]`), one JSON field per bit, LSB first. Bits `0x02`/`0x04`/`0x08`/`0x10` (**PROVEN**) gate the 4 minigame-select entries -- confirmed via `DrawMinigameSelectMenu`/`ShowMinigameLockedMessageIfNeeded`/`HandleMinigameMenuSelection` (`0x0802D148`/`0x0802D1C8`/`0x0802D08C`), a real save where bit `0x04` flipped `0->1` at the exact save "Buckbeak's Hippogriff Glide" was unlocked, and the dialog strings each minigame reads its name from (`0xa4a`+index in `data/text/en_us.json`): index 0 = "Wizard Cracker Pop-it" (bit `0x02`), 1 = "Buckbeak's Hippogriff Glide" (bit `0x04`), 2 = "Riddikulus Boggart Challenge" (bit `0x08`), 3 = "Tea Leaf Divination" (bit `0x10`). Bit `0x80` (`flGammaHigh`, **PROVEN**) is the options-menu **Gamma** setting (Normal/High), confirmed against a real save with Gamma=High; also read by a menu-graphics selector, `FUN_0800D1A4`. File-level (part of `SaveHeader`, shared across all 3 save slots -- unlike the per-slot `abQuestEventState`), matching that a minigame unlock isn't scoped to one save slot (`options.abUnknown0` stayed all-zero throughout, ruling that out as the location). **Bit `0x01` (`flHeaderBit0`) resolved**: it's part of the minigame *launch* sequence itself (`InitMinigameLaunchSequence`/`TickMinigameLaunchSequence`, `0x08036038`/`0x08035EB0`, run after `HandleMinigameMenuSelection` sets `g_nSelectedMinigameIndex`), and only affects minigame index 0 ("Wizard Cracker Pop-it") specifically: when set, it points a pointer (`DAT_03005208`) at ROM `0x0806948C` instead of `0x08069474` (chosen by a second flag, bit 0 of `DAT_0300321C`/the save's own `anUnknown15`). These are **not two independent tables** -- confirmed byte-identical, `0x0806948C` is `0x08069474` shifted by exactly 2 records (24 bytes) -- so the bit just shifts, by +2, which row `TickMinigameLaunchSequence` reads (indexed by `DAT_03003F14`, a within-minigame round counter persisted across launches via `DAT_030052BC`/`FUN_080360DC`) before feeding one `u32` from that row into a game-mode-push call (`FUN_0802C7C4`). Row 0 and row 2 hold the identical value (`71`), so **this bit has no observable effect until the round counter reaches 1** -- confirmed in-game: no visible difference on a first playthrough, consistent with this. What rows 1 (`66`) vs. 3 (`41`) actually change isn't traced further. **Bit `0x40` (`flTeaLeafDivinationIntroShown`) resolved**: read/written by a previously-boundary-less function at ROM `0x0802CF38` (now `HandleMinigameSelectMenuConfirm`, found by disassembling backward from a `ldrb r1,[r?,#0xd]` hit to its `push {r4,lr}` entry point), the confirm-button handler for the minigame select menu. Selecting minigame index 3 (Tea Leaf Divination, already unlock-gated by bit `0x10`) checks this bit: clear sets it, syncs the header to EEPROM, and pushes game mode `0x44` (param `3`) -- an intro/tutorial sequence shown once; set skips straight to game mode `0x1C` (param `0`), the normal launch. Bit `0x20` (`flHeaderBit5`) still has no known reader: the same exhaustive xref search (direct address, `SaveManager` base, and the `g_bHeaderFlags` symbol's own 26 xrefs) turns up masks for every other bit in this byte (`0x01`/`0x02`/`0x04`/`0x08`/`0x10`/`0x40`/`0x80`) but never `0x20`. |
| 0xE | 2 | `wChecksum` | `u16`, `-Sum16(header, 16)`. |

### SaveOptions (40 bytes, blocks 2-6)

Default is all zero (`g_abDefaultSaveOptions`, `0x0806B81C`).
`ValidateSaveOptions`/`WriteDefaultSaveOptions` treat it with the same
checksum-then-content-compare pattern as the header, with the checksum
word at local offset 0x26 (global offset 0x36 within `g_SaveManager`).

**This is where minigame high scores live**, not per-slot data --
file-level, loaded once at boot by `InitSaveSystem` regardless of which
save slot (if any) is later picked, matching minigames being reachable
straight from the main menu. The live RAM copy is `SaveManager+0x10`
(`DAT_030055A8`), synced to EEPROM by `SyncSaveOptionsIfDirty` (called
from minigame-exit cleanup paths, e.g. `FUN_08008AD0`/`FUN_080338A4`).

| Offset | Size | JSON key | Notes |
|---|---|---|---|
| 0x0 | 4 | `dwWizardCrackerPopItEasyHighScore` | Wizard Cracker Pop-it's Easy-difficulty high score. Inferred from the confirmed field below by the same 3-consecutive-`u32`-per-minigame pattern `DrawDifficultySelectMenu` reads (`DAT_03003F88*0xC` selects a minigame's 12-byte block; within it, offsets 0/4/8 = Easy/Medium/Hard) -- not independently confirmed against a real save yet. |
| 0x4 | 4 | `dwWizardCrackerPopItMediumHighScore` | **PROVEN**: confirmed byte-exact against two real saves differing only here (`0 -> 1080`) after setting a Medium-difficulty Wizard Cracker Pop-it high score. Stored as a `u32` (matching `FUN_08032534`'s `*(uint*)` writes), though only the low 16 bits were nonzero in the one sample seen. |
| 0x8 | 4 | `dwWizardCrackerPopItHardHighScore` | Same inference as offset 0x0 (Hard difficulty). |
| 0xC-0x17 | 12 | `dwBuckbeaksHippogriffGlideEasy/Medium/HardHighScore` | **PROVEN** in-game -- immediately follows Wizard Cracker Pop-it's block, in minigame-unlock-bit order. |
| 0x18-0x23 | 12 | `dwRiddikulusBoggartChallengeEasy/Medium/HardHighScore` | **PROVEN** in-game -- next block in unlock-bit order. |
| 0x24-0x25 | 2 | `abOptionsPadding` | Unused padding. Per the user, Tea Leaf Divination has no high scores at all, consistent with only 3 of the 4 minigames needing a 12-byte block here (3 x 3 difficulties x 4 bytes = 36 bytes, fitting the 38 available data bytes almost exactly). Exhaustive xref search on the RAM copy's address (`0x030055CC`-`0x030055CD`, `SaveManager+0x10+0x24`) and on the containing `SaveManager+0x10` options base finds no code that reads or writes this offset -- every located accessor of the options block (`FUN_08032534`'s high-score writer, `FUN_0802CC44`'s high-score display, `HandleHighScoreDifficultyMenuTick`'s reset-all-3 handler at `0x0802C988`) only ever indexes the 9 `u32` high-score slots (byte range `0x0`-`0x23`), never past them. Omitted from the JSON like other padding fields (`abTailPadding`, etc.) when all-zero, which it is in every real save sampled so far. |
| 0x26 | 2 | `wChecksum` | Same convention as the header/each slot. |

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
| `0x03003186` | `bPlaytimeHours` + `bPlaytimeMinutes` + `bPlaytimeSeconds` + `bPlaytimeFrames` | **playtime**, one byte each (**PROVEN**). Per the user, their save's in-game HH:MM display reads "05:13"; the decoded bytes are exactly `5, 13, 17, 14` -- the first two match the display exactly, and the third is a plausible seconds value (0-59) the HH:MM display doesn't show. The 4th byte (`bPlaytimeFrames`) stays in `0-28` across 26 real samples gathered since -- well under a 50/60fps rollover, consistent with a sub-second frame counter. **Incrementer located**: `ProcessPlaytimeTick` (`0x0802165C`), called unconditionally every frame from `main`, adds 1 to `bPlaytimeFrames` via `AddPlaytimeDelta` (`0x0800C6EC`, a carry-chained add: Frames mod 30 -> Seconds mod 60 -> Minutes mod 60 -> Hours mod 99) -- but only while `bSaveFlags` bit `0x01` is set (see below) and `bPlaytimeHours` is still below the ROM-supplied cap of 99 (`ComparePlaytimeField`/`0x0800CA70` against `0x0806054C`); once Hours reaches 99 the counter freezes rather than rolling over. This whole mechanism operates on an 8-byte RAM struct at `0x03003184` (2 leading bytes, then the 4 playtime bytes, then 2 trailing bytes) that's wider than what's actually serialized -- the 2 bytes on each side are reset to 0 every load (`InitializePlaytimeStruct`/`0x0800CAE8`) and never written by any other code, so they carry no save-format meaning of their own (the carry chain's would-be 5th, "beyond Hours" field is unreachable in practice, since the Hours cap stops the whole chain from running first). |
| `0x03003B50` | `bUnknown2` | unidentified |
| `0x0300318C` | `bSaveFlags` | Bit 0 (`flPlaytimeCounterActive`, **PROVEN**): set once by `StartNewGamePlaytime` (`0x080215DC`), reached only from the "start a new game" path (`FUN_08044070`, taken when the selected save slot is empty) rather than continuing an existing save -- never cleared afterward. Gates `ProcessPlaytimeTick`'s per-frame advance above; not a slot-validity marker (`ValidateSaveSlot`, `0x0803C0A8`, validates purely by checksum and never reads `bSaveFlags` at all). Bit 1 (**PROVEN**): consumed one-shot (cleared on use) by `HandleSaveLoadContinuation` (`0x08043AF0`) at save-load -- if set, pushes game mode `0x38` (the fresh-start/intro sequence, via `HandleEndingSequenceTransition`); if clear, resumes normally. `HandleEndingSequenceTransition` (`0x0801D6DC`) sets bit 1 *and* bit 2 together (`\|= 6`) at game-mode `0x40` (game completion), the same instant it starts New Game+ (`ResetQuestStateForNewGame(1)`). Bit 2 has no reader anywhere in the program: an exhaustive xref search on `bSaveFlags`'s storage address turns up exactly 10 accesses total (covering bits 0/1/2 above plus its serialize/deserialize copies in `SerializeGameStateToSaveBuffer`/the slot-unpack routine at `0x080213C0`), none of which test bit `0x04` -- and testing in-game (bit 2 set without bit 1) showed no observed effect, consistent with it being dead. Bits 3-7: the same exhaustive search finds no code touching them at all. |
| `0x030027B9` (`g_bMainMenuObjectiveIndex`) | `bMainMenuObjectiveIndex` | Index into the main-menu current-objective string table. Confirmed across 24 real saves to be the exact same live byte as `abQuestEventState[25]` below -- serialized twice. |
| `g_pPartyMasterStats_candidate[0].bLevel + 1` | `bPartyLeaderDisplayLevel` | derived value (party leader's display level, not a raw field) |
| `0x0300338C`-`0x0300338E` | `bOverworldSprite0`-`bOverworldSprite2` | Per the user: which overworld sprite each party slot's follower uses. Observed values: `3` = Harry (Lumos, headless -- likely rendered as a separate overlay), `4` = Harry (GBC), `5` = Harry, `7` = Ron, `8` = Buckbeak; `9` is out of bounds (severe graphical corruption, crashes the game). |
| `0x03002614` | `flOverworldMonstersDisabled` | Per the user: disables overworld random encounters with regular monsters (bosses still trigger). Packed as a single bit, not a byte. |
| `0x0300338F` | `bSelectedOverworldSpell` | Per the user: the currently-selected spell in the overworld (as opposed to in battle). |
| `0x030037B0` (`g_abItemQuantities`), 152 bytes | `itemQuantities` + `equippedItems` | see "Item quantities and equipment" below |
| **party stats** (`SerializePartyStats`, `0x080187EC`) | `partyStats` | 3 x 28 = 84 bytes, see below |
| **room-object state** (`PackRoomObjectStateToSaveStream`, `0x0802A570`), variable-length | `roomObjectState` | data-dependent, see below |
| `0x03002240` | `abUnknown10` (32 bytes) | unidentified, but its containing reset function is now known -- see `ResetQuestStateForNewGame` below. |
| `0x030027A0` (`g_abQuestEventState`) | `abQuestEventState` (256 bytes) | Index 25 = `bMainMenuObjectiveIndex` above. Persistent global quest/event state, not per-room -- confirmed unchanged (byte-for-byte) across a real room-to-room border crossing. Indices ~224-254 hold flags/counters (e.g. one index counts kills of one specific boss species) that all reset to 0 together at a specific story-progression checkpoint (not on ordinary room transitions), while index 25 (and index 0, an unconfirmed story-stage counter candidate) didn't reset there. |
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

**Item quantities and equipment** (`g_abItemQuantities`, `0x030037B0`,
152 bytes): a flat item-ID-indexed quantity array. **PROVEN**: item ID
== index into `g_pBattleItemTable` (ROM `0x08060ED4`, `BattleItemEntry_candidate[78]`,
stride `0x34`) == index into `g_abItemQuantities`. Each entry's
`nNameTextId` field resolves through the decoded dialog/UI string table
(`data/text/en_us.json`'s 2767 `strings`) to that item's real display
name -- every one of 78 entries decodes to a real, sensible item name,
and 6 of them were independently cross-checked against real-save
evidence with an exact match every time (`bGrandWiggenweldPotion`
going 3->4 for a picked-up Grand Wiggenweld Potion; `bMonsterBookOfMonsters`
tracking boss-drop kills; `bPocketWatch` appearing at exactly the
save a Pocket Watch was received; and the user's own listed
Belt/Gloves/Boots/Cloak landing on indices 4/25/32/53 exactly). The
JSON exposes one field per index in on-disk order (`itemQuantities`, a
struct not a bare array -- see "Parsing"/"JSON shape" below); indices
0-78 are contiguous (a plain ordered list in the tool, `ITEM_NAMES`, not
an index->name map -- there's no gap to justify one) using their real
names; the remainder (79-131, confirmed *not* a continuation of
`g_pBattleItemTable` -- see below) are `bItemQuantityNNN`-style
placeholders.

Save/item-table order groups into contiguous per-equipment-slot/category
runs (belts 0-7, misc/quest items 8-19, gloves 20-28, boots 29-37, caps
38-46, robes/cloaks 47-55, potions 56-61, ingredients/quest items
62-77, `bMonsterBookOfMonsters` alone at 78), each with its own local
string-ID base rather than one single global offset across the whole
table -- e.g. potions are `index + 1540`, while gloves/boots are
`index + 1538` and belts/misc are `index + 1576`.

**Index 79 is confirmed invalid, marking the real end of the table.**
Per the user in-game: item 79 shows up under "all items" but not under
any real category, uses the Rat Tonic sprite, and displays as "There you
are, Harry!" -- and reading `g_pBattleItemTable[79].nNameTextId`
directly from ROM gives exactly `0`, which decodes to that same string
(the very first dialog line in the table). That's not a real item name,
it's `g_pBattleItemTable` simply ending at 78 entries and index 79
reading zeroed/unrelated memory past it. So indices 0-78 (79 entries)
are the complete, real table; **79-131 are not a continuation of it**
and shouldn't be assumed to hold real item data at all.

Indices 132-149 are `g_abEquippedItemIds` (Ghidra: typed `EquippedItemSlots[3]`,
though the global keeps its `ab`-prefixed name -- a known checker bug
rejects `st`/struct-typed global names, same as `SaveManager`), an alias
into this same array (not a separate allocation): 3 fighters x 6 equip
slots, item ID or `0xff` (empty), exposed as `equippedItems.harry`/
`.hermione`/`.ron`, each `{belt, charm, gloves, boots, hat, cloak}`.
Fighter order confirmed from a real save with distinct per-character
counts (Harry 0 items, Hermione 4, Ron 1 -- unambiguous). **Slot order
confirmed**: belt, charm, gloves, boots, hat, cloak (slot 2 = gloves
independently matches Ron's one equipped item). Trailing 2 bytes are
always-zero padding so far (`abItemQuantitiesPadding`, omitted like
other padding fields when zero).

**Room-object state** (`roomObjectState`, packed by `PackRoomObjectStateToSaveStream`
(`0x0802A570`), unpacked by `UnpackRoomObjectStateFromSaveStream` (`0x0802A3D4`)):
this is **not an inventory list** -- it's a snapshot of every non-default
object currently active in the room the player is standing in (spawned
monsters, pickups, switches, chests, etc.), keyed by world-tile position,
so re-entering a room restores it to how the player left it. **STRUCTURAL
MATCH**: confirmed by finding the exact symmetric producer,
`CaptureRoomObjectState` (`0x0802A70C`), which walks the live
`sActiveObjectListHead` linked list of room objects and re-populates
`g_pRoomObjectStateBuffer` (`0x03003B68`) every time the room state is
captured (e.g. before a save or a room transition); `RestoreRoomObjectState`/
`RestoreRoomObjectStateMinimal` (`0x0802AB34`/`0x0802AE64`) are the
load-side counterparts that walk it back out, respawning each tile's
default object via `RespawnRoomObjectAtTile` (`0x08005B70`, looks up the
room's static per-tile object-type table and instantiates it) and then
overwriting specific fields on top with the saved deltas.

Fixed 17-byte header (packed in this exact, non-sequential field order):

| Offset (from `g_pRoomObjectStateBuffer`) | Size | JSON key | Notes |
|---|---|---|---|
| 0x0 | 1 | `bPlayerFacing` | Read from/written to `g_pPlayerObject->field_0x12` on both the capture and restore side. Not a table count -- despite occupying the position a naive read of the packing order might suggest. Per the user: confirmed as an 8-direction facing enum -- `4` = facing down, `3` = facing down-right (consistent with a clockwise, 45-degrees-per-step enum covering all 8 directions). |
| 0xC | 4 | `fxPlayerPosX` | **STRUCTURAL MATCH**: `g_pPlayerObject->nX` (per `docs/formats/object_script.md`'s already-identified `Object` layout), copied verbatim -- already in the engine's 16.16 fixed-point form, unlike the per-tile `u16` coordinates the tables below store (which get `<<0x10` on restore). Passed straight to `SnapObjectPosition` when restoring. Decoded as a JSON float (raw `/ 65536`); confirmed against a real save (`bak.sav`), whose raw values (`0x05D17900`/`0x01F4B980`) divide out to plausible, unremarkable-looking world coordinates (`1489.47`/`500.72`) rather than the odd-looking large integers the raw hex represents. |
| 0x10 | 4 | `fxPlayerPosY` | Same as above, `g_pPlayerObject->nY`. |
| 0x9 | 1 | `bSwitchState` | **STRUCTURAL MATCH**: not read from the player `Object` at all -- it's `g_bRoomSwitchState` (`0x03003B64`), get/set via `GetRoomSwitchState`/`SetRoomSwitchState` (`0x0802B12C`/`0x0802B110`). The setter is called from the room's tile-collision dispatcher (`0x0802D8F4`) for two specific trigger tile IDs (`0x23`/`0x24`) that set it to `0`/`1` respectively; only when the value actually *changes* does it call `ApplyRoomSwitchEffect` (`0x0802DF3C`), which plays a sound (`0x0803D338`, args `5,0x1f` for state 0 / `4,0x1f` for state 1) and swaps a tile graphic between two frames (effect IDs `0x19`/`0x18`) at a fixed screen position (`0xE0,0x220`) via `0x08020440`. Being a single scalar (not an array/table), this mechanic supports **at most one such lever/switch per room** -- a room needing several independently-stateful toggles instead uses the `kind5SwitchObjects` table below (kind-`5` objects with sub-kind `'3'`, up to 32 entries, one toggle bit each). |
| remaining bytes (1, 2, 3, 4, 5, 6, 7) | 1 each | *(none)* | Entry counts for the 7 saved tables below -- not represented as their own JSON field, since each is exactly the corresponding table's list length (recomputed on encode). |

7 variable-length record tables follow, each holding up to 32 entries
(one table up to 570) of a fixed record size, at fixed offsets from the
base pointer. Each is a plain JSON array of objects -- one field per
named struct member (see below), no count/size/table-index metadata
alongside it (that's implied by the key name and array length). Every
record's field layout is traced byte-for-byte from the two symmetric
producer/consumer functions (`CaptureRoomObjectState` capture; `RestoreRoomObjectState`/
`RestoreRoomObjectStateMinimal` restore) and cross-checked against a real save (`bak.sav`);
most fields are a straight copy of one fixed offset of the live `Object`
struct (`docs/formats/object_script.md`) -- ones with no identified
purpose keep that struct's own offset in their name (`bUnk_0xNN`/
`wUnk_0xNN`/`dwUnk_0xNN`), matching this ROM's existing `bUnk_0x0F`-style
convention for unnamed fields. A record's leftover bytes (confirmed
always zero in practice, since the capture side memsets the whole
buffer before writing) round-trip through an `abPadding` key, omitted
like a slot's `abTailPadding` when all-zero.

| JSON key | Offset | Record size | Max entries | Selected (capture side, `CaptureRoomObjectState`) for room-object "kind" (`*(short*)(obj+8)`) |
|---|---|---|---|---|
| `defaultKindObjects` | 0x14 | 0x6C (108) | 32 | the fallback/default case -- any kind not one of the values below. The richest record: full `Object` state, plus the tile positions of up to 3 linked sub-objects (`Object+0xa0`/`+0xa4`/`+0xa8`) -- captured but **never restored** (the load side reads no such fields for this table). |
| `kind4Or7Objects` | 0xD94 | 0xC (12) | 32 | kinds `4`, `7`. Captures `Object+0xc` (flags) **unmasked** -- the only table that doesn't clear bit `0x00200000` before saving it. |
| `kind5Objects` | 0xF14 | 0x34 (52) | 32 | kind `5`, when the object's byte at `+0x61` is *not* the ASCII char `'3'` |
| `floorItemStates` | 0x1594 | 0xC (12) | 32 | kind `1`. Its two dwords aren't `Object` fields at all -- on restore, the respawned object's own tile position is used to look up an entry in a separate, static per-map item-drop table (`LookupFloorItemStateEntry`), and these two dwords overwrite that entry. Refreshes persistent floor-item state keyed by tile position, not the spawned object itself. |
| `kind5SwitchObjects` | 0x1714 | 0x4 | 32 | kind `5`, when `+0x61 == '3'` -- structurally the per-object counterpart to the single-instance `bSwitchState` room switch above, but with up to 32 independent instances per room. `bTriggered` is encoded inverted (stored as `NOT(bit 0x4 of Object+0xc)`); a stored `1` makes restore call `MarkRoomObjectConsumed`, which plays a "consumed/vanish" animation and clears that bit. |
| `pickupMarkers` | 0x1794 | 0x4 | 32 | kind `0xB`. `bUnk_0x80` round-trips with a `+1` offset applied only on restore (`Object+0x80` becomes `bUnk_0x80 + 1`); captured verbatim (`Object+0x80`'s raw low byte) on save. `bUnk_0x8f`, when it equals `8` on restore, triggers an item-grant popup callback (`GrantPickupMarkerItem`). |
| `presenceMarkers` | 0x17D4 | 0x4 | 570 (theoretical span; see below) | kinds `2`, `8`, `10` unconditionally, plus kind `5`/`6` under specific status-bit conditions -- just a tile position (`bTileX`/`bTileY`), no extra state: restore only respawns the tile's default object. |

None of the numeric "kind" values above are tied to a named enum yet --
the table names above describe which capture-side branch produces which
JSON table, not what each kind represents in game terms.

**Not part of the save.** `g_pRoomObjectStateBuffer[8]` (a byte the pack/unpack
functions never touch) and the region at offset `0x19B4` (record size
`0x24` = 36, inside the nominal span of `presenceMarkers`' table) form an
eighth, purely in-memory table: captured only for room objects flagged
`+0x10 == 0xFF` and kind `0x10` (`CaptureRoomObjectState`), and restored by both
`RestoreRoomObjectState` and `RestoreRoomObjectStateMinimal` independent of any `Unpack*` call.
`0x0802B0F4` (`memset`s the whole `0x20BC`-byte buffer to 0) runs after
every restore, and the `Unpack*`-driven load path (`0x0802A3D4`) never
populates this table at all -- so whatever it holds only survives a room
transition within the same play session, never a save/reload. This means
`presenceMarkers`' *effective* usable range is smaller than its
570-entry span suggests, since the tail of that space doubles as this
table's storage during normal (non-serialized) play.

`0x0802B018` allocates the whole `0x20BC`-byte buffer once
(`DAT_03003B68`) via the heap allocator also used elsewhere in save
handling.

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
(header, options, a slot, or `roomObjectState`), in on-disk order -- no
separate index/wrapper object. Every non-struct
field's key carries a Hungarian-notation type/size prefix, the same
convention already used for this ROM's globals (`wHp`, `bLevel`,
`g_abDefaultSaveHeader`):

| Prefix | Meaning |
|---|---|
| `b` | 1-byte scalar (JSON int) |
| `w` | 2-byte scalar / u16 (JSON int) |
| `dw` | 4-byte scalar / u32 (JSON int) |
| `fx` | 4-byte 16.16 fixed-point scalar (JSON float -- dividing/multiplying by 65536 is exact in IEEE754 double, so this round-trips losslessly) |
| `fl` | 1-bit flag (JSON bool) |
| `sz` | fixed-length ASCII string |
| `ab` | byte array/blob -- size given by its JSON length (hex string or list of ints) |
| `an` | nibble array (each element 0-15) -- size given by list length |
| `a3` | array of 3-bit values (each element 0-7) -- size given by list length |
| `a1` | array of 1-bit values (each element 0/1), unpacked LSB-first from its packed byte storage -- size given by list length |

Struct-shaped fields (`partyStats`, `roomObjectState`) carry no prefix,
since a single type/size doesn't describe them. Fields whose real
name/meaning isn't identified are named `<prefix>UnknownN`, where `N` is
that field's 0-based position among its immediate siblings sharing that
prefix (top-level slot fields are indexed separately from, e.g.,
`roomObjectState`'s own `unknownN` record tables, each a plain JSON
array of fixed-size hex-encoded records with no prefix -- the array
carries no single scalar type/size) -- not a global counter across the
whole file.

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

- Decode what `flHeaderBit0`'s row-1-vs-row-3 game-mode values (`66`
  vs `41`, read by `TickMinigameLaunchSequence` off a shared table at
  ROM `0x08069474`) actually change in "Wizard Cracker Pop-it" --
  resolved which minigame/code path and that it's a same-table row
  shift rather than two distinct tables, but not what the values
  themselves represent in game terms, nor when the round counter
  (`DAT_03003F14`) actually reaches 1 during play.
- Identify the remaining unlabeled globals `SerializeGameStateToSaveBuffer`
  packs directly: `0x03003B50` (`bUnknown2`), `0x03002240` (`abUnknown10`,
  32 bytes), and the fields inside `FUN_08037FB8`/`FUN_08022EA8` other
  than the Folio Universitas ones: `0x03003212` (`abUnknown14`),
  `0x0300321C` (`anUnknown15`), `0x03003220` (`abUnknown16`),
  `0x03003226` (`abUnknown17`), `0x03003224` (`abUnknown18`),
  `0x0300322C` (`abUnknown19`).
- Name the remaining `bUnk_0xNN`/`wUnk_0xNN`/`dwUnk_0xNN` fields in the
  7 room-object-state tables (see "Room-object state" above) -- their
  byte offsets are traced precisely, but most still only carry their
  raw `Object` struct offset rather than a real name; cross-referencing
  `docs/formats/object_script.md` as more `Object` fields there get
  identified should resolve several of these directly.
- Identify the room-object "kind" enum (`*(short*)(obj+8)`) that
  `0x0802A70C` switches on to pick a table -- would let each table above
  get a real name instead of `unknownN`.
- Confirm the full 8-direction `bPlayerFacing` enum beyond the two
  values already confirmed by the user (`4` = down, `3` = down-right).
- Find what else in a room reads `bSwitchState` (getter `0x0802B12C`) --
  confirmed so far only drives its own sound/graphic-swap effect
  (`0x0802DF3C`); whatever door/platform/gate a lever is meant to
  control elsewhere in the room isn't traced yet.
- Trace where `slotPreview` (`g_SaveManager+0x3C`) gets built from a
  loaded slot, for the save-select UI.
- Locate the running XP accumulator that `ApplyPendingLevelUps_candidate`
  (`0x0801D308`) is presumably driven by against `wXpToNextLevel` --
  neither disassembly currently shows a caller for it.
- JP-side addresses are not yet matched from these US ones (see
  `tools/match_functions.py` / `just match-functions`).
