#pragma once

#include "actor.h"
#include "pause_menu.h"

// The No/Yes prompt shown by SelectNewGameSlot.
extern const ListMenuDefinition g_NewGameSlotConfirmationMenuDefinition;  // 0x0806C024

// The bar behind each save slot row, also used for the slot cursor.
extern const ActorAssetRecord g_SaveSlotBarAsset;

extern Actor *g_pSaveSlotCursorActor;  // 0x03005DC8

void HandleSaveLoadContinuation(void);
void SpawnSaveSlotActors(void);
// Draws one slot's objective, level and playtime, or "Empty".
void DrawSaveSlot(u32 slot, u32 selectedSlot);
void SelectNewGameSlot(void);
void ResolveOverwriteConfirmation(void);
void InitializeLoadGame(void);
void UpdateLoadGame(void);
