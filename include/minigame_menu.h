#pragma once

#include "types.h"
#include "actor.h"

extern const u32 g_dwMinigameMenuBg3Control;  // 0x0806605C
extern const u32 g_dwMinigameMenuBg1Control;  // 0x08066060

extern void HandleMinigameSelectMenuConfirm(void);
extern void InitializeMinigameMenu(void);
extern void ExitMinigameMenu(void);
extern void DrawMinigameSelectMenu(void);
extern void HandleMinigameMenuSelection(u32 index);
extern void BeginMinigameSwitchFade_candidate(void);
extern u32 TickMinigameSwitchFadeOut_candidate(void);
extern void SwapMinigameSelection_candidate(void);
extern void TickMinigameSwitchFadeIn_candidate(void);
