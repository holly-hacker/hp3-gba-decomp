#include "types.h"
#include "game/game_modes.h"
#include "overworld/room_script.h"

typedef struct ShowLoadingScreenTransitionRecord {
    u32 dwOpcode;
    u8 bModeArg1;
    u8 bModeArg2;
    u8 bModeArg3;
} ShowLoadingScreenTransitionRecord;

void RoomScriptOpShowLoadingScreenTransition(ShowLoadingScreenTransitionRecord *pRecord)
{
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    g_dwGameModeFlags |= 1;
    PushGameMode_3(LoadingScreen, pRecord->bModeArg1, pRecord->bModeArg2, pRecord->bModeArg3);
}
