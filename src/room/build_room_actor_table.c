#include "types.h"
#include "overworld/room_blob.h"

// Builds g_pRoomActorTable at pOut; returns its end.
u8 *BuildRoomActorTable(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut)
{
    const RoomBlobTable *pTable;
    u8 count;
    u8 i;
    u16 offset;

    g_wRoomResourceFlags_candidate = pVariant->wFlags;
    pTable = &pVariant->actorTable;
    pVariant = (const RoomBlobSubBlock *)pTable;
    count = pTable->wCount;

    if (g_wRoomResourceFlags_candidate & 1)
        g_pRoomActorTable->wCount = count + 1;
    else
        g_pRoomActorTable->wCount = count;

    offset = GetRoomOffsetTableSize(g_pRoomActorTable->wCount + 1);
    pOut += offset;

    if (g_wRoomResourceFlags_candidate & 1)
    {
        g_pRoomActorTable->awOffsets[0] = offset;
        pTable = &pDefault->actorTable;
        pOut = BuildRoomActorGroup(pTable, pOut, 0);
    }

    pTable = (const RoomBlobTable *)pVariant;
    for (i = 0; i < count; i++)
    {
        offset = pOut - (u8 *)g_pRoomActorTable;
        if (g_wRoomResourceFlags_candidate & 1)
            g_pRoomActorTable->awOffsets[i + 1] = offset;
        else
            g_pRoomActorTable->awOffsets[i] = offset;
        pOut = BuildRoomActorGroup(pTable, pOut, i);
    }
    return pOut;
}
