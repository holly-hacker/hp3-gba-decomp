#include "types.h"
#include "graphics/object.h"

void TickObjectAffineEffect(Object *obj)
{
    obj->bAffineEffectTimer--;
    obj->nAffineScaleX += obj->nAffineScaleVelX;
    obj->nAffineScaleY += obj->nAffineScaleVelY;
    SetObjectAffineTransform(obj, obj->nAffineScaleX, obj->nAffineScaleY, obj->wAffineAngle,
                             obj->bAffineMode);
}
