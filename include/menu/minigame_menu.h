#pragma once

#include "types.h"
#include "actor.h"

extern const u32 g_dwMinigameMenuBg3Control;  // 0x0806605C
extern const u32 g_dwMinigameMenuBg1Control;  // 0x08066060

extern s32 g_dwSelectedMinigame;  // 0x03003F88: minigame index passed to the difficulty select

extern u32 g_dwListMenuSelection;  // 0x03003F14: the same word as g_GameModeStackContext.dwModeScratchB,
                                   // the selected row of a minigame's results/pause menu

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

// Text actors: SpawnTextActor spawns an actor that draws *ppText and files it in
// g_apTextActors[slot]; SetTextActorCenterPosition_candidate centers it on x.
extern Actor *g_apTextActors[17];  // 0x03005D10
extern Actor *SpawnTextActor(const u8 **ppText, u32 slot);
extern void SetTextActorCenterPosition_candidate(Actor *pActor, s32 x, s32 y);

extern MinigameTextPanel *SpawnMinigameTextPanel(s32 x, s32 y, s32 widthTiles, u32 priority);
extern void FreeMinigameTextPanel(MinigameTextPanel *pPanel);
extern void sub_0803FF04(void);

// Shared minigame exit teardown: DisableKrawall, SyncSaveOptionsIfDirty, EnableKrawall.
extern void SyncSaveOptionsPausingKrawall(void);

extern void DrawMinigameSelectMenu(void);
extern void HandleMinigameMenuSelection(u32 index);
extern void BeginMinigameSwitchFade_candidate(void);
extern u32 TickMinigameSwitchFadeOut_candidate(void);
extern void SwapMinigameSelection_candidate(void);
extern void TickMinigameSwitchFadeIn_candidate(void);
