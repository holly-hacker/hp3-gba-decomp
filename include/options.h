#pragma once

#include "types.h"
#include "object.h"

typedef struct {
    Object *apObjects[8];  // 0x00
    u32 dwMusicVolume;     // 0x20
    u32 dwSoundVolume;     // 0x24
    u32 dwGammaHigh;       // 0x28
} OptionsState;

extern OptionsState g_OptionsState;  // 0x03005DD0

// One row of the options screen, 0x18 bytes each.
typedef struct {
    const void *pUnk00_candidate;
    const void *pUnk04_candidate;
    u32 dwUnk08_candidate;
    u32 dwUnk0C_candidate;
    const void *pObjectData_candidate;
    s16 nX;
    s16 nY;
} OptionsMenuItem;

extern const OptionsMenuItem g_aOptionsMenuItems[8];  // 0x0806C048

extern u32 g_dwOptionsReturnMode;      // 0x03005E04: mode that opened the options screen
extern u8 g_bOptionsSavedMusicVolume;  // 0x03005E08: settings kept across the language select trip
extern u8 g_bOptionsSavedSoundVolume;  // 0x03005E09
extern u8 g_bOptionsSavedGammaHigh;    // 0x03005E0A
extern u32 g_dwOptionsEntryLanguage;   // 0x03005E0C: language when the screen was entered

extern const u8 g_abGammaNormalRemap[];  // 0x0804D798
extern const u8 g_abGammaHighRemap[];    // 0x0804D7B8
extern const u8 g_MenuScreenGraphic[];   // 0x08DE5214

extern void ApplyGammaRemapTable(const u8 *pTable);
extern void MoveOptionsCursor_candidate(void);
extern void AdjustOptionValue_candidate(void);
extern void BuildOptionsScreen_candidate(void);
