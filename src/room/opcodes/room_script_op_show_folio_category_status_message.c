#include "types.h"
#include "dialog.h"
#include "text.h"
#include "room_script.h"

void RoomScriptOpShowFolioCategoryStatusMessage(RoomScriptRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    SetDialogMacroString0_candidate(GetDialogText(pRecord->operand.ab[0] + 0x405));
    SetDialogMacroString1_candidate(GetDialogText(pRecord->operand.ab[0] + 0x405));
    if (pRecord->operand.ab[1] != 0)
        ShowRoomDialogBox_candidate(0x291);
    else
        ShowRoomDialogBox_candidate(0x290);
    g_DialogState_candidate.bArg1C = pRecord->operand.ab[2];
    g_DialogState_candidate.bArg1D = pRecord->operand.ab[3];
}
