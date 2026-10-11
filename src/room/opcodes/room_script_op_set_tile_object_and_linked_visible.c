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
    Actor *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pRecord->bVisible != 0)
    {
        pObject->dwFlags |= ActorFlagVisible;
        if (pObject->pLinkedActor_candidate != NULL)
            pObject->pLinkedActor_candidate->dwFlags |= ActorFlagVisible;
    }
    else
    {
        pObject->dwFlags &= ~ActorFlagVisible;
        if (pObject->pLinkedActor_candidate != NULL)
            pObject->pLinkedActor_candidate->dwFlags &= ~ActorFlagVisible;
    }
}
