#include "types.h"
#include "audio.h"
#include "dialog.h"
#include "room_script.h"

typedef struct ShowRoomDialogRecord {
    u32 dwOpcode;
    u16 wBlockId;
    u8 bDialogArg1C;
    u8 bDialogArg1D;
} ShowRoomDialogRecord;

void RoomScriptOpShowRoomDialog(ShowRoomDialogRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;

    if (pRecord->wBlockId == 0x270)
        PlaySoundById(0x24);
    else
        PlaySoundById(5);

    ShowRoomDialogBox_candidate(pRecord->wBlockId);
    g_DialogState_candidate.bArg1C = pRecord->bDialogArg1C;
    g_DialogState_candidate.bArg1D = pRecord->bDialogArg1D;
}
