#pragma once

#include "types.h"

// Dialog box state at 0x03002E88; only the fields room scripts touch are named.
typedef struct DialogState {
    u32 dwState;                // 0x00, 0 = no box, 1 = open (InitializeDialogue), 2 = closed by
                                //       ExitDialogue; the next vblank's sub_0801FBBC resets 2 to 0
    u8 pad_04[0x08];
    u16 wBlockId;               // 0x0C, set by ShowRoomDialogBox_candidate
    u8 pad_0E[0x08];
    u16 wRevealStep_candidate;  // 0x16, added to the halfword at 0x10 per reveal step (sub_0801FD64); defaults to 1
    u8 pad_18[0x04];
    u8 bArg1C;     // 0x1C, forwarded from room-script dialog opcodes
    u8 bArg1D;     // 0x1D
} DialogState;
extern DialogState g_DialogState_candidate;

// Destination for expanding text macros (@1, @2, ...) into a dialog string
// before it is drawn (sub_08020EB8); allocated once by InitDialogBox.
#define DIALOG_MACRO_EXPAND_BUFFER_SIZE 0x400
extern u8 *g_pDialogMacroExpandBuffer;

extern void InitDialogBox(void);

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
