#include "types.h"
#include "overworld/room_script.h"

typedef struct DelayedRespawnRowAndRunChainRecord {
    u32 dwOpcode;
    u16 wDelay;  // units of 30 frames; 0 runs the chain immediately
    u8 bRespawnRow;
    u8 bChainRow;
} DelayedRespawnRowAndRunChainRecord;

void RoomScriptOpDelayedRespawnRowAndRunChain(DelayedRespawnRowAndRunChainRecord *pRecord)
{
    RoomScriptRecord *pNextRecord = g_pRoomScriptNextRecord;
    Object *pTimer;

    if (pRecord->wDelay == 0)
    {
        RespawnRowAndRunChain_candidate(pRecord->bRespawnRow, pRecord->bChainRow);
    }
    else
    {
        if (g_dwRoomScriptRunState == 1 && pNextRecord->dwOpcode != 0)
            g_dwRoomScriptRunState = 2;
        pTimer = SpawnScriptEffectObject(1);
        pTimer->dwStateTimer = pRecord->wDelay * 30;
        pTimer->bDelayedRespawnRow = pRecord->bRespawnRow;
        pTimer->bDelayedChainRow = pRecord->bChainRow;
    }
}
