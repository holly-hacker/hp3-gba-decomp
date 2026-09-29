#include "types.h"
#include "graphics/object.h"
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
    Object *pObject;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;

    pObject = GetRoomObjectField_candidate(pRecord->bX, pRecord->bY);
    if (pObject == NULL)
        return;

    if (g_dwPendingCameraFocusFlag != 0)
        RestorePendingCameraFocus_candidate(g_pPendingCameraFocus_candidate);
    if (g_dwRoomScriptRunState == 2)
        pObject->dwFlags |= ObjectFlagRoomScriptYield;

    pObject->scriptState.wScriptPc = pRecord->wScriptPc;
    pObject->wStagedDamage = pRecord->wScriptData;
    pObject->bFollowResumeDistance = pRecord->bArg65;
    pObject->bRoomScriptArg66_candidate = pRecord->bArg66;
    SetObjectActionState(pObject, 15);

    if (pObject->dwFlags & ObjectFlagFourWayDirections_candidate)
        pObject->bRoomScriptArg64_candidate = pRecord->bArg64 >> 1;
    else
        pObject->bRoomScriptArg64_candidate = pRecord->bArg64;

    SetObjectFlags(pObject, ObjectFlagHasTickLogic);
    SetObjectActionSubState(pObject, 0);
}
