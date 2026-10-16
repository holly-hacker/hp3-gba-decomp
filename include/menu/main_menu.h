#pragma once

#include "types.h"

// Result of the save slot screen, set by HandleSaveSlotInput_candidate.
typedef enum {
    SaveSlotResultConfirmed = 1,
    SaveSlotResultCancelled = 2,
} SaveSlotScreenResult;

extern u8 g_bSaveSlotScreenResult;  // 0x03005DC4

extern void InitializeSaveSlotScreen_candidate(u32 titleStringId);
extern u32 HandleSaveSlotInput_candidate(void);
extern void SelectNewGameSlot_candidate(void);
extern void ResolveOverwriteConfirmation_candidate(void);
extern void ExitSaveSlotScreen_candidate(void);
extern void ConfirmLoadGameSlot_candidate(void);
extern void InitRoomState(void);
