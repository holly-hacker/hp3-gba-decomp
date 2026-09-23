#pragma once

#include "types.h"
#include "object.h"

extern const u32 g_dwMinigameMenuBg3Control;  // 0x0806605C
extern const u32 g_dwMinigameMenuBg1Control;  // 0x08066060

extern u32 g_dwSelectedMinigame;  // 0x03003F88: minigame index passed to the difficulty select

extern u32 g_dwListMenuSelection;  // 0x03003F14: the same word as g_GameModeStackContext.dwModeScratchB,
                                   // the selected row of a minigame's results/pause menu

// Shared by the minigame screens.
extern void sub_0800A598(const void *pTable, const void *pBgControls, u32 count);
extern void sub_0802CEE4(void *pObjectGroup);  // frees the objects a group owns
extern void sub_0803FF04(void);
extern void sub_080075C0(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5);

// Shared minigame exit teardown: DisableKrawall, sub_0803C178, EnableKrawall.
extern void sub_0802CDB8(void);

extern void DrawMinigameSelectMenu(void);
extern void HandleMinigameMenuSelection(u32 index);
extern void BeginMinigameSwitchFade_candidate(void);
extern u32 TickMinigameSwitchFadeOut_candidate(void);
extern void SwapMinigameSelection_candidate(void);
extern void TickMinigameSwitchFadeIn_candidate(void);
extern u32 StepWrappedSelectionHorizontal_candidate(u32 *pValue, u32 min, u32 max, s32 wrap, u32 player);
extern void SetObjectMoveTargetWithDuration_candidate(Object *pObject, s32 x, s32 y, s32 duration);
