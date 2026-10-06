#include "types.h"
#include "overworld/room_object.h"

// Room object constructor for tile objType 13, a portrait door: a type 2 door
// whose collision callback routes the change through portrait_room_passage.
Object *SpawnPortraitDoorObject(u8 bColumn, u8 bRow)
{
    Object *pObj = SpawnDoorObject(bColumn, bRow);

    pObj->apfnCollisionCallback[0] = sub_0802BBAC;
    return pObj;
}
