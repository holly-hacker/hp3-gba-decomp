#pragma once

#include "types.h"
#include "gen/graphics/minigames/hippogriff.h"


extern void ShowSaveConfirmationPrompt_candidate(u32 stringId);
extern void ShowSavingMessage_candidate(void);
extern void ShowGameSavedMessage_candidate(void);
extern void ResolveSaveConfirmation_candidate(void);
extern void TickMenuFadeIn(void);
extern void SaveGameToSlot(u32 slot);
