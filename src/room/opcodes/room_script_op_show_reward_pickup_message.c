#include "types.h"
#include "audio.h"
#include "dialog.h"
#include "text.h"
#include "room_script.h"

void RoomScriptOpShowRewardPickupMessage(RoomScriptRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    PlaySoundEffect_candidate(0x1a);
    SetTextMacro1String(GetDialogText(GetRewardNameStringId_candidate(pRecord->operand.ab[0])));
    SetTextMacro3String(GetDialogText(GetRewardNameStringId_candidate(pRecord->operand.ab[0])));
    if (pRecord->operand.ab[0] <= 0x4e)
        ShowRoomDialogBox_candidate(0x28d);
    else
        ShowRoomDialogBox_candidate(0x295);
    g_DialogState_candidate.bArg1C = pRecord->operand.ab[1];
    g_DialogState_candidate.bArg1D = pRecord->operand.ab[2];
}
