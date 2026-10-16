#include "types.h"
#include "area.h"
#include "overworld/room_script.h"

typedef struct DelayedRespawnRowAndRunChainFramesRecord {
    u32 dwOpcode;
    u16 wDelay;  // frames; 0 runs the chain immediately
    u8 bRespawnRow;
    u8 bChainRow;
} DelayedRespawnRowAndRunChainFramesRecord;

void RoomScriptOpDelayedRespawnRowAndRunChainFrames(DelayedRespawnRowAndRunChainFramesRecord *pRecord)
{
    RoomScriptRecord *pNextRecord = g_pRoomScriptNextRecord;
    Actor *pTimer;

    if (pRecord->wDelay == 0)
    {
        RespawnGroupAndRunChain(pRecord->bRespawnRow, pRecord->bChainRow);
    }
    else
    {
        if (g_dwRoomScriptRunState == 1 && pNextRecord->dwOpcode != 0)
            g_dwRoomScriptRunState = 2;
        pTimer = SpawnScriptEffectActor(1);
        pTimer->dwStateTimer = pRecord->wDelay;
        pTimer->modeState.actor.bDelayedRespawnRow = pRecord->bRespawnRow;
        pTimer->modeState.actor.bDelayedChainRow = pRecord->bChainRow;
    }
}
