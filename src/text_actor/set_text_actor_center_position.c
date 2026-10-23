#include "types.h"
#include "text_actor.h"

// Places a text actor with its top edge at y, centered on x.
void SetTextActorCenterPosition(Actor *pActor, s16 x, s16 y)
{
    SnapActorPosition(pActor, (x - (TEXT_ACTOR_WIDTH(pActor) >> 1)) << 16, y << 16);
}
