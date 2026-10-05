#pragma once

#include "types.h"
#include "graphics/object.h"
#include "gen/graphics/minigames/hippogriff.h"

// US adds a Language row.
#ifdef VERSION_JP
#define OPTIONS_MENU_ITEM_COUNT 7
#else
#define OPTIONS_MENU_ITEM_COUNT 8
#endif

typedef struct {
    Object *apObjects[OPTIONS_MENU_ITEM_COUNT];  // 0x00
    u32 dwMusicVolume;     // US 0x20, JP 0x1C
    u32 dwSoundVolume;     // US 0x24, JP 0x20
    u32 dwGammaHigh;       // US 0x28, JP 0x24
} OptionsState;

extern OptionsState g_OptionsState;  // 0x03005DD0

// One row of the options screen, 0x18 bytes each.
typedef struct {
    const void *pTileGfx;
    const void *pFrameData;  // 0x04
    u32 dwUnk08;
    u32 dwUnk0C;
    const void *pPalette;    // 0x10
    s16 nX;                  // 0x14
    s16 nY;                  // 0x16
} OptionsMenuItem;

extern const OptionsMenuItem g_aOptionsMenuItems[OPTIONS_MENU_ITEM_COUNT];  // 0x0806C048

extern u32 g_dwOptionsReturnMode;      // 0x03005E04: mode that opened the options screen
extern u8 g_bOptionsSavedMusicVolume;  // 0x03005E08: settings kept across the language select trip
extern u8 g_bOptionsSavedSoundVolume;  // 0x03005E09
extern u8 g_bOptionsSavedGammaHigh;    // 0x03005E0A
extern u32 g_dwOptionsEntryLanguage;   // 0x03005E0C: language when the screen was entered

extern const u8 g_abGammaNormalRemap[32];  // 0x0804D798
extern const u8 g_abGammaHighRemap[32];    // 0x0804D7B8
// Approximate inverse of g_abGammaHighRemap, used to undo it.
extern const u8 g_abGammaHighInverseRemap[32];  // 0x0804D7D8

extern void ApplyGammaRemapTable(const u8 *pTable);
extern void MoveOptionsCursor_candidate(void);
extern void AdjustOptionValue_candidate(void);
extern void BuildOptionsScreen_candidate(void);
