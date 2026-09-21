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

// See docs/formats/save.md. File-level header, shared across all 3 save
// slots -- the live RAM copy is SaveManager.header (0x03005598, IWRAM).
typedef struct {
    u8 szMagic[8];        // 0x0: "HPPOA001" (US) / "HPPOA004" (JP)
    u8 bLanguageByte;     // 0x8: bit 0x80 = flLanguageConfigured, bits 0-6 = bLanguageIndex
    u8 bMusicVolume;      // 0x9: options-menu Music volume, 0-10
    u8 bSoundVolume;      // 0xA: options-menu Sound volume, 0-10
    u8 abUnknown0[2];     // 0xB-0xC: unused padding (ValidateSaveHeader doesn't check it)
    HeaderFlagsBits bHeaderFlags;  // 0xD
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

// One 12-byte slot summary record; only the flags byte is mapped.
typedef struct {
    u8 abUnmapped_0[9];
    u8 bFlags;  // bit 0 is set when the slot holds a save
    u8 abUnmapped_A[2];
} SaveSlotPreview;

// The live save manager at 0x03005598; only the mapped members are declared.
typedef struct {
    SaveHeader header;
    u8 abUnmapped_10[0x2C];
    SaveSlotPreview aSlotPreview[3];  // 0x3C
    u32 adwSlotValid[3];      // 0x60: ValidateSaveSlot's result per slot, 1 when the checksum is good
    u32 dwActiveSlot;  // 0x6C: slot last loaded or saved
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

extern s32 SetSaveLanguageFlag(void);
extern s32 SyncSaveHeaderIfDirty(void);
extern void LoadSaveSlot(u32 slot);
extern u32 ValidateSaveSlot(u32 slot);
extern void sub_0803BD48(u32 slot);
