#include "types.h"
#include "room_script.h"

void RoomScriptOpSetTileObjectAndLinkedVisible(RoomScriptRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->operand.ab[0], pRecord->operand.ab[1]);

    if (pRecord->operand.ab[2] != 0)
    {
        pObject->dwFlags |= ObjectFlagVisible;
        if (pObject->pLinkedObject_candidate != NULL)
            pObject->pLinkedObject_candidate->dwFlags |= ObjectFlagVisible;
    }
    else
    {
        pObject->dwFlags &= ~ObjectFlagVisible;
        if (pObject->pLinkedObject_candidate != NULL)
            pObject->pLinkedObject_candidate->dwFlags &= ~ObjectFlagVisible;
    }
}
