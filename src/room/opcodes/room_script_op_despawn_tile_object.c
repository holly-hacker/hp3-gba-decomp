#include "types.h"
#include "overworld/room_script.h"

typedef struct DespawnTileObjectRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} DespawnTileObjectRecord;

void RoomScriptOpDespawnTileObject(DespawnTileObjectRecord *pRecord)
{
    Actor *pObject = GetRoomObjectField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pObject != NULL)
    {
        if (pObject->pLinkedActor_candidate != NULL)
            pObject->pLinkedActor_candidate->dwFlags |= 0x82;
        pObject->dwFlags |= 0x82;
    }
}
