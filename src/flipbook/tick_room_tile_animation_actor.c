#include "types.h"
#include "actor.h"
#include "flipbook.h"

// Tick of the room actor that owns the animation at its position; the action
// state is a request, handled once.
void TickRoomTileAnimationActor(Actor *pActor)
{
    switch (pActor->bActionState)
    {
    case 0:
        break;
    case 1:
        pActor->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    case 4:
        ResumeRoomTileAnimation((s16)(pActor->pos.x >> 16), (s16)(pActor->pos.y >> 16));
        // fall through
    case 3:
        SetActorActionState(pActor, 0);
        break;
    case 5:
        HaltRoomTileAnimation((s16)(pActor->pos.x >> 16), (s16)(pActor->pos.y >> 16));
        SetActorActionState(pActor, 0);
        break;
    }
}
