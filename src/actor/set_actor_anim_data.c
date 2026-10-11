#include "actor.h"

// Starts the animation command stream at command startCommand of pAnimData. A
// new sprite record also invalidates the loaded frame so it is reloaded.
void SetActorAnimData(Actor *actor, const void *pAnimTable, const void *pAnimData, u8 startCommand)
{
    actor->anim.pAnimFrameBase = (u8 *)pAnimData + startCommand * 2;
    actor->anim.pAnimFrameCursor = actor->anim.pAnimFrameBase;

    if (actor->anim.pAnimTable != pAnimTable) {
        actor->anim.pAnimTable = (ActorAssetRecord *)pAnimTable;
        actor->anim.bAnimFrameIndex_candidate = 0xFF;
        actor->anim.bLastAnimFrameValue = 0xFF;
    }

    RunActorAnimCommands(actor);
    LoadActorAnimFrameBounds(actor);
}
