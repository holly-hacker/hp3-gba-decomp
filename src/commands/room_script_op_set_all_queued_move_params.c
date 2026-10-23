#include "types.h"
#include "commands.h"
#include "overworld/overworld.h"
#include "hero.h"

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
        g_aCameraEffects[i].nStep = pRecord->nAmplitude * 65536;
        g_aCameraEffects[i].dwFramesLeft = pRecord->wDuration * 30;
        g_aCameraEffects[i].bState = 3;
        g_aCameraEffects[i].wCounter = 0;
        g_aCameraEffects[i].bRespawnRow = pRecord->bRespawnRow;
        g_aCameraEffects[i].bChainRow = pRecord->bChainRow;
        if (g_aCameraEffects[i].dwFramesLeft == 0)
            g_aCameraEffects[i].dwRunForever = 1;
        else
            g_aCameraEffects[i].dwRunForever = 0;
    }
}
