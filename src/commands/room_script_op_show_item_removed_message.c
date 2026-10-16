#include "types.h"
#include "commands.h"
#include "dialog.h"
#include "dialog_box.h"
#include "font.h"
#include "text.h"
#include "overworld/room_script.h"
#include "inventory.h"

typedef struct ShowItemRemovedMessageRecord {
    u32 dwOpcode;
    u8 bRewardId;
    u8 bDialogArg1C;
    u8 bDialogArg1D;
} ShowItemRemovedMessageRecord;

void RoomScriptOpShowItemRemovedMessage(ShowItemRemovedMessageRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    SetTextMacro1String(GetDialogText(GetRewardNameStringId_candidate(pRecord->bRewardId)));
    SetTextMacro3String(GetDialogText(GetRewardNameStringId_candidate(pRecord->bRewardId)));
    ShowRoomDialogBox_candidate(0x28e);
    g_DialogState_candidate.bArg1C = pRecord->bDialogArg1C;
    g_DialogState_candidate.bArg1D = pRecord->bDialogArg1D;
}
