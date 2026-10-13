#pragma once

#include "types.h"
#include "actor.h"
#include "graphics/scanline_effects.h"

// Game mode 0x1A (ChooseCharacter): the story-stage choice pushed by the room script op
// ShowChooseCharacter; see docs/formats/save.md ("Choose-character story-stage choice").
// The mode's three arguments are the story stages offered by the options.
#define CHOOSE_CHARACTER_OPTION_COUNT 3

typedef struct ChooseCharacterState {
    Actor *pCursorActor;                                // 0x00
    Actor *apOptionActors[CHOOSE_CHARACTER_OPTION_COUNT];// 0x04
    void *pBgTilemap;                                   // 0x10, BG2 panel graphic
    u8 abOptionStage[CHOOSE_CHARACTER_OPTION_COUNT];    // 0x14, story stage each option selects
    u8 bPreviousStage;                                  // 0x17, story stage before the choice
    u8 bStageRow;                                       // 0x18, index of the current stage in g_abChooseCharacterStages
    u8 bInputDelay;                                     // 0x19, frames before A is accepted
    u8 bSavedBg2Priority;                               // 0x1A
} ChooseCharacterState;
extern ChooseCharacterState g_ChooseCharacterState;  // 0x03002260
extern u32 g_dwChooseCharacterBgRow;             // 0x0300227C, BG2 tile row of the panel

// Per stage row (a stage's position in abStages): the text variant shown for each option
// selection (0 = none), then a bitmask of the options present.
typedef struct ChooseCharacterTables {
    u8 abStages[7];             // story stage per row, ended by 0xFF
    u8 aabOptionRows[6][4];
} ChooseCharacterTables;
extern const ChooseCharacterTables g_ChooseCharacterTables;  // 0x0804D6CC

// Per stage row: 1 when only two options are offered. A label inside the raw data that
// precedes the scanline table.
extern const u8 g_abChooseCharacterTwoOptions[6];  // 0x0804D76A
extern const ScanlineEffectEntry g_aChooseCharacterScanlineEffects[2];  // 0x0804D770

extern void InitializeChooseCharacter(void);
extern void UpdateChooseCharacter(void);
extern void ExitChooseCharacter(void);

extern void sub_0800C344(void);  // creates the option actors
extern void sub_0800C3FC(void);  // draws the panel and text for the current selection
extern void sub_0800C618(u32 *pPayload0, u32 *pPayload1);
extern void sub_0800C674(u32 *pPayload0, u32 *pPayload1);
extern s32 sub_0800C6D0(void);  // BG tile row of the panel from the camera Y
