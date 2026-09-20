#include "types.h"
#include "overworld.h"
#include "room_script.h"

void RoomScriptOpClearAllQueuedMoves(RoomScriptRecord *pRecord)
{
    u8 i;

    for (i = 0; i < g_OverworldControlState.bSlotCount; i++)
        g_aCameraEffects_candidate[i].bState = 0;
}
