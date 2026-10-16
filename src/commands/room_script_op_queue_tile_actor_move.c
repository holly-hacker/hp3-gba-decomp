#include "types.h"
#include "area.h"
#include "commands.h"
#include "math.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"

typedef struct QueueTileActorMoveRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bRespawnRow;
    u8 bChainRow;
    s16 nSpeed;
    u16 wDelayFrames;
} QueueTileActorMoveRecord;

void RoomScriptOpQueueTileActorMove(QueueTileActorMoveRecord *pRecord)
{
    Actor *pControlled = g_OverworldControlState.aSlots[g_OverworldControlState.bSlotIndex].pActor;
    Actor *pTarget;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    pTarget = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);
    if (g_dwRoomScriptRunState == 2)
        g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].dwResumeScript = 1;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].nStep = SignMagnitude8_8ToFixed(pRecord->nSpeed);
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].wCounter = pRecord->wDelayFrames;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].pTarget = pTarget;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bRespawnRow = pRecord->bRespawnRow;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bChainRow = pRecord->bChainRow;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bState = 1;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bSavedActionSubState = pControlled->bActionSubState;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].savedVel = pControlled->vel;
    g_aCameraEffects_candidate[g_OverworldControlState.bSlotIndex].bChainRan = 0;
    pControlled->vel.x = 0;
    pControlled->vel.y = 0;
}
