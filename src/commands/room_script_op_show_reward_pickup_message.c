#include "types.h"
#include "commands.h"
#include "sound.h"
#include "dialog.h"
#include "dialog_box.h"
#include "font.h"
#include "text.h"
#include "items.h"

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
    PlayJingle(0x1a);
    SetTextMacro1String(GetDialogText(GetRewardNameTextId(pRecord->bRewardId)));
    SetTextMacro3String(GetDialogText(GetRewardNameTextId(pRecord->bRewardId)));
    if (pRecord->bRewardId <= 0x4e)
        ShowDialogBlock(0x28d);
    else
        ShowDialogBlock(0x295);
    g_DialogState.bArg1C = pRecord->bDialogArg1C;
    g_DialogState.bArg1D = pRecord->bDialogArg1D;
}
