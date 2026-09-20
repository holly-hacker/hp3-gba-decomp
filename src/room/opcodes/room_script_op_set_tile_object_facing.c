#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectFacing(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    SetObjectActionState(pObject, 3);
    if (pObject->dwFlags & 0x100000)
        pObject->bFacing = pRecord->operand.ab[2] >> 1;
    else
        pObject->bFacing = pRecord->operand.ab[2];
}
