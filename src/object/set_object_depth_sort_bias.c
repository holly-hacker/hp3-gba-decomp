#include "types.h"
#include "object.h"

// See SortObjectsByDepth_candidate, which folds this into its sort key.
void SetObjectDepthSortBias(Object *obj, u8 bias)
{
    if (obj != NULL)
    {
        obj->bDepthSortBias = bias;
    }
}
