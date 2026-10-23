#include "types.h"
#include "area.h"

// Constructs the actor of record (col, row), binds it to the record and returns it.
Actor *SpawnRoomGroupMember(u8 col, u8 row)
{
    RoomBlobTable *pGroup;
    RoomActorRecord *pRecord;
    u32 type;

    pGroup = (RoomBlobTable *)((u8 *)g_pRoomActorTable + g_pRoomActorTable->awOffsets[col]);
    pRecord = (RoomActorRecord *)((u8 *)pGroup + pGroup->awOffsets[row]);
    type = pRecord->wActorType;
    pRecord->pActor = g_apRoomActorConstructors[type](col, row);
    pRecord->pActor->bRoomRecordCol = col;
    pRecord->pActor->bRoomRecordRow = row;
    pRecord->pActor->dwFlags |= ActorFlagRoomRecordBound;
    return pRecord->pActor;
}
