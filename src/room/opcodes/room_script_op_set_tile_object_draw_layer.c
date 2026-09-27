#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectDrawLayer(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    if (pObject != NULL)
        pObject->oam.priority = pRecord->operand.ab[2];
}
