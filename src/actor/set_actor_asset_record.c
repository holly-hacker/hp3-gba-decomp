#include "types.h"
#include "actor.h"

void SetActorAssetRecord(Actor *actor, const void *rec)
{
    if (actor->anim.pAnimTable != rec)
    {
        actor->anim.pAnimTable = (ActorAssetRecord *)rec;
        actor->dwFlags |= ActorFlagAnimFrameLoaded;
    }

    SetActorAnimFrame(actor, 0);
}
