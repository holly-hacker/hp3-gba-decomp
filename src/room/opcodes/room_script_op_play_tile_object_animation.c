#include "types.h"
#include "room_script.h"

void RoomScriptOpPlayTileObjectAnimation(RoomScriptRecord *pRecord)
{
    Object *pObject;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);
    if (g_dwRoomScriptRunState == 2)
        pObject->dwFlags |= ObjectFlagRoomScriptYield;
    SetObjectAnimData_candidate(pObject, pRecord->operand.aw[1]);
    pObject->dwFlags |= ObjectFlagHasAnimation;
}
