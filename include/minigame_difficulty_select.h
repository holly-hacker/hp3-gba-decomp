#pragma once

#include "types.h"
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
extern void DrawMinigameDifficultyRow(s32 row, u32 fontColor);
// Draws the selected difficulty's saved high score, or clears the area for the other rows.
extern void DrawMinigameDifficultyHighScore(s32 row);

extern void HandleHighScoreDifficultyMenuTick(void);
extern void InitializeWizardCrackerPopItDifficultySelect(void);
extern void ExitWizardCrackerPopItDifficultySelect(void);

extern s32 g_dwSelectedMinigame;  // 0x03003F88: minigame index passed to the difficulty select
