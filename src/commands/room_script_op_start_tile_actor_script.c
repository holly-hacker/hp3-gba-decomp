#include "types.h"
#include "actor.h"
#include "area.h"
#include "commands.h"
#include "move.h"

typedef struct StartTileActorScriptRecord {
    u32 dwOpcode;
    u16 wScriptPc;
    u16 wScriptData;
    u8 bX;
    u8 bY;
    u8 bArg65;
    u8 bArg66;
    u8 bArg64;
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

    pActor->scriptState.wScriptPc = pRecord->wScriptPc;
    pActor->modeState.actor.wStagedDamage = pRecord->wScriptData;
    pActor->modeState.actor.bFollowResumeDistance = pRecord->bArg65;
    pActor->modeState.actor.bRoomScriptArg66_candidate = pRecord->bArg66;
    SetActorActionState(pActor, 15);

    if (pActor->dwFlags & ActorFlagFourWayDirections_candidate)
        pActor->modeState.actor.bRoomScriptArg64_candidate = pRecord->bArg64 >> 1;
    else
        pActor->modeState.actor.bRoomScriptArg64_candidate = pRecord->bArg64;

    SetActorFlags(pActor, ActorFlagHasTickLogic);
    SetActorActionSubState(pActor, 0);
}
