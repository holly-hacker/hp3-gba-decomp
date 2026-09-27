#include "types.h"
#include "game_modes.h"
#include "room_script.h"

typedef struct CloseRoomDialogRecord {
    u32 dwOpcode;
    u8 pad_04[1];
    u8 bExitParam;
} CloseRoomDialogRecord;

void RoomScriptOpCloseRoomDialog(CloseRoomDialogRecord *pRecord)
{
    u8 i;

    for (i = 0; i < 2; i++)
        g_abRoomScriptExitParams_candidate[i] = pRecord->bExitParam;
    if (g_dwGameModeFlags & 1)
        g_dwGameModeFlags &= ~1;
}
