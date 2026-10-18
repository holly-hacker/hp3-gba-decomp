#include "types.h"
#include "area.h"

// Copies route `index` (a u32 count, then 8-byte waypoints); returns its end.
u8 *CopyRoomRouteWaypoints(const RoomBlobTable *pTable, u8 *pDst, u8 index)
{
    const RoomRoute *pSrc;
    RoomRoute *pRoute;
    u8 count;
    u8 i;
    u16 offset;

    offset = pTable->awOffsets[index];
    pSrc = (const RoomRoute *)((const u8 *)pTable + offset);
    pRoute = (RoomRoute *)pDst;
    count = pSrc->dwCount;
    pRoute->dwCount = count;
    for (i = 0; i < count; i++)
        pRoute->aWaypoints[i] = pSrc->aWaypoints[i];
    offset = count * sizeof(RoomRouteWaypoint);
    pDst += offset + 4;
    return pDst;
}
