#include "types.h"
#include "game_modes.h"
#include "room_script.h"

void RoomScriptOpShowLoadingScreenTransition(RoomScriptRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    g_dwGameModeFlags |= 1;
    PushGameMode_3(LoadingScreen, pRecord->operand.ab[0], pRecord->operand.ab[1], pRecord->operand.ab[2]);
}
