#pragma once

#include "types.h"

extern void InitializeGameSave(void);
extern void UpdateGameSave(void);
extern void ExitGameSave(void);
extern void ShowSaveConfirmationPrompt_candidate(u32 stringId);
extern void ShowSavingMessage_candidate(void);
extern void ShowGameSavedMessage_candidate(void);
extern void ResolveSaveConfirmation_candidate(void);
