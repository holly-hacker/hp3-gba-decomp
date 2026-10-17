#include "types.h"
#include "area.h"
#include "math.h"
#include "actor.h"
#include "actor_inline.h"
#include "overworld/room_script_bytecode.h"

// Action states 8, 11 and 13: walks the route's waypoints once, then stops and runs the
// respawn row and chain in modeState.route.finish, if any.
void TickActorWalkRouteOnce(Actor *actor)
{
    u8 route;
    u8 waypoint;
    u8 subState;
    u16 direction;
    FixedPoint pos;
    Point target;

    route = actor->modeState.route.bRoute;
    waypoint = actor->modeState.route.bWaypoint;

    subState = actor->bActionSubState;
    switch (subState) {
    case 0:
        SetActorActionSubState(actor, 3);
        target = GetRoomRouteWaypointPos(route, waypoint);
        IntToFixedPoint(target, &actor->moveTarget);
        break;
    case 3:
        pos = actor->pos;
        target = actor->moveTarget;
        direction = GetDirectionToTarget(actor->dwFlags, pos, target, actor->nMoveSpeed);
        if (((actor->dwFlags & ActorFlagFourWayDirections_candidate) && direction == Direction4None)
            || direction == DirectionNone) {
            RunRoomRouteWaypointChain(route, waypoint);
            waypoint++;
            if (waypoint == GetRoomRouteWaypointCount(route)) {
                direction = actor->bFacing;
                CancelActorMove_candidate(actor);
                SetActorActionSubState(actor, 14);
            }
            else {
                actor->modeState.route.bWaypoint = waypoint;
                target = GetRoomRouteWaypointPos(route, waypoint);
                IntToFixedPoint(target, &actor->moveTarget);
                // BUG: target is in pixels but pos is 16.16, so this faces the actor toward the
                // room's top-left corner for a tick, until case 3 faces it toward the waypoint.
                target.x -= pos.x;
                target.y -= pos.y;
                direction = GetDirectionFromVector(target, actor->dwFlags & ActorFlagFourWayDirections_candidate);
            }
        }
        if (actor->bFacing != direction) {
            actor->bFacing = direction;
            actor->bActionFlags |= 0x10;
        }
        break;
    case 14:
        if (actor->modeState.route.finish.wPair != 0)
            RespawnGroupAndRunChain(actor->modeState.route.finish.rows.bRespawnRow,
                                            actor->modeState.route.finish.rows.bChainRow);
        else {
            SetActorActionState(actor, 3);
            SetActorActionSubState(actor, 2);
        }
        if ((actor->dwFlags & ActorFlagRoomScriptYield) && g_bRoomScriptYieldOpcode == RSOP_StartActorAnimSequence) {
            actor->dwFlags &= ~ActorFlagRoomScriptYield;
            ResumeRoomScriptChain();
        }
        break;
    default:
        TickActorIdle(actor);
        break;
    }
}
