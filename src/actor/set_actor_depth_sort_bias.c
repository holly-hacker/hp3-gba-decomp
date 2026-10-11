#include "types.h"
#include "actor.h"

// See SortActorsByDepth, which folds this into its sort key.
void SetActorDepthSortBias(Actor *actor, u8 bias)
{
    if (actor != NULL)
    {
        actor->bDepthSortBias = bias;
    }
}
