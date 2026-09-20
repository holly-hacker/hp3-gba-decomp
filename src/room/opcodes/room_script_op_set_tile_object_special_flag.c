#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectSpecialFlag(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    if (pRecord->operand.ab[2] != 0)
        pObject->bFlags_0x94_candidate |= 4;
}
