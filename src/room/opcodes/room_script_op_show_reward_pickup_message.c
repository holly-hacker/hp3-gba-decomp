#include "types.h"
#include "audio.h"
#include "dialog.h"
#include "text.h"
#include "room_script.h"

typedef struct ShowRewardPickupMessageRecord {
    u32 dwOpcode;
    u8 bRewardId;
    u8 bDialogArg1C;
    u8 bDialogArg1D;
} ShowRewardPickupMessageRecord;

void RoomScriptOpShowRewardPickupMessage(ShowRewardPickupMessageRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    PlaySoundEffect_candidate(0x1a);
    SetTextMacro1String(GetDialogText(GetRewardNameStringId_candidate(pRecord->bRewardId)));
    SetTextMacro3String(GetDialogText(GetRewardNameStringId_candidate(pRecord->bRewardId)));
    if (pRecord->bRewardId <= 0x4e)
        ShowRoomDialogBox_candidate(0x28d);
    else
        ShowRoomDialogBox_candidate(0x295);
    g_DialogState_candidate.bArg1C = pRecord->bDialogArg1C;
    g_DialogState_candidate.bArg1D = pRecord->bDialogArg1D;
}
