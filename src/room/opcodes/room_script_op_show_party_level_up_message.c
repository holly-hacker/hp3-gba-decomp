#include "types.h"
#include "menu/dialog.h"
#include "overworld/room_script.h"

typedef struct ShowPartyLevelUpMessageRecord {
    u32 dwOpcode;
    u8 bLevelCount;
    u8 bDialogArg1C;
    u8 bDialogArg1D;
} ShowPartyLevelUpMessageRecord;

void RoomScriptOpShowPartyLevelUpMessage(ShowPartyLevelUpMessageRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    SetTextMacro1Number(pRecord->bLevelCount);
    SetTextMacro3Number(pRecord->bLevelCount);
    ShowRoomDialogBox_candidate(0x293);
    g_DialogState_candidate.bArg1C = pRecord->bDialogArg1C;
    g_DialogState_candidate.bArg1D = pRecord->bDialogArg1D;
}
