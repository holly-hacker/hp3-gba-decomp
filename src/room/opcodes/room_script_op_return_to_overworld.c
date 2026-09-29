#include "types.h"
#include "game/game_modes.h"
#include "overworld/room_script.h"

typedef struct ReturnToOverworldRecord {
    u32 dwOpcode;
    u8 bExitId;
    u8 bExitParam;
} ReturnToOverworldRecord;

void RoomScriptOpReturnToOverworld(ReturnToOverworldRecord *pRecord)
{
    u8 i;

    for (i = 0; i < 2; i++)
        g_abRoomScriptExitParams_candidate[i] = pRecord->bExitParam;
    PushGameMode_2(Overworld, 0, pRecord->bExitId);
    g_dwGameModeFlags |= 0x80000000;
}
