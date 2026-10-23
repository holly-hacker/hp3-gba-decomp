#include "types.h"
#include "area.h"
#include "overworld/room_blob.h"

// Builds g_pRoomRouteTable at pOut; returns its end.
u8 *BuildRoomRouteTable(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut)
{
    const RoomBlobTable *pDefaultTable;
    const RoomBlobTable *pVariantTable;
    u8 defaultCount;
    u8 i;
    u16 offset;

    pDefaultTable = NULL;
    defaultCount = 0;
    if (g_wRoomVariantFlags & 1)
    {
        pDefaultTable = (const RoomBlobTable *)((const u8 *)pDefault + pDefault->wRouteTableOffset);
        defaultCount = pDefaultTable->wCount;
    }
    pVariantTable = (const RoomBlobTable *)((const u8 *)pVariant + pVariant->wRouteTableOffset);
    defaultCount += pVariantTable->wCount;
    g_pRoomRouteTable->wCount = defaultCount;
    pOut += GetRoomOffsetTableSize(defaultCount + 1);

    if (g_wRoomVariantFlags & 1)
    {
        for (i = 0; i < pDefaultTable->wCount; i++)
        {
            offset = pOut - (u8 *)g_pRoomRouteTable;
            g_pRoomRouteTable->awOffsets[i] = offset;
            pOut = CopyRoomRouteWaypoints(pDefaultTable, pOut, i);
        }
        defaultCount = pDefaultTable->wCount;
    }
    else
        defaultCount = 0;

    for (i = 0; i < pVariantTable->wCount; i++)
    {
        offset = pOut - (u8 *)g_pRoomRouteTable;
        g_pRoomRouteTable->awOffsets[i + defaultCount] = offset;
        pOut = CopyRoomRouteWaypoints(pVariantTable, pOut, i);
    }
    return pOut;
}
