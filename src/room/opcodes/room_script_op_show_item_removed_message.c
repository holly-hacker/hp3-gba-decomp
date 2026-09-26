#include "types.h"
#include "dialog.h"
#include "text.h"
#include "room_script.h"

void RoomScriptOpShowItemRemovedMessage(RoomScriptRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    SetTextMacro1String(GetDialogText(GetRewardNameStringId_candidate(pRecord->operand.ab[0])));
    SetTextMacro3String(GetDialogText(GetRewardNameStringId_candidate(pRecord->operand.ab[0])));
    ShowRoomDialogBox_candidate(0x28e);
    g_DialogState_candidate.bArg1C = pRecord->operand.ab[1];
    g_DialogState_candidate.bArg1D = pRecord->operand.ab[2];
}
