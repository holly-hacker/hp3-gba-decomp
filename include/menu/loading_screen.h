#pragma once

#include "types.h"
#include "graphics/object.h"
#include "graphics/scanline_effects.h"

// Game mode 0x1A (LoadingScreen): the story-stage choice pushed by the room script op
// ShowLoadingScreenTransition; see docs/formats/save.md ("Loading-screen story-stage choice").
// The mode's three arguments are the story stages offered by the options.
#define LOADING_SCREEN_OPTION_COUNT 3

typedef struct LoadingScreenState {
    Object *pCursorObject;                              // 0x00
    Object *apOptionObjects[LOADING_SCREEN_OPTION_COUNT];  // 0x04
    void *pBgTilemap;                                   // 0x10, BG2 panel graphic
    u8 abOptionStage[LOADING_SCREEN_OPTION_COUNT];      // 0x14, story stage each option selects
    u8 bPreviousStage;                                  // 0x17, story stage before the choice
    u8 bStageRow;                                       // 0x18, index of the current stage in g_abLoadingScreenStages
    u8 bInputDelay;                                     // 0x19, frames before A is accepted
    u8 bSavedBg2Priority;                               // 0x1A
} LoadingScreenState;
extern LoadingScreenState g_LoadingScreenState;  // 0x03002260
extern u32 g_dwLoadingScreenBgRow;               // 0x0300227C, BG2 tile row of the panel

// Per stage row (a stage's position in abStages): the text variant shown for each option
// selection (0 = none), then a bitmask of the options present.
typedef struct LoadingScreenTables {
    u8 abStages[7];             // story stage per row, ended by 0xFF
    u8 aabOptionRows[6][4];
} LoadingScreenTables;
extern const LoadingScreenTables g_LoadingScreenTables;  // 0x0804D6CC

// Per stage row: 1 when only two options are offered. A label inside the raw data that
// precedes the scanline table.
extern const u8 g_abLoadingScreenTwoOptions[6];  // 0x0804D76A
extern const ScanlineEffectEntry g_aLoadingScreenScanlineEffects[2];  // 0x0804D770

extern void InitializeLoadingScreen(void);
extern void UpdateLoadingScreen(void);
extern void ExitLoadingScreen(void);

extern void sub_0800C344(void);  // creates the option objects
extern void sub_0800C3FC(void);  // draws the panel and text for the current selection
extern void sub_0800C618(u32 *pPayload0, u32 *pPayload1);
extern void sub_0800C674(u32 *pPayload0, u32 *pPayload1);
extern s32 sub_0800C6D0(void);  // BG tile row of the panel from the camera Y
