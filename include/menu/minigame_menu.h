#pragma once

#include "types.h"
#include "actor.h"

extern const u32 g_dwMinigameMenuBg3Control;  // 0x0806605C
extern const u32 g_dwMinigameMenuBg1Control;  // 0x08066060

extern u32 g_dwListMenuSelection;  // 0x03003F14: the same word as g_GameModeStackContext.dwModeScratchB,
                                   // the selected row of a minigame's results/pause menu

// Text actors: SpawnTextActor spawns an actor that draws *ppText and files it in
// g_apTextActors[slot]; SetTextActorCenterPosition_candidate centers it on x.
extern Actor *g_apTextActors[17];  // 0x03005D10
extern Actor *SpawnTextActor(const u8 **ppText, u32 slot);
extern void SetTextActorCenterPosition_candidate(Actor *pActor, s32 x, s32 y);

extern void sub_0803FF04(void);

extern void DrawMinigameSelectMenu(void);
extern void HandleMinigameMenuSelection(u32 index);
extern void BeginMinigameSwitchFade_candidate(void);
extern u32 TickMinigameSwitchFadeOut_candidate(void);
extern void SwapMinigameSelection_candidate(void);
extern void TickMinigameSwitchFadeIn_candidate(void);
