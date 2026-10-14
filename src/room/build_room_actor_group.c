#include "types.h"
#include "overworld/room_blob.h"

// Builds one column of the room actor table at pOut; returns its end.
u8 *BuildRoomActorGroup(const RoomBlobTable *pTable, u8 *pOut, u8 index)
{
    const RoomBlobColumn *pColumn;
    RoomBlobTable *pOutColumn;
    const u8 *pSrc;
    u8 count;
    u8 i;
    u16 step;

    step = pTable->awOffsets[index];
    pSrc = (const u8 *)pTable + step;
    pColumn = (const RoomBlobColumn *)pSrc;
    pOutColumn = (RoomBlobTable *)pOut;
    count = pColumn->bCount;
    pOutColumn->wCount = count;

    // Row sizes follow the count, then the records start on a 4-byte boundary.
    step = AlignRoomSizeTo4(count + 2);
    pSrc += step;
    step = GetRoomOffsetTableSize(count + 1);

    for (i = 0; i < count; i++)
    {
        pOut += step;
        pOutColumn->awOffsets[i] = pOut - (u8 *)pOutColumn;
        step = pColumn->abRowSizes[i];
        CopyRoomActorStaticBytes(pSrc, pOut, step);
        pSrc += step;
        step += 8;
    }
    pOut += step;
    return pOut;
}
