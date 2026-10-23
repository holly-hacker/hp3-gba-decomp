#include "types.h"
#include "modes.h"
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

    for (i = 0; i < ARRAY_COUNT(g_abRoomEntryIds); i++)
        g_abRoomEntryIds[i] = pRecord->bExitParam;
    if (g_dwGameModeFlags & GameModeFlagOverlayMode)
        g_dwGameModeFlags &= ~GameModeFlagOverlayMode;
}
