#include "types.h"
#include "area.h"
#include "math.h"
#include "actor.h"
#include "actor_inline.h"
#include "overworld/room_blob.h"

// Action states 9 and 12: walks the route back and forth between its first and
// last waypoints, waiting scriptState.wScriptPc ticks at each.
void TickActorWalkRoutePingPong(Actor *actor)
{
    u8 route;
    u8 waypoint;
    u8 waypointCount;
    u8 forward;
    u8 subState;
    u8 facing;
    u8 direction;
    FixedPoint pos;
    Point target;

    route = actor->modeState.route.bRoute;
    waypoint = actor->modeState.route.bWaypoint;
    waypointCount = GetRoomRouteWaypointCount(route);
    forward = actor->modeState.route.bForward;
    subState = actor->bActionSubState;
    facing = actor->bFacing;

    switch (subState) {
    case 0:
        SetActorActionSubState(actor, 3);
        // BUG: The stale `forward` stored at the end overwrites this, so a route started
        // while bForward is 0 first walks backward to waypoint 0.
        actor->modeState.route.bForward = 1;
        actor->dwStateTimer = 0;
        target = GetRoomRouteWaypointPos(route, waypoint);
        IntToFixedPoint(target, &actor->moveTarget);
        break;
    case 10:
        if (--actor->dwStateTimer == -1) {
            SetActorActionSubState(actor, 3);
            actor->dwStateTimer = 0;
            target = GetRoomRouteWaypointPos(route, waypoint);
            IntToFixedPoint(target, &actor->moveTarget);
        }
        break;
    case 3:
        pos = actor->pos;
        target = actor->moveTarget;
        direction = GetDirectionToTarget(actor->dwFlags, pos, target, actor->nMoveSpeed);
        if (((actor->dwFlags & ActorFlagFourWayDirections_candidate) && direction == Direction4None)
            || direction == DirectionNone) {
            RunRoomRouteWaypointChain(route, waypoint);
            if (forward)
                waypoint++;
            else if (waypoint != 0)
                waypoint--;
            if (waypoint >= waypointCount - 1)
                forward = 0;
            else if (waypoint == 0)
                forward = 1;
            actor->dwStateTimer = actor->scriptState.wScriptPc;
            SetActorActionSubState(actor, 10);
            target = GetRoomRouteWaypointPos(route, waypoint);
            IntToFixedPoint(target, &actor->moveTarget);
        }
        else if (direction != facing) {
            actor->bFacing = direction;
            actor->bActionFlags |= 0x10;
        }
        break;
    default:
        TickActorIdle(actor);
        break;
    }

    actor->modeState.route.bWaypoint = waypoint;
    actor->modeState.route.bForward = forward;
}
