#pragma once

#include "types.h"
#include "actor.h"
#include "modes.h"

// Minigame difficulty select, game mode 0x1E (MinigameDifficultySelect). Rows 0-2 pick
// Easy/Medium/Hard for the minigame in g_dwSelectedMinigame; row 3, "Erase High Scores",
// is only offered once the minigame has a saved score. The selected row is kept in
// g_GameModeStackContext.dwModeScratchB.

#define MINIGAME_DIFFICULTY_COUNT 3
#define MINIGAME_ERASE_SCORES_ROW 3

extern const u32 g_adwMinigameDifficultyTextIds[4];  // 0x0806601C: "Easy", "Medium", "Hard", "Erase High Scores"
extern const GameMode g_aeMinigameDifficultyModes[4];  // 0x0806602C: mode started for each minigame

// Draws one row of the menu in the given font color.
extern void sub_0802CB80(u32 row, u32 fontColor);
// Draws the selected difficulty's saved high score, or clears the area for the other rows.
extern void sub_0802CC44(u32 row);

extern void HandleHighScoreDifficultyMenuTick(void);
extern void InitializeWizardCrackerPopItDifficultySelect(void);
extern void ExitWizardCrackerPopItDifficultySelect(void);

extern s32 g_dwSelectedMinigame;  // 0x03003F88: minigame index passed to the difficulty select

// A horizontal panel of actors drawn behind a minigame's HUD text: end caps at
// x and x + widthTiles * 8 (the right one flipped) and widthTiles - 4 middle
// pieces between them. The Boggart minigame puts one behind the score and one
// behind the lives counter.
typedef struct MinigameTextPanel {
    Actor *pLeftCap;
    Actor *pRightCap;
    Actor **ppMiddlePieces;  // NULL when there are none
    s32 middleCount;
} MinigameTextPanel;

extern MinigameTextPanel *SpawnMinigameTextPanel(s32 x, s32 y, s32 widthTiles, u32 priority);
extern void FreeMinigameTextPanel(MinigameTextPanel *pPanel);

// Shared minigame exit teardown: DisableKrawall, SyncSaveOptionsIfDirty, EnableKrawall.
extern void SyncSaveOptionsPausingKrawall(void);
