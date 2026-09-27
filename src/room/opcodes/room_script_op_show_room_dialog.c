#include "types.h"
#include "audio.h"
#include "dialog.h"
#include "room_script.h"

void RoomScriptOpShowRoomDialog(RoomScriptRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;

    if (pRecord->operand.aw[0] == 0x270)
        PlaySoundById(0x24);
    else
        PlaySoundById(5);

    ShowRoomDialogBox_candidate(pRecord->operand.aw[0]);
    g_DialogState_candidate.bArg1C = pRecord->operand.ab[2];
    g_DialogState_candidate.bArg1D = pRecord->operand.ab[3];
}
