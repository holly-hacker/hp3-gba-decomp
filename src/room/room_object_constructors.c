#include "types.h"
#include "overworld/room_object.h"

// Room tile objType -> constructor table; see docs/formats/rooms.md.
// Type 0 is unused.
const RoomObjectConstructor g_apRoomObjectConstructors[ROOM_OBJECT_TYPE_COUNT] = {
    0,
    SpawnRoomTileAnimationObject_candidate,
    sub_0802BB00,
    sub_08044C00,
    sub_08026414,
    sub_08045AE8,
    sub_0802F500,
    sub_08026348,
    sub_08035540,
    SpawnScriptedOneTimeObject,
    sub_08040038,
    sub_08044894,
    sub_0803B64C,
    sub_0802BC54,
};
