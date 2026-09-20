#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectFacingAndScriptPage(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    SetObjectActionState(pObject, 0x1b);
    SetObjectActionSubState(pObject, 0);
    if (pObject->dwFlags & 0x100000)
        pObject->bFacing = pRecord->operand.ab[2] >> 1;
    else
        pObject->bFacing = pRecord->operand.ab[2];
    pObject->bScriptPageHigh_candidate = pRecord->operand.ab[3];
}
