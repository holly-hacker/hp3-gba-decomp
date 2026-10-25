#include "actor.h"

// Like SetActorActionState: no-op if unchanged, otherwise stores the value and
// raises bActionFlags bit 0x4. Also resumes animation (sets ActorFlagHasAnimation,
// clears ActorFlagActionAnimDone).
void SetActorAnchorVariantTableIndex(Actor *actor, u8 tableIndex)
{
    if (tableIndex != actor->bAnchorVariantTableIndex) {
        actor->bAnchorVariantTableIndex = tableIndex;
        actor->dwFlags |= ActorFlagHasAnimation;
        actor->bActionFlags |= 4;
        actor->dwFlags &= ~ActorFlagActionAnimDone;
    }
}
