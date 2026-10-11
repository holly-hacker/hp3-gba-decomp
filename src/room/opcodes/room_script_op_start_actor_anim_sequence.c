#include "types.h"
#include "actor.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct StartActorAnimSequenceRecord {
    u32 dwOpcode;
    u8 bX;
    u8 bY;
    u8 bScriptDataLow;
    u8 bScriptDataHigh;
    u8 bArg64;
    u8 bArg65;
    u8 bActionSelector;
    u8 bScriptPc;
    u8 bArg6A;
    u8 bArg6B;
} StartActorAnimSequenceRecord;

void RoomScriptOpStartActorAnimSequence(StartActorAnimSequenceRecord *pRecord)
{
    Actor *pActor;
    u8 actionState = 0;
    u8 *pScriptData;
    u8 scriptDataLow;
    u8 scriptDataHigh;

    if (g_dwPendingCameraFocusFlag != 0)
        RestorePendingCameraFocus_candidate(g_pPendingCameraFocus_candidate);
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;

    pActor = GetRoomActorField_candidate(pRecord->bX, pRecord->bY);
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
    scriptDataLow = pRecord->bScriptDataLow;
    pScriptData = (u8 *)&pActor->modeState.actor.wStagedDamage;
    *pScriptData = scriptDataLow;
    scriptDataHigh = pRecord->bScriptDataHigh;
    ++pScriptData;
    *pScriptData = scriptDataHigh;
    pActor->modeState.actor.bRoomScriptArg64_candidate = pRecord->bArg64;
    pActor->modeState.actor.bFollowResumeDistance = pRecord->bArg65;
    pActor->scriptState.wScriptPc = pRecord->bScriptPc;
    pActor->modeState.actor.bRoomScriptArg6A_candidate = pRecord->bArg6A;
    pActor->modeState.actor.bRoomScriptArg6B_candidate = pRecord->bArg6B;
    SetActorActionSubState(pActor, 0);
    pActor->dwFlags |= ActorFlagHasTickLogic;
}
