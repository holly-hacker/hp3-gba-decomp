#include "types.h"
#include "object.h"
#include "room.h"
#include "room_script.h"

typedef struct StartObjectAnimSequenceRecord {
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
} StartObjectAnimSequenceRecord;

void RoomScriptOpStartObjectAnimSequence(StartObjectAnimSequenceRecord *pRecord)
{
    Object *pObject;
    u8 actionState = 0;
    u8 *pScriptData;
    u8 scriptDataLow;
    u8 scriptDataHigh;

    if (g_dwPendingCameraFocusFlag != 0)
        RestorePendingCameraFocus_candidate(g_pPendingCameraFocus_candidate);
    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;

    pObject = GetRoomObjectField_candidate(pRecord->bX, pRecord->bY);
    if (g_dwRoomScriptRunState == 2)
        pObject->dwFlags |= ObjectFlagRoomScriptYield;

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
        pObject->dwFlags &= ~ObjectFlagHasAnimation;
        break;
    }

    SetObjectActionState(pObject, actionState);
    scriptDataLow = pRecord->bScriptDataLow;
    pScriptData = (u8 *)&pObject->wStagedDamage;
    *pScriptData = scriptDataLow;
    scriptDataHigh = pRecord->bScriptDataHigh;
    ++pScriptData;
    *pScriptData = scriptDataHigh;
    pObject->bRoomScriptArg64_candidate = pRecord->bArg64;
    pObject->bFollowResumeDistance = pRecord->bArg65;
    pObject->scriptState.wScriptPc = pRecord->bScriptPc;
    pObject->bRoomScriptArg6A_candidate = pRecord->bArg6A;
    pObject->bRoomScriptArg6B_candidate = pRecord->bArg6B;
    SetObjectActionSubState(pObject, 0);
    pObject->dwFlags |= ObjectFlagHasTickLogic;
}
