#include "types.h"
#include "actor.h"
#include "hero.h"
#include "input.h"
#include "math.h"
#include "scroll.h"
#include "world_actors.h"

// Action state 33: the D-pad drives the prop while it stays on screen; A or B returns
// control to the player.
void TickPropActorPlayerControl(Actor *pActor)
{
    u32 stopped;
    s8 direction;
    IntPoint next;
    s32 camera[2];

    stopped = 0;
    if (pActor->vel.x == 0 && pActor->vel.y == 0)
        stopped = 1;

    direction = ApplyTerrainToWalkVelocity(pActor, GetDpadDirection());
    if (direction != DirectionNone)
    {
        if (stopped == 1 || pActor->bFacing != direction)
        {
            SetActorActionSubState(pActor, 3);
            pActor->bFacing = direction;
        }
        else
        {
            SetActorActionSubState(pActor, 2);
            CancelActorMove_candidate(pActor);
        }
    }
    else
    {
        SetActorActionSubState(pActor, 2);
        CancelActorMove_candidate(pActor);
    }

    if ((pActor->bActionFlags & 2) && pActor->bActionSubState == 3)
    {
        pActor->bActionFlags &= ~2;
        pActor->vel.x = FixedMultiply(g_aDirection8Vectors[pActor->bFacing][0], pActor->nMoveSpeed);
        pActor->vel.y = FixedMultiply(g_aDirection8Vectors[pActor->bFacing][1], pActor->nMoveSpeed);
        next.x = (pActor->posPrev.x + pActor->vel.x) >> 16;
        next.y = (pActor->posPrev.y + pActor->vel.y) >> 16;
        GetCameraPosition(camera);
        if (next.x < camera[0] || next.x > camera[0] + 240 || next.y < camera[1] || next.y > camera[1] + 160)
        {
            SetActorActionSubState(pActor, 2);
            CancelActorMove_candidate(pActor);
        }
    }

    if (g_wKeysPressed & (KeyA | KeyB))
    {
        SetActorActionSubState(pActor, 2);
        SetActorActionState(pActor, 0);
        SetActorActionState(g_pPlayerActor, 0x21);
        ROOM_ACTOR_TRIGGER_STATE(pActor)->b6A = 0;
    }
}
