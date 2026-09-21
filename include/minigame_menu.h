#pragma once

#include "types.h"
#include "object.h"

extern const u32 g_dwMinigameMenuBg3Control;  // 0x0806605C
extern const u32 g_dwMinigameMenuBg1Control;  // 0x08066060

extern u32 g_dwSelectedMinigame;  // 0x03003F88: minigame index passed to the difficulty select

extern void DrawMinigameSelectMenu(void);
extern void HandleMinigameMenuSelection(u32 index);
extern void BeginMinigameSwitchFade_candidate(void);
extern u32 TickMinigameSwitchFadeOut_candidate(void);
extern void SwapMinigameSelection_candidate(void);
extern void TickMinigameSwitchFadeIn_candidate(void);
extern u32 StepWrappedSelectionHorizontal_candidate(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player);
extern void SetObjectMoveTargetWithDuration_candidate(Object *pObject, s32 x, s32 y, s32 duration);
