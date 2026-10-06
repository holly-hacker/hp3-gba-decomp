#pragma once

#include "types.h"

// SaveHeader.bHeaderFlags, one field per HeaderFlags bit (LSB first).
typedef struct {
    u8 bOwlCareKitUnlocked : 1;
    u8 bMinigame1Unlocked : 1;
    u8 bMinigame2Unlocked : 1;
    u8 bMinigame3Unlocked : 1;
    u8 bMinigame4Unlocked : 1;
    u8 bMinigame5Unlocked : 1;
    u8 bTeaLeafDivinationIntroShown : 1;
    u8 bGammaHigh : 1;
} __attribute__((packed)) HeaderFlagsBits;

// The flags byte, viewed as a whole (with the HeaderFlags masks) or as bit-fields.
typedef union {
    u8 all;
    HeaderFlagsBits bits;
} __attribute__((packed)) SaveHeaderFlags;

// SaveHeader.language: the language SetLanguage applies at boot, and
// whether the player has picked one yet.
typedef struct {
    u8 bLanguageIndex : 7;
    u8 flLanguageConfigured : 1;
} __attribute__((packed)) SaveLanguage;

// See docs/formats/save.md. File-level header, shared across all 3 save
// slots -- the live RAM copy is SaveManager.header (0x03005598, IWRAM).
typedef struct {
    u8 szMagic[8];        // 0x0: "HPPOA001" (US) / "HPPOA004" (JP)
    SaveLanguage language;  // 0x8
    u8 bMusicVolume;      // 0x9: options-menu Music volume, 0-10
    u8 bSoundVolume;      // 0xA: options-menu Sound volume, 0-10
    u8 abUnknown0[2];     // 0xB-0xC: unused padding (ValidateSaveHeader doesn't check it)
    SaveHeaderFlags bHeaderFlags;  // 0xD
    u16 wChecksum;        // 0xE-0xF: -Sum16(header, 16)
} SaveHeader;

// bHeaderFlags bits, see docs/formats/save.md.
typedef enum {
    flOwlCareKitUnlocked           = 0x01,
    flMinigame1Unlocked            = 0x02,
    flMinigame2Unlocked            = 0x04,
    flMinigame3Unlocked            = 0x08,
    flMinigame4Unlocked            = 0x10,
    flMinigame5Unlocked            = 0x20,  // unused fifth minigame; set by UnlockMinigame index 4
    flTeaLeafDivinationIntroShown  = 0x40,
    flGammaHigh                    = 0x80,
} HeaderFlags;

// The file-level options block (blocks 2-6), holding the minigame high
// scores indexed by difficulty (Easy/Medium/Hard).
typedef struct {
    u32 adwWizardCrackerPopItHighScores[3];  // 0x00
    u32 adwHippogriffGlideHighScores[3];     // 0x0C
    u32 adwRiddikulusHighScores[3];          // 0x18
    u8 abPadding[2];                         // 0x24
    u16 wChecksum;                           // 0x26: -Sum16(options, 0x26)
} SaveOptions;

// A slot's summary for the save/load menus, unpacked from the first fields
// of the slot's save stream (see UnpackSaveSlotPreview).
typedef struct {
    u32 dwMoney;
    u8 bPlaytimeHours;
    u8 bPlaytimeMinutes;
    u8 bPlaytimeSeconds;
    u8 bPlaytimeFrames;
    u8 bCurrentRoomId;
    u8 bSaveFlags;  // SaveFlags; PlaytimeCounterActive is set once a game was started
    u8 bMainMenuObjectiveIndex;
    u8 bPartyLeaderDisplayLevel;
} SaveSlotPreview;

// SaveManager.dwStreamMode while the slot stream is in use.
typedef enum {
    SaveStreamIdle = 0,
    SaveStreamPacking = 1,
    SaveStreamUnpacking = 2,
} SaveStreamMode;

// EEPROM layout: header in blocks 0-1, options in blocks 2-6, then three
// slots of SAVE_SLOT_BLOCKS 8-byte blocks each.
#define SAVE_SLOT_SIZE 0xA98
#define SAVE_SLOT_BLOCKS (SAVE_SLOT_SIZE / 8)
#define SAVE_SLOT_FIRST_BLOCK 7
#define SAVE_SLOT_COUNT 3

// The live save manager at 0x03005598.
typedef struct {
    SaveHeader header;
    SaveOptions options;              // 0x10
    u8 *pSlotBuffer;                  // 0x38: 0xA98-byte staging buffer for one slot
    SaveSlotPreview aSlotPreview[3];  // 0x3C
    u32 adwSlotValid[3];      // 0x60: ValidateSaveSlot's result per slot, 1 when the checksum is good
    u32 dwActiveSlot;  // 0x6C: slot last loaded or saved
    u8 *pStreamCursor;         // 0x70: next byte of the slot stream
    s32 dwStreamBitPos;        // 0x74: bit (or nibble shift) within *pStreamCursor
    u32 dwStreamBytesUsed;     // 0x78: stream length after the last full pack/unpack
    u32 dwStreamPercentUsed;   // 0x7C: dwStreamBytesUsed as a percentage of the slot size
    u32 dwStreamMode;          // 0x80: SaveStreamMode
} SaveManager;

extern SaveManager g_saveManager;  // 0x03005598

typedef struct {
    s16 wHourCarry;
    s8 bHours;
    s8 bMinutes;
    s8 bSeconds;
    s8 bFrames;
    u8 aUnused[2];
} Playtime;

typedef enum {
    PlaytimeCounterActive = 0x01,
    ContinueRestartsIntro = 0x02,
    Unknown_0x04 = 0x04,
} SaveFlags;

// Live save-adjacent state block at 0x03003180 (money, playtime, save flags,
// ...); see docs/formats/save.md. abMonsterDocLevel is accessed as a member
// to reproduce the ROM's base+0x10 address shape shared by three code sites.
typedef struct {
    u32 dwMoney;
    Playtime stPlaytime;
    u8 bSaveFlags;
    u8 pad_0D[0x03];
    u8 abMonsterDocLevel[69];
    u8 abOtherSaveState[0x47];  // 0x55-0x9B: Folio Universitas counts and flags, etc.
    u8 bOwlCareKitFlags;        // 0x9C: bit 0 = care screen visited (owlCareKit.flVisited)
} SaveStateBlock;

extern SaveStateBlock g_saveStateBlock;

extern const Playtime g_stPlaytimeFrameDelta;
extern const Playtime g_stPlaytimeHourLimit;

u32 AddPlaytimeDelta(Playtime *playtime, const Playtime *toAdd);
u32 ComparePlaytimeField(const Playtime *playtime, const Playtime *mask, u32 fieldMask);
void ProcessPlaytimeTick(void);

// Adds a signed amount of Sickles to the player's money, clamped to
// 0..999999, and returns the new total.
u32 AddSickles(s32 amount);

extern const SaveHeader g_DefaultSaveHeader;
extern const SaveOptions g_DefaultSaveOptions;

u16 Sum16(const void *data, u32 size);

// DISPSTAT saved by EepromTransferBegin and restored by EepromTransferEnd.
extern u16 g_wEepromSavedDispstat;

void EepromTransferBegin(void);
void EepromTransferEnd(void);
void EepromReadBlocks(u32 startBlock, u32 count, void *dst);
void EepromWriteBlocks(u32 startBlock, u32 count, const void *src);

void InitSaveSystem(void);
void LoadSaveSlotPreviews(void);
void ClearSaveSlotBuffer(void);
void UnpackBytesFromSaveStream(void *dst, u32 len);
void UnpackSaveSlotPreview(SaveSlotPreview *preview);
u32 ValidateSaveHeader(void);
void WriteDefaultSaveHeader(void);
u32 ValidateSaveOptions(void);
void WriteDefaultSaveOptions(void);

extern s32 SetSaveLanguageFlag(void);
extern s32 SyncSaveHeaderIfDirty(void);
extern void LoadSaveSlot(u32 slot);
extern u32 ValidateSaveSlot(u32 slot);
extern void ResetCharacterToLevel(u32 character, u32 level);  // sets a party member's saved level and stats from the level table
extern void InitCharacterSpells_candidate(u32 index, u16 *pStats);
extern void sub_0803BD48(u32 slot);
