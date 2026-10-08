#include "types.h"
#include "graphics/object.h"
#include "graphics/graphics.h"

u32 AllocObjectAffineSlot(Object *obj)
{
    u16 slot;

    if (obj->oam.affineMode == 1 || obj->oam.affineMode == 3)
    {
        slot = GetObjectAffineSlotId(&obj->oam);
    }
    else
    {
        slot = AllocAffineSlot();
        SetObjectAffineSlotId(&obj->oam, slot);
    }

    return slot;
}
