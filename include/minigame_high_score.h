#pragma once

#include "types.h"
#include "actor.h"

// Helpers shared by the minigames: the HUD text panel and the save made on exit.

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

extern const ActorAssetRecord g_MinigameTextPanelCapAsset;     // 0x0806603C
extern const ActorAssetRecord g_MinigameTextPanelMiddleAsset;  // 0x0806604C

extern MinigameTextPanel *SpawnMinigameTextPanel(s32 x, s32 y, s32 widthTiles, u8 priority);
extern void FreeMinigameTextPanel(MinigameTextPanel *pPanel);

// Shared minigame exit teardown: DisableKrawall, SyncSaveOptionsIfDirty, EnableKrawall.
extern void SyncSaveOptionsPausingKrawall(void);
