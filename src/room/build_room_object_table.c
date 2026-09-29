#include "types.h"
#include "overworld/room_blob.h"

// Builds g_pRoomObjectTable at pOut; returns its end.
u8 *BuildRoomObjectTable_candidate(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut)
{
    const RoomBlobTable *pTable;
    u8 count;
    u8 i;
    u16 offset;

    g_wRoomResourceFlags_candidate = pVariant->wFlags;
    pTable = &pVariant->objectTable;
    pVariant = (const RoomBlobSubBlock *)pTable;
    count = pTable->wCount;

    if (g_wRoomResourceFlags_candidate & 1)
        g_pRoomObjectTable->wCount = count + 1;
    else
        g_pRoomObjectTable->wCount = count;

    offset = sub_08005EC8(g_pRoomObjectTable->wCount + 1);
    pOut += offset;

    if (g_wRoomResourceFlags_candidate & 1)
    {
        g_pRoomObjectTable->awOffsets[0] = offset;
        pTable = &pDefault->objectTable;
        pOut = BuildRoomObjectColumn_candidate(pTable, pOut, 0);
    }

    pTable = (const RoomBlobTable *)pVariant;
    for (i = 0; i < count; i++)
    {
        offset = pOut - (u8 *)g_pRoomObjectTable;
        if (g_wRoomResourceFlags_candidate & 1)
            g_pRoomObjectTable->awOffsets[i + 1] = offset;
        else
            g_pRoomObjectTable->awOffsets[i] = offset;
        pOut = BuildRoomObjectColumn_candidate(pTable, pOut, i);
    }
    return pOut;
}
