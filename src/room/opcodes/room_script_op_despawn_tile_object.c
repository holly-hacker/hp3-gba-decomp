#include "types.h"
#include "room_script.h"

void RoomScriptOpDespawnTileObject(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    if (pObject != NULL)
    {
        if (pObject->pLinkedObject_candidate != NULL)
            pObject->pLinkedObject_candidate->dwFlags |= 0x82;
        pObject->dwFlags |= 0x82;
    }
}
