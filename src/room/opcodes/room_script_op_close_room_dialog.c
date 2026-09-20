#include "types.h"
#include "game_modes.h"
#include "room_script.h"

void RoomScriptOpCloseRoomDialog(RoomScriptRecord *pRecord)
{
    u8 i;

    for (i = 0; i < 2; i++)
        g_abRoomScriptExitParams_candidate[i] = pRecord->operand.ab[1];
    if (g_dwGameModeFlags & 1)
        g_dwGameModeFlags &= ~1;
}
