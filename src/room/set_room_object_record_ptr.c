#include "types.h"
#include "actor.h"
#include "overworld/room_blob.h"

// Points the room object table's record at tile (col, row) to `obj`, marking the object as bound
// to that record. Passing a null `obj` clears the record.
void SetRoomObjectRecordPtr_candidate(Actor *obj, u8 col, u8 row)
{
    RoomBlobTable *pColumn;
    Actor **ppRecord;

    pColumn = (RoomBlobTable *)((u8 *)g_pRoomObjectTable + g_pRoomObjectTable->awOffsets[col]);
    ppRecord = (Actor **)((u8 *)pColumn + pColumn->awOffsets[row]);
    *ppRecord = obj;
    if (obj != 0)
        obj->dwFlags |= ActorFlagRoomRecordBound;
}
