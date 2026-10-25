#pragma once

#include "types.h"
#include "pause_menu.h"

// Shared by the save, new game slot and trade confirmation prompts.
extern const ListMenuDefinition g_SaveConfirmationMenuDefinition;
extern const ListMenuEntry g_aNoYesEntries[2];

extern void InitializeGameSave(void);
extern void UpdateGameSave(void);
extern void ExitGameSave(void);
extern void ShowSaveConfirmationPrompt(u32 stringId);
extern void ShowSavingMessage(void);
extern void ShowGameSavedMessage(void);
extern void ResolveSaveConfirmation(void);
