#include "types.h"
#include "actor.h"
#include "actor_inline.h"
#include "area.h"
#include "overworld/room_script_bytecode.h"

// Action state 15, started by RoomScriptOpStartTileActorScript: walks to the pixel
// position (scriptState.wScriptPc, modeState.scriptWalk.wTargetY), then runs its finish
// chain or returns to action state 3.
void TickActorScriptWalk(Actor *actor)
{
    u8 direction;
    FixedPoint pos;
    FixedPoint target;

    switch (actor->bActionSubState) {
    case 0:
        SetActorActionSubState(actor, 3);
        actor->moveTarget.x = actor->scriptState.wScriptPc << 16;
        actor->moveTarget.y = actor->modeState.scriptWalk.wTargetY << 16;
        break;
    case 2:
    case 3:
        pos = actor->pos;
        target = actor->moveTarget;
        direction = GetDirectionToTarget(actor->dwFlags, pos, target, actor->nMoveSpeed);
        if (((actor->dwFlags & ActorFlagFourWayDirections) && direction == Direction4None)
            || direction == DirectionNone) {
            StopActorMotion(actor);
            SetActorActionSubState(actor, 14);
        }
        else if (actor->bFacing != direction) {
            actor->bFacing = direction;
            actor->bActionFlags |= 0x10;
        }
        break;
    case 14:
        if (actor->modeState.scriptWalk.args.dwWord & 0xFFFF00)
            RespawnGroupAndRunChain(actor->modeState.scriptWalk.args.bytes.bRespawnRow,
                                            actor->modeState.scriptWalk.args.bytes.bChainRow);
        else {
            SetActorActionState(actor, 3);
            SetActorActionSubState(actor, 2);
        }
        if ((actor->dwFlags & ActorFlagRoomScriptYield) && g_bRoomScriptYieldOpcode == RSOP_StartTileActorScript) {
            actor->dwFlags &= ~ActorFlagRoomScriptYield;
            ResumeRoomScriptChain();
        }
        break;
    default:
        TickActorIdle(actor);
        break;
    }
}
