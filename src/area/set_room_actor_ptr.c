#include "types.h"
#include "actor.h"
#include "area.h"
#include "overworld/room_blob.h"

// Points the room actor table's record at tile (col, row) to `actor`, marking the actor as bound
// to that record. Passing a null `actor` clears the record.
void SetRoomActorPtr(Actor *actor, u8 col, u8 row)
{
    RoomBlobTable *pColumn;
    Actor **ppRecord;

    pColumn = (RoomBlobTable *)((u8 *)g_pRoomActorTable + g_pRoomActorTable->awOffsets[col]);
    ppRecord = (Actor **)((u8 *)pColumn + pColumn->awOffsets[row]);
    *ppRecord = actor;
    if (actor != 0)
        actor->dwFlags |= ActorFlagRoomRecordBound;
}
