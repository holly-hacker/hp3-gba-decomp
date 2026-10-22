#pragma once

#include "types.h"
#include "actor.h"

// Rows of the options screen; the cursor is in dwModeScratchB. US adds a
// Language row.
typedef enum {
    OptionsRowSound = 0,
    OptionsRowMusic = 1,
    OptionsRowGamma = 2,
#ifndef VERSION_JP
    OptionsRowLanguage = 3,
#endif
    OPTIONS_ROW_COUNT
} OptionsRow;

// g_aOptionsMenuItems and OptionsState.apActors: one icon per row, then a
// bar and a knob each for the Sound and Music rows.
typedef enum {
    OptionsItemSoundBar = OPTIONS_ROW_COUNT,
    OptionsItemMusicBar,
    OptionsItemSoundKnob,
    OptionsItemMusicKnob,
    OPTIONS_MENU_ITEM_COUNT
} OptionsMenuItemIndex;

typedef struct {
    Actor *apActors[OPTIONS_MENU_ITEM_COUNT];  // 0x00
    u32 adwValues[OPTIONS_ROW_COUNT];          // US 0x20, JP 0x1C: by OptionsRow; Language's is unused
} OptionsState;

extern OptionsState g_OptionsState;  // 0x03005DD0

// One row of the options screen, 0x18 bytes each.
typedef struct {
    ActorAssetRecord asset;  // its own palette is null; pPalette is attached at spawn
    const void *pPalette;    // 0x10
    s16 nX;                  // 0x14
    s16 nY;                  // 0x16
} OptionsMenuItem;

extern const OptionsMenuItem g_aOptionsMenuItems[OPTIONS_MENU_ITEM_COUNT];  // 0x0806C048

// The Sound and Music knobs' spin animations, with the knobs out of phase.
extern const u8 g_aabOptionsKnobAnims[2][18];

extern u32 g_dwOptionsReturnMode;      // 0x03005E04: mode that opened the options screen
extern u8 g_bOptionsSavedMusicVolume;  // 0x03005E08: settings kept across the language select trip
extern u8 g_bOptionsSavedSoundVolume;  // 0x03005E09
extern u8 g_bOptionsSavedGammaHigh;    // 0x03005E0A
extern u32 g_dwOptionsEntryLanguage;   // 0x03005E0C: language when the screen was entered

void InitializeOptions(void);
void UpdateOptions(void);
void BuildOptionsScreen(void);
// Positions a volume knob, or draws the gamma setting's name.
void DrawOptionValue(u32 row, s32 value);
void MoveOptionsCursor(void);
void AdjustOptionValue(void);
void ExitOptions(void);
void DrawOptionsRowLabel(u32 row, u32 selectedRow);
// Shows the Language row's hint while it is selected (US), else clears it.
void DrawOptionsLanguageHint(void);
