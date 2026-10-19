#pragma once

#include "types.h"

// Result of the save slot screen, set by HandleSaveSlotInput.
typedef enum {
    SaveSlotResultConfirmed = 1,
    SaveSlotResultCancelled = 2,
} SaveSlotScreenResult;

extern u8 g_bSaveSlotScreenResult;  // 0x03005DC4

void InitializeNewGameMenu(void);
void UpdateNewGameMenu(void);
void ExitNewGameMenu(void);
void InitializeSaveSlotScreen(u32 titleStringId);
// Returns 1 when A picked the selected slot.
u32 HandleSaveSlotInput(void);
void ExitSaveSlotScreen(void);
void DrawSaveSlots(void);
void StartNewGame(void);
void ConfirmLoadGameSlot(void);
void MoveSaveSlotCursor(void);
