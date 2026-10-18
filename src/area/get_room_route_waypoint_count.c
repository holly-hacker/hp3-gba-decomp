#include "types.h"
#include "area.h"

// Number of waypoints in route `route`.
u8 GetRoomRouteWaypointCount(u8 route)
{
    RoomRoute *pRoute;

    pRoute = (RoomRoute *)((u8 *)g_pRoomRouteTable + g_pRoomRouteTable->awOffsets[route]);
    return pRoute->dwCount;
}
