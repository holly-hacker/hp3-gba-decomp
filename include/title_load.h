#pragma once

#include "types.h"
#include "pause_menu.h"

// The No/Yes prompt shown by SelectNewGameSlot_candidate.
extern const ListMenuDefinition g_NewGameSlotConfirmationMenuDefinition;  // 0x0806C024

void HandleSaveLoadContinuation(void);
extern void SelectNewGameSlot_candidate(void);
extern void ResolveOverwriteConfirmation_candidate(void);
void InitializeLoadGame(void);
void UpdateLoadGame(void);
