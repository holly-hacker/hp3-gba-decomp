#include "types.h"
#include "game_modes.h"
#include "room_script.h"

void RoomScriptOpReturnToOverworld(RoomScriptRecord *pRecord)
{
    u8 i;

    for (i = 0; i < 2; i++)
        g_abRoomScriptExitParams_candidate[i] = pRecord->operand.ab[1];
    PushGameMode_2(Overworld, 0, pRecord->operand.ab[0]);
    g_dwGameModeFlags |= 0x80000000;
}
