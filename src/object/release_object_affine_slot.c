#include "types.h"
#include "graphics/object.h"
#include "graphics/graphics.h"

void ReleaseObjectAffineSlot(Object *obj)
{
    u16 slot;

    if (obj->oam.affineMode == 1 || obj->oam.affineMode == 3)
    {
        obj->oam.affineMode = 0;
        slot = GetObjectAffineSlotId(&obj->oam);
        SetObjectAffineSlotId(&obj->oam, 0);
        FreeAffineSlot(slot);
    }
}
