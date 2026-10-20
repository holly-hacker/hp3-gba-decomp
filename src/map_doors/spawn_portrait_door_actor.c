#include "types.h"
#include "map_doors.h"

// Room actor constructor for tile actorType 13, a portrait door: a type 2 door
// whose collision callback routes the change through portrait_room_passage.
Actor *SpawnPortraitDoorActor(u8 bColumn, u8 bRow)
{
    Actor *pActor = SpawnDoorActor(bColumn, bRow);

    pActor->apfnCollisionCallback[0] = HandlePortraitDoorTouch;
    return pActor;
}
