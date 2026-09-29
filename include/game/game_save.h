#pragma once

#include "types.h"

extern const u8 g_SaveMenuBg1Graphic[];  // 0x08DF2664

extern void ShowSaveConfirmationPrompt_candidate(u32 stringId);
extern void ShowSavingMessage_candidate(void);
extern void ShowGameSavedMessage_candidate(void);
extern void ResolveSaveConfirmation_candidate(void);
extern void TickBlendFadeOut_candidate(void);
extern void SaveGameToSlot(u32 slot);
