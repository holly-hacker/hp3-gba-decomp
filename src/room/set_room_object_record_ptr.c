#include "types.h"
#include "graphics/object.h"
#include "overworld/room_blob.h"

// Points the room object table's record at tile (col, row) to `obj`, marking the object as bound
// to that record. Passing a null `obj` clears the record.
void SetRoomObjectRecordPtr_candidate(Object *obj, u8 col, u8 row)
{
    RoomBlobTable *pColumn;
    Object **ppRecord;

    pColumn = (RoomBlobTable *)((u8 *)g_pRoomObjectTable + g_pRoomObjectTable->awOffsets[col]);
    ppRecord = (Object **)((u8 *)pColumn + pColumn->awOffsets[row]);
    *ppRecord = obj;
    if (obj != 0)
        obj->dwFlags |= ObjectFlagRoomRecordBound;
}
