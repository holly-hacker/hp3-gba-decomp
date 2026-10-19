#include "types.h"
#include "actor.h"
#include "area.h"
#include "math.h"
#include "collision.h"

// Collision callback with no known user: when the player comes within bPauseRange
// pixels, the actor pauses (action state 6, restarting its pause timer) and
// runs its pair on entering the pause, and the player is kept out of its box.
void HandlePausingActorTouch(Actor *pSelf, Actor *pOther)
{
    u32 range;

    if (pOther->wActorType != RoomActorType_Player)
        return;

    range = pSelf->bPauseRange << 16;
    if (ApproximateDistance(pSelf->posPrev, pOther->posPrev) > range)
        return;

    if (pSelf->bActionState != 6)
    {
        pSelf->vel.x = pSelf->vel.y = 0;
        pSelf->posPrev = pSelf->pos;
        pSelf->bResumeActionState = pSelf->bActionState;
        pSelf->bActionFlags &= 4;
        SetActorActionState(pSelf, 6);
        RespawnGroupAndRunChain(pSelf->bRespawnRow, pSelf->bChainRow);
    }

    pSelf->wPauseTimer = pSelf->wPauseDuration;
    BlockActorWithTerrainBox(pSelf, pOther);
}
