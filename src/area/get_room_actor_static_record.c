#include "types.h"
#include "area.h"

// The static part of record (bColumn, bRow), starting with its actor type.
void *GetRoomActorStaticRecord(u8 bColumn, u8 bRow)
{
    RoomBlobTable *pGroup;
    RoomActorRecord *pRecord;

    pGroup = (RoomBlobTable *)((u8 *)g_pRoomActorTable + g_pRoomActorTable->awOffsets[bColumn]);
    pRecord = (RoomActorRecord *)((u8 *)pGroup + pGroup->awOffsets[bRow]);
    return &pRecord->wActorType;
}
