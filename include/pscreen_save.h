#pragma once

#include "types.h"
#include "pause_menu.h"

// Shared by the save, new game slot and trade confirmation prompts.
extern const ListMenuDefinition g_SaveConfirmationMenuDefinition;  // 0x0806B214
extern const ListMenuEntry g_aNoYesEntries[2];  // 0x0806B238

extern void InitializeGameSave(void);
extern void UpdateGameSave(void);
extern void ExitGameSave(void);
extern void ShowSaveConfirmationPrompt_candidate(u32 stringId);
extern void ShowSavingMessage_candidate(void);
extern void ShowGameSavedMessage_candidate(void);
extern void ResolveSaveConfirmation_candidate(void);
