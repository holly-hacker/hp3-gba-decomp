#include "types.h"
#include "area.h"

// The room's spawn point for (entryId, index), or the default one for index.
const RoomEntryPoint *FindRoomEntryPoint(u8 entryId, u8 index)
{
    const RoomEntryPoint *pEntry;
    u8 i;

    pEntry = &g_aDefaultRoomEntryPoints[index];
    for (i = 0; i < g_pRoomTableBuffer->wRecordCount; i++)
    {
        if (g_pRoomTableBuffer->aRecords[i].bEntryId == entryId && g_pRoomTableBuffer->aRecords[i].bIndex == index)
        {
            pEntry = &g_pRoomTableBuffer->aRecords[i];
            break;
        }
    }
    return pEntry;
}
