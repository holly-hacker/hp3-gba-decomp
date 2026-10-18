#include "types.h"
#include "area.h"

// Runs the waypoint's chain, as RespawnGroupAndRunChain(0, chain); ShouldRunRoomIndex(0) is
// always false, so group 0 is never respawned.
void RunRoomRouteWaypointChain(u8 route, u8 waypoint)
{
    RoomRoute *pRoute;
    RoomRouteWaypoint *pWaypoint;
    u8 chain;

    pRoute = (RoomRoute *)((u8 *)g_pRoomRouteTable + g_pRoomRouteTable->awOffsets[route]);
    pWaypoint = &pRoute->aWaypoints[waypoint];
    chain = pWaypoint->bChain;
    if (ShouldRunRoomIndex(0))
    {
        g_dwRoomChainRanThisFrame_candidate = 1;
        SpawnMissingRoomGroupActors(0);
    }
    if (ShouldRunRoomIndex(chain))
    {
        g_dwRoomChainRanThisFrame_candidate = 1;
        RunRoomScriptChain(chain, 0);
    }
}
