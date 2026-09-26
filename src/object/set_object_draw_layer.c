#include "types.h"
#include "object.h"

// See SortObjectsByDepth and TickObjectList's per-layer particle flush.
void SetObjectDrawLayer(Object *obj, u8 layer)
{
    u32 type;

    if (obj == NULL)
        return;

    type = layer;
    obj->bDrawLayer = type;
}
