#include "types.h"
#include "overworld/room_script.h"

typedef struct DespawnTileActorRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
} DespawnTileActorRecord;

void RoomScriptOpDespawnTileActor(DespawnTileActorRecord *pRecord)
{
    Actor *pActor = GetRoomActorField_candidate(pRecord->bTileX, pRecord->bTileY);

    if (pActor != NULL)
    {
        if (pActor->pLinkedActor_candidate != NULL)
            pActor->pLinkedActor_candidate->dwFlags |= 0x82;
        pActor->dwFlags |= 0x82;
    }
}
