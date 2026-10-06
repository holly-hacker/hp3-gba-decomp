#include "types.h"
#include "overworld/room_object.h"

// Room tile objType -> constructor table; see docs/formats/rooms.md.
// Type 0 is unused.
const RoomObjectConstructor g_apRoomObjectConstructors[ROOM_OBJECT_TYPE_COUNT] = {
    0,
    SpawnRoomTileAnimationObject_candidate,
    SpawnDoorObject,
    SpawnSwitchObject,
    SpawnTriggerZoneObject,
    SpawnPropObject,
    SpawnNpcObject,
    SpawnTriggerRectObject,
    SpawnPushResetButtonObject,
    SpawnScriptedOneTimeObject,
    SpawnSpongifyPadObject,
    SpawnFlamePillarObject,
    SpawnRaisingPlatformObject,
    SpawnPortraitDoorObject,
};
