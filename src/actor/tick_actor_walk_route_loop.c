#include "types.h"
#include "area.h"
#include "math.h"
#include "actor.h"
#include "actor_inline.h"

// Action states 7 and 10: walks the route's waypoints in order, wrapping to the
// first, and waits scriptState.wScriptPc ticks at each.
void TickActorWalkRouteLoop(Actor *actor)
{
    u8 route;
    u8 waypoint;
    u8 waypointCount;
    u8 subState;
    u8 facing;
    u8 direction;
    FixedPoint pos;
    Point target;

    route = actor->modeState.route.bRoute;
    waypoint = actor->modeState.route.bWaypoint;
    waypointCount = GetRoomRouteWaypointCount(route);
    subState = actor->bActionSubState;
    facing = actor->bFacing;

    switch (subState) {
    case 0:
        SetActorActionSubState(actor, 3);
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
            waypoint = ++actor->modeState.route.bWaypoint;
            if (waypoint >= waypointCount) {
                actor->modeState.route.bWaypoint = 0;
                waypoint = 0;
            }
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
}
