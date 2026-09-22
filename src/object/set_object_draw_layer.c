#include "types.h"
#include "object.h"

// See SortObjectsByDepth and TickObjectList's per-layer particle flush.
void SetObjectDrawLayer(Object *obj, u8 layer)
{
    ObjectFlagsD5 *pFlags;
    u32 type;

    if (obj == NULL)
        return;

    type = layer;
    pFlags = (ObjectFlagsD5 *)&obj->bGfxSlotAndFlags;
    pFlags->bDrawLayer = type;
}
