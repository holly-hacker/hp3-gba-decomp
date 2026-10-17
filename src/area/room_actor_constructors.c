#include "types.h"
#include "area.h"
#include "chest_actor.h"
#include "overworld/room_actor.h"
#include "flipbook.h"
#include "invisible_actors.h"
#include "map_doors.h"
#include "npc_actor.h"
#include "pressure_pad_actor.h"
#include "rising_platform_actor.h"
#include "spongify_pad_actor.h"
#include "torch_actor.h"

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
