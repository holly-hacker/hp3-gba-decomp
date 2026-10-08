#include "graphics/object.h"

void SetObjectActionSubState(Object *obj, u8 state)
{
    if (obj->bActionSubState != state) {
        obj->bActionSubState = state;
        obj->bActionFlags |= 0x2;
    }
}
