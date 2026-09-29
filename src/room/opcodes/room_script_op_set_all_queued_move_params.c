#include "types.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

typedef struct SetAllQueuedMoveParamsRecord {
    u32 dwOpcode;
    u16 wDuration;
    s16 nAmplitude;
    u8 bRespawnRow;
    u8 bChainRow;
} SetAllQueuedMoveParamsRecord;

void RoomScriptOpSetAllQueuedMoveParams(SetAllQueuedMoveParamsRecord *pRecord)
{
    u8 i;

    for (i = 0; i < g_OverworldControlState.bSlotCount; i++)
    {
        g_aCameraEffects_candidate[i].nStep = pRecord->nAmplitude * 65536;
        g_aCameraEffects_candidate[i].dwFramesLeft = pRecord->wDuration * 30;
        g_aCameraEffects_candidate[i].bState = 3;
        g_aCameraEffects_candidate[i].wCounter = 0;
        g_aCameraEffects_candidate[i].bRespawnRow = pRecord->bRespawnRow;
        g_aCameraEffects_candidate[i].bChainRow = pRecord->bChainRow;
        if (g_aCameraEffects_candidate[i].dwFramesLeft == 0)
            g_aCameraEffects_candidate[i].dwRunForever = 1;
        else
            g_aCameraEffects_candidate[i].dwRunForever = 0;
    }
}
