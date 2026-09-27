#include "types.h"
#include "room_script.h"

void RoomScriptOp2(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    if (pObject->wObjectType == RoomObjectType_Player)
        pObject->dwUnk_0x28 = pRecord->operand.asw[1] * 5 << 14;
    else
        pObject->dwUnk_0x28 = pRecord->operand.asw[1] << 16;
    pObject->bActionFlags |= 8;
}
