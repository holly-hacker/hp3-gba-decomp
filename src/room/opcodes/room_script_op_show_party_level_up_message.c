#include "types.h"
#include "dialog.h"
#include "room_script.h"

void RoomScriptOpShowPartyLevelUpMessage(RoomScriptRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    SetDialogMacroNumber0_candidate(pRecord->operand.ab[0]);
    SetDialogMacroNumber1_candidate(pRecord->operand.ab[0]);
    ShowRoomDialogBox_candidate(0x293);
    g_DialogState_candidate.bArg1C = pRecord->operand.ab[1];
    g_DialogState_candidate.bArg1D = pRecord->operand.ab[2];
}
