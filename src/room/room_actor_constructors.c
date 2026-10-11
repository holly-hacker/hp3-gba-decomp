#include "types.h"
#include "overworld/room_actor.h"

// Room tile actorType -> constructor table; see docs/formats/rooms.md.
// Type 0 is unused.
const RoomActorConstructor g_apRoomActorConstructors[ROOM_ACTOR_TYPE_COUNT] = {
    0,
    SpawnRoomTileAnimationActor_candidate,
    SpawnDoorActor,
    SpawnSwitchActor,
    SpawnTriggerZoneActor,
    SpawnPropActor,
    SpawnNpcActor,
    SpawnTriggerRectActor,
    SpawnPushResetButtonActor,
    SpawnChestActor,
    SpawnSpongifyPadActor,
    SpawnFlamePillarActor,
    SpawnRaisingPlatformActor,
    SpawnPortraitDoorActor,
};
