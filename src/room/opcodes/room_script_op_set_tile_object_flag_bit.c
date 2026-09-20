#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectFlagBit(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    pObject->dwFlags |= 1 << pRecord->operand.ab[2];
}
