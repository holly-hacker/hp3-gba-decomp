#include "types.h"
#include "actor.h"

// See SortObjectsByDepth, which folds this into its sort key.
void SetActorDepthSortBias(Actor *actor, u8 bias)
{
    if (actor != NULL)
    {
        actor->bDepthSortBias = bias;
    }
}
