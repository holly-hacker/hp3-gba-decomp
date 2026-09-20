#pragma once

#include "types.h"

// See docs/formats/save.md. File-level header, shared across all 3 save
// slots -- the live RAM copy is SaveManager.header (0x03005598, IWRAM).
typedef struct {
    u8 szMagic[8];        // 0x0: "HPPOA001" (US) / "HPPOA004" (JP)
    u8 bLanguageByte;     // 0x8: bit 0x80 = flLanguageConfigured, bits 0-6 = bLanguageIndex
    u8 bMusicVolume;      // 0x9: options-menu Music volume, 0-10
    u8 bSoundVolume;      // 0xA: options-menu Sound volume, 0-10
    u8 abUnknown0[2];     // 0xB-0xC: unused padding (ValidateSaveHeader doesn't check it)
    u8 bHeaderFlags;      // 0xD: HeaderFlags bitmask
    u16 wChecksum;        // 0xE-0xF: -Sum16(header, 16)
} SaveHeader;

// bHeaderFlags bits, see docs/formats/save.md.
typedef enum {
    flOwlCareKitUnlocked           = 0x01,
    flMinigame1Unlocked            = 0x02,
    flMinigame2Unlocked            = 0x04,
    flMinigame3Unlocked            = 0x08,
    flMinigame4Unlocked            = 0x10,
    flHeaderBit5                   = 0x20,  // unidentified
    flTeaLeafDivinationIntroShown  = 0x40,
    flGammaHigh                    = 0x80,
} HeaderFlags;

extern SaveHeader g_saveHeader;  // 0x03005598

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
