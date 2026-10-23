#include "types.h"
#include "commands.h"
#include "modes.h"
#include "hero.h"
#include "main.h"
#include "map.h"

typedef struct ReturnToOverworldRecord {
    u32 dwOpcode;
    u8 bExitId;
    u8 bExitParam;
} ReturnToOverworldRecord;

void RoomScriptOpReturnToOverworld(ReturnToOverworldRecord *pRecord)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(g_abRoomEntryIds); i++)
        g_abRoomEntryIds[i] = pRecord->bExitParam;
    PushGameMode_2(Overworld, OverworldEntryEnterRoom, pRecord->bExitId);
    g_dwGameModeFlags |= GameModeFlagModeChangeRequested;
}
