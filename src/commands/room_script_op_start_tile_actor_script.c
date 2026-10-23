#include "types.h"
#include "actor.h"
#include "area.h"
#include "commands.h"
#include "move.h"

typedef struct StartTileActorScriptRecord {
    u32 dwOpcode;
    u16 wTargetX;
    u16 wTargetY;
    u8 bX;
    u8 bY;
    u8 bRespawnRow;
    u8 bChainRow;
    u8 bFacing;
} StartTileActorScriptRecord;

void RoomScriptOpStartTileActorScript(StartTileActorScriptRecord *pRecord)
{
    Actor *pActor;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;

    pActor = GetRoomActorPtr(pRecord->bX, pRecord->bY);
    if (pActor == NULL)
        return;

    if (g_dwFieldSpellActive != 0)
        EndFieldSpellEffect(g_pFieldSpellEffectActor);
    if (g_dwRoomScriptRunState == 2)
        pActor->dwFlags |= ActorFlagRoomScriptYield;

    pActor->scriptState.wScriptPc = pRecord->wTargetX;
    pActor->modeState.scriptWalk.wTargetY = pRecord->wTargetY;
    pActor->modeState.scriptWalk.args.bytes.bRespawnRow = pRecord->bRespawnRow;
    pActor->modeState.scriptWalk.args.bytes.bChainRow = pRecord->bChainRow;
    SetActorActionState(pActor, 15);

    if (pActor->dwFlags & ActorFlagFourWayDirections)
        pActor->modeState.scriptWalk.args.bytes.bFacing = pRecord->bFacing >> 1;
    else
        pActor->modeState.scriptWalk.args.bytes.bFacing = pRecord->bFacing;

    SetActorFlags(pActor, ActorFlagHasTickLogic);
    SetActorActionSubState(pActor, 0);
}
