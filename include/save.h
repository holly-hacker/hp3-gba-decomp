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
