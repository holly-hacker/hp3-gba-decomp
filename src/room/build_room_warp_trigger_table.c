#include "types.h"
#include "overworld/room_blob.h"

// Builds g_pRoomWarpTriggerTable at pOut; returns its end.
u8 *BuildRoomWarpTriggerTable_candidate(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut)
{
    const RoomBlobTable *pDefaultTable;
    const RoomBlobTable *pVariantTable;
    u8 defaultCount;
    u8 i;
    u16 offset;

    pDefaultTable = NULL;
    defaultCount = 0;
    if (g_wRoomResourceFlags_candidate & 1)
    {
        pDefaultTable = (const RoomBlobTable *)((const u8 *)pDefault + pDefault->wWarpTableOffset);
        defaultCount = pDefaultTable->wCount;
    }
    pVariantTable = (const RoomBlobTable *)((const u8 *)pVariant + pVariant->wWarpTableOffset);
    defaultCount += pVariantTable->wCount;
    g_pRoomWarpTriggerTable->wCount = defaultCount;
    pOut += sub_08005EC8(defaultCount + 1);

    if (g_wRoomResourceFlags_candidate & 1)
    {
        for (i = 0; i < pDefaultTable->wCount; i++)
        {
            offset = pOut - (u8 *)g_pRoomWarpTriggerTable;
            g_pRoomWarpTriggerTable->awOffsets[i] = offset;
            pOut = sub_08005E40(pDefaultTable, pOut, i);
        }
        defaultCount = pDefaultTable->wCount;
    }
    else
        defaultCount = 0;

    for (i = 0; i < pVariantTable->wCount; i++)
    {
        offset = pOut - (u8 *)g_pRoomWarpTriggerTable;
        g_pRoomWarpTriggerTable->awOffsets[i + defaultCount] = offset;
        pOut = sub_08005E40(pVariantTable, pOut, i);
    }
    return pOut;
}
