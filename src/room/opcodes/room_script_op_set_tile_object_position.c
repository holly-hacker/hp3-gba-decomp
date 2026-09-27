#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectPosition(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[4], pRecord->operand.ab[5]);

    pObject->nX = pRecord->operand.asw[0] << 16;
    pObject->nY = pRecord->operand.asw[1] << 16;
    pObject->bFacing = pRecord->operand.ab[6];
    pObject->bActionFlags |= 0x10;
}
