#include "types.h"
#include "commands.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"
#include "hero.h"

void RoomScriptOpClearAllQueuedMoves(RoomScriptRecord *pRecord)
{
    u8 i;

    for (i = 0; i < g_OverworldControlState.bSlotCount; i++)
        g_aCameraEffects[i].bState = 0;
}
