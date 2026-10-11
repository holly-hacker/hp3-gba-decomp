#include "types.h"
#include "actor.h"
#include "overworld/room.h"
#include "overworld/room_script.h"

typedef struct StartTileObjectScriptRecord {
    u32 dwOpcode;
    u16 wScriptPc;
    u16 wScriptData;
    u8 bX;
    u8 bY;
    u8 bArg65;
    u8 bArg66;
    u8 bArg64;
} StartTileObjectScriptRecord;

void RoomScriptOpStartTileObjectScript(StartTileObjectScriptRecord *pRecord)
{
    Actor *pObject;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;

    pObject = GetRoomObjectField_candidate(pRecord->bX, pRecord->bY);
    if (pObject == NULL)
        return;

    if (g_dwPendingCameraFocusFlag != 0)
        RestorePendingCameraFocus_candidate(g_pPendingCameraFocus_candidate);
    if (g_dwRoomScriptRunState == 2)
        pObject->dwFlags |= ActorFlagRoomScriptYield;

    pObject->scriptState.wScriptPc = pRecord->wScriptPc;
    pObject->modeState.actor.wStagedDamage = pRecord->wScriptData;
    pObject->modeState.actor.bFollowResumeDistance = pRecord->bArg65;
    pObject->modeState.actor.bRoomScriptArg66_candidate = pRecord->bArg66;
    SetActorActionState(pObject, 15);

    if (pObject->dwFlags & ActorFlagFourWayDirections_candidate)
        pObject->modeState.actor.bRoomScriptArg64_candidate = pRecord->bArg64 >> 1;
    else
        pObject->modeState.actor.bRoomScriptArg64_candidate = pRecord->bArg64;

    SetActorFlags(pObject, ActorFlagHasTickLogic);
    SetActorActionSubState(pObject, 0);
}
