#pragma once

#include "types.h"

// Dialog box state at 0x03002E88; only the fields room scripts touch are named.
typedef struct DialogState {
    u8 pad_00[0x0C];
    u16 wBlockId;  // 0x0C, set by ShowRoomDialogBox_candidate
    u8 pad_0E[0x0E];
    u8 bArg1C;     // 0x1C, forwarded from room-script dialog opcodes
    u8 bArg1D;     // 0x1D
} DialogState;
extern DialogState g_DialogState_candidate;

// Copy a string into the first/second text macro buffer (the @1/@2 slots of
// dialog text).
extern void SetDialogMacroString0_candidate(const u8 *pString);
extern void SetDialogMacroString1_candidate(const u8 *pString);
extern void SetDialogMacroNumber0_candidate(u32 value);
extern void SetDialogMacroNumber1_candidate(u32 value);
// Dialog string id for a reward id (item, card or Sickles).
extern u32 GetRewardNameStringId_candidate(u32 rewardId);
// Sets the dialog block to show and pushes the dialog game mode.
extern void ShowRoomDialogBox_candidate(u32 blockId);
