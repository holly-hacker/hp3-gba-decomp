#include "types.h"
#include "room_script.h"

void RoomScriptOpDelayedRespawnRowAndRunChainFrames(RoomScriptRecord *pRecord)
{
    RoomScriptRecord *pNextRecord = g_pRoomScriptNextRecord;
    Object *pTimer;

    if (pRecord->operand.aw[0] == 0)
    {
        RespawnRowAndRunChain_candidate(pRecord->operand.ab[2], pRecord->operand.ab[3]);
    }
    else
    {
        if (g_dwRoomScriptRunState == 1 && pNextRecord->dwOpcode != 0)
            g_dwRoomScriptRunState = 2;
        pTimer = SpawnScriptEffectObject(1);
        pTimer->dwStateTimer = pRecord->operand.aw[0];
        pTimer->bDelayedRespawnRow = pRecord->operand.ab[2];
        pTimer->bDelayedChainRow = pRecord->operand.ab[3];
    }
}
