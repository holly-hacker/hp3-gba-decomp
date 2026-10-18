#include "types.h"
#include "area.h"

// Spawns every actor of group `row` whose record has no live actor.
void SpawnMissingRoomGroupActors(u8 row)
{
    RoomBlobTable *pGroup;
    RoomActorRecord *pRecord;
    u32 type;
    u8 count;
    u8 i;
    u16 offset;

    offset = g_pRoomActorTable->awOffsets[row];
    pGroup = (RoomBlobTable *)((u8 *)g_pRoomActorTable + offset);
    count = pGroup->wCount;
    for (i = 0; i < count; i++)
    {
        offset = pGroup->awOffsets[i];
        pRecord = (RoomActorRecord *)((u8 *)pGroup + offset);
        if (pRecord->pActor == NULL)
        {
            type = pRecord->wActorType;
            pRecord->pActor = g_apRoomActorConstructors[type](row, i);
            pRecord->pActor->bRoomTileCol_candidate = row;
            pRecord->pActor->bRoomTileRow_candidate = i;
            pRecord->pActor->dwFlags |= ActorFlagRoomRecordBound;
        }
    }
}
