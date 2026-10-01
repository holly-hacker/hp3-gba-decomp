#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 13: a type 2 object with its own collision callback.
Object *sub_0802BC54(u8 bColumn, u8 bRow)
{
    Object *pObj = sub_0802BB00(bColumn, bRow);

    pObj->apfnCollisionCallback[0] = sub_0802BBAC;
    return pObj;
}
