#pragma once

#include "types.h"
#include "actor.h"
#include "video.h"

// Game mode 0x1A (ChooseCharacter): the story-stage choice pushed by the room script op
// ShowChooseCharacter.
// The mode's three arguments are the story stages offered by the options.
#define CHOOSE_CHARACTER_OPTION_COUNT 3

typedef struct ChooseCharacterState {
    Actor *pCursorActor;                                // 0x00
    Actor *apOptionActors[CHOOSE_CHARACTER_OPTION_COUNT];// 0x04
    const u16 *pBgTilemap;                                   // 0x10, BG2 panel graphic
    u8 abOptionStage[CHOOSE_CHARACTER_OPTION_COUNT];    // 0x14, story stage each option selects
    u8 bPreviousStage;                                  // 0x17, story stage before the choice
    u8 bStageRow;                                       // 0x18, index of the current stage in g_abChooseCharacterStages
    u8 bInputDelay;                                     // 0x19, frames before A is accepted
    u8 bSavedBg2Priority;                               // 0x1A
} ChooseCharacterState;
extern ChooseCharacterState g_ChooseCharacterState;  // 0x03002260
extern u32 g_dwChooseCharacterBgRow;             // 0x0300227C, BG2 tile row of the panel

// Story stage per row, ended by 0xFF. A row is the current stage's position in this list.
extern const u8 g_abChooseCharacterStages[7];

// Per stage row: the name variant shown for each cursor position (0 = none; 1 Harry, 2 Hermione,
// 3 Harry and Hermione, 4 Ron, 5 Harry and Ron, 6 Ron and Hermione), then a bitmask of the
// option actors present.
extern const u8 g_aabChooseCharacterOptionRows[6][4];

// Per stage row and cursor position: the objective text shown under the character name.
extern const u32 g_aadwChooseCharacterObjectiveTextIds[6][CHOOSE_CHARACTER_OPTION_COUNT];

// The X pixel of each option actor, indexed [stage row][cursor position][option actor].
extern const u8 g_aaabChooseCharacterActorX[6][3][3];

// Per stage row: 1 when only two options are offered.
extern const u8 g_abChooseCharacterTwoOptions[6];
extern const ScanlineEffectEntry g_aChooseCharacterScanlineEffects[2];

extern void InitializeChooseCharacter(void);
extern void UpdateChooseCharacter(void);
extern void ExitChooseCharacter(void);

extern void SpawnChooseCharacterOptionActors(void);  // one actor per option; hides those absent from the row's bitmask
extern void DrawChooseCharacterSelection(void);  // redraws the panel, name, objective and actor positions
// Scanline callbacks at lines 0x3F and 0x7F: show the panel through window 0, then restore BG2.
extern void BeginChooseCharacterPanelScanline(u32 *pPayload0, u32 *pPayload1);
extern void EndChooseCharacterPanelScanline(u32 *pPayload0, u32 *pPayload1);
extern s32 GetChooseCharacterPanelBgRow(void);  // BG tile row of the panel from the camera Y
