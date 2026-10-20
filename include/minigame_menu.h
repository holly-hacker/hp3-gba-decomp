#pragma once

#include "types.h"
#include "save.h"

extern const u32 g_dwMinigameMenuBg3Control;  // 0x0806605C
extern const u32 g_dwMinigameMenuBg1Control;  // 0x08066060
// Large "1"-"4" numeral of each minigame, drawn on BG3 at tile column g_adwMinigameMenuNumberX[i], row 5.
extern const u8 *const g_apMinigameMenuNumbers[4];  // 0x08066064
extern const u32 g_adwMinigameMenuNumberX[4];       // 0x08066074

extern void HandleMinigameSelectMenuConfirm(void);
extern void InitializeMinigameMenu(void);
extern void ExitMinigameMenu(void);
extern void DrawMinigameSelectMenu(void);
extern void HandleMinigameMenuSelection(u32 index);
extern void ShowMinigameLockedMessageIfNeeded(u32 index);
extern void BeginMinigameSwitchFade(void);
extern u32 TickMinigameSwitchFadeOut(void);
extern void SwapMinigameSelection(void);
extern void TickMinigameSwitchFadeIn(void);

// Whether the minigame menu entry at index has been unlocked.
#define IS_MINIGAME_UNLOCKED(index)                                                              \
    (((index) == 0   ? g_saveManager.header.bHeaderFlags.all & flWizardCrackerPopItUnlocked     \
      : (index) == 1 ? g_saveManager.header.bHeaderFlags.all & flBuckbeakUnlocked               \
      : (index) == 2 ? g_saveManager.header.bHeaderFlags.all & flBoggartUnlocked                \
                     : g_saveManager.header.bHeaderFlags.all & flTeaLeafDivinationUnlocked) != 0)
