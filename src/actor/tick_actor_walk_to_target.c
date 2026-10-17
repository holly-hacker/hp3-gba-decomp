#include "types.h"
#include "area.h"
#include "math.h"
#include "particles.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "overworld/room_script.h"
#include "overworld/room_script_bytecode.h"
#include "hero.h"

// Action state 0x20: walks around obstacles to moveTarget, then stands in action state 0.
void TickActorWalkToTarget(Actor *actor)
{
    u8 direction;

    switch (actor->bActionSubState) {
    case 0:
        SetActorActionSubState(actor, 3);
        break;
    case 3:
        if ((s16)(actor->pos.x >> 16) > (actor->moveTarget.x >> 16) - 2
            && (s16)(actor->pos.x >> 16) < (actor->moveTarget.x >> 16) + 2
            && (s16)(actor->pos.y >> 16) > (actor->moveTarget.y >> 16) - 2
            && (s16)(actor->pos.y >> 16) < (actor->moveTarget.y >> 16) + 2) {
            CancelActorMove_candidate(actor);
            SetActorActionState(actor, 0);
            SetPartyMemberAnim(actor, PartyAnimStand);
            if ((actor->dwFlags & ActorFlagRoomScriptYield) && g_bRoomScriptYieldOpcode == RSOP_StartTileActorScript) {
                ClearActorFlags(actor, ActorFlagRoomScriptYield | ActorFlagHasTickLogic);
                ResumeRoomScriptChain();
            }
        }
        else {
            direction = GetUnblockedDirectionToTarget(actor, actor->pos, actor->moveTarget, 0x10000);
            actor->vel.x = FixedMultiply(g_aDirection8Vectors[direction][0], actor->nMoveSpeed);
            actor->vel.y = FixedMultiply(g_aDirection8Vectors[direction][1], actor->nMoveSpeed);
            if (actor->bActionSubState == 0 || actor->bFacing != direction) {
                SetPartyMemberAnim(actor, PartyAnimWalk);
                actor->bFacing = direction;
            }
        }
        break;
    }
}
