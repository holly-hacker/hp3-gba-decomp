#include "types.h"
#include "overworld/room_script.h"

typedef struct SetTileObjectAndLinkedVisibleRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u8 bVisible;
} SetTileObjectAndLinkedVisibleRecord;

void RoomScriptOpSetTileObjectAndLinkedVisible(SetTileObjectAndLinkedVisibleRecord *pRecord)
{
    Object *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pRecord->bVisible != 0)
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
