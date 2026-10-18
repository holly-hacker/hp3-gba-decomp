#include "types.h"
#include "area.h"

// Position of a route waypoint.
IntPoint GetRoomRouteWaypointPos(u8 route, u8 waypoint)
{
    RoomRoute *pRoute;
    RoomRouteWaypoint *pWaypoint;
    IntPoint pos;

    pRoute = (RoomRoute *)((u8 *)g_pRoomRouteTable + g_pRoomRouteTable->awOffsets[route]);
    pWaypoint = &pRoute->aWaypoints[waypoint];
    pos.x = pWaypoint->nX;
    pos.y = pWaypoint->nY;
    return pos;
}
