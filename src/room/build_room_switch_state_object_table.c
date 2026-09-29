#include "types.h"
#include "overworld/room_blob.h"

// Builds g_pRoomSwitchStateObjectTable at pOut; returns its end.
u8 *BuildRoomSwitchStateObjectTable_candidate(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut)
{
    const RoomBlobTable *pChains;
    u16 offset;
    u8 count;
    u8 i;

    offset = pVariant->wSwitchTableOffset;
    pChains = (const RoomBlobTable *)((const u8 *)pVariant + offset);
    count = pChains->wCount;

    if (g_wRoomResourceFlags_candidate & 1)
        g_pRoomSwitchStateObjectTable->wHeader = count + 1;
    else
        g_pRoomSwitchStateObjectTable->wHeader = count;

    offset = sub_08005EC8(g_pRoomSwitchStateObjectTable->wHeader + 1);
    pOut += offset;

    if (g_wRoomResourceFlags_candidate & 1)
    {
        g_pRoomSwitchStateObjectTable->awChainOffsets[0] = offset;
        offset = pDefault->wSwitchTableOffset;
        pChains = (const RoomBlobTable *)((const u8 *)pDefault + offset);
        pOut = sub_08005E84(pChains, pOut, 0);
    }

    offset = pVariant->wSwitchTableOffset;
    pChains = (const RoomBlobTable *)((const u8 *)pVariant + offset);
    for (i = 0; i < count;)
    {
        offset = pOut - (u8 *)g_pRoomSwitchStateObjectTable;
        if (g_wRoomResourceFlags_candidate & 1)
            g_pRoomSwitchStateObjectTable->awChainOffsets[i + 1] = offset;
        else
            g_pRoomSwitchStateObjectTable->awChainOffsets[i] = offset;
        pOut = sub_08005E84(pChains, pOut, i);
        i++;
    }
    return pOut;
}
