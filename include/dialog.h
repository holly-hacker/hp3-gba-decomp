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

// Fill text macro @N (sTextMacroTable slot N - 1) with a string or a signed
// decimal number.
extern void SetTextMacroString(const u8 *pString, u32 slot);
extern void SetTextMacro1String(const u8 *pString);
extern void SetTextMacro2String(const u8 *pString);
extern void SetTextMacro3String(const u8 *pString);
extern void SetTextMacroNumber(s32 value, u32 slot);
extern void SetTextMacro1Number(s32 value);
extern void SetTextMacro2Number(s32 value);
extern void SetTextMacro3Number(s32 value);
// Dialog string id for a reward id (item, card or Sickles).
extern u32 GetRewardNameStringId_candidate(u32 rewardId);
// Sets the dialog block to show and pushes the dialog game mode.
extern void ShowRoomDialogBox_candidate(u32 blockId);

extern void sub_0801FBA4(u32 arg);  // stores a byte at DialogState + 0x18
