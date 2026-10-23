#include "types.h"
#include "actor.h"
#include "area.h"
#include "commands.h"
#include "move.h"

typedef struct StartActorAnimSequenceRecord {
    u32 dwOpcode;
    u8 bX;
    u8 bY;
    u8 bFinishRespawnRow;
    u8 bFinishChainRow;
    u8 bRoute;
    u8 bWaypoint;
    u8 bActionSelector;
    u8 bWaitTicks;
    u8 bNoPlatePress;
    u8 bUnused6B;
} StartActorAnimSequenceRecord;

void RoomScriptOpStartActorAnimSequence(StartActorAnimSequenceRecord *pRecord)
{
    Actor *pActor;
    u8 actionState = 0;
    u8 *pFinish;
    u8 finishRespawnRow;
    u8 finishChainRow;

    if (g_dwFieldSpellActive != 0)
        EndFieldSpellEffect(g_pFieldSpellEffectActor);
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;

    pActor = GetRoomActorPtr(pRecord->bX, pRecord->bY);
    if (g_dwRoomScriptRunState == 2)
        pActor->dwFlags |= ActorFlagRoomScriptYield;

    switch (pRecord->bActionSelector)
    {
    case 0:
        actionState = 7;
        break;
    case 1:
        actionState = 8;
        break;
    case 2:
        actionState = 9;
        break;
    case 3:
        actionState = 10;
        break;
    case 4:
        actionState = 11;
        break;
    case 5:
        actionState = 12;
        break;
    case 6:
        actionState = 13;
        pActor->dwFlags &= ~ActorFlagHasAnimation;
        break;
    }

    SetActorActionState(pActor, actionState);
    finishRespawnRow = pRecord->bFinishRespawnRow;
    pFinish = (u8 *)&pActor->modeState.route.finish;
    *pFinish = finishRespawnRow;
    finishChainRow = pRecord->bFinishChainRow;
    ++pFinish;
    *pFinish = finishChainRow;
    pActor->modeState.route.bRoute = pRecord->bRoute;
    pActor->modeState.route.bWaypoint = pRecord->bWaypoint;
    pActor->scriptState.wScriptPc = pRecord->bWaitTicks;
    pActor->modeState.actor.bNoPlatePress = pRecord->bNoPlatePress;
    pActor->modeState.route.bUnused6B = pRecord->bUnused6B;
    SetActorActionSubState(pActor, 0);
    pActor->dwFlags |= ActorFlagHasTickLogic;
}
