#include "types.h"
#include "area.h"
#include "overworld/room_blob.h"

// Builds g_pRoomScriptChainTable at pOut; returns its end.
u8 *BuildRoomScriptChainTable(const RoomBlobSubBlock *pDefault, const RoomBlobSubBlock *pVariant, u8 *pOut)
{
    const RoomBlobTable *pChains;
    u16 offset;
    u8 count;
    u8 i;

    offset = pVariant->wSwitchTableOffset;
    pChains = (const RoomBlobTable *)((const u8 *)pVariant + offset);
    count = pChains->wCount;

    if (g_wRoomResourceFlags_candidate & 1)
        g_pRoomScriptChainTable->wHeader = count + 1;
    else
        g_pRoomScriptChainTable->wHeader = count;

    offset = GetRoomOffsetTableSize(g_pRoomScriptChainTable->wHeader + 1);
    pOut += offset;

    if (g_wRoomResourceFlags_candidate & 1)
    {
        g_pRoomScriptChainTable->awChainOffsets[0] = offset;
        offset = pDefault->wSwitchTableOffset;
        pChains = (const RoomBlobTable *)((const u8 *)pDefault + offset);
        pOut = CopyRoomScriptChain(pChains, pOut, 0);
    }

    offset = pVariant->wSwitchTableOffset;
    pChains = (const RoomBlobTable *)((const u8 *)pVariant + offset);
    for (i = 0; i < count;)
    {
        offset = pOut - (u8 *)g_pRoomScriptChainTable;
        if (g_wRoomResourceFlags_candidate & 1)
            g_pRoomScriptChainTable->awChainOffsets[i + 1] = offset;
        else
            g_pRoomScriptChainTable->awChainOffsets[i] = offset;
        pOut = CopyRoomScriptChain(pChains, pOut, i);
        i++;
    }
    return pOut;
}
