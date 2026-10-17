#include "types.h"
#include "commands.h"
#include "hero.h"
#include "main.h"

typedef struct CloseRoomDialogRecord {
    u32 dwOpcode;
    u8 pad_04[1];
    u8 bExitParam;
} CloseRoomDialogRecord;

void RoomScriptOpCloseRoomDialog(CloseRoomDialogRecord *pRecord)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(g_abRoomScriptExitParams_candidate); i++)
        g_abRoomScriptExitParams_candidate[i] = pRecord->bExitParam;
    if (g_dwGameModeFlags & 1)
        g_dwGameModeFlags &= ~1;
}
