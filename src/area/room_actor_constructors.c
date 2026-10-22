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
#include "trigger_actor.h"
#include "world_actors.h"

// Room tile actorType -> constructor table.
// Type 0 is unused.
const RoomActorConstructor g_apRoomActorConstructors[ROOM_ACTOR_TYPE_COUNT] = {
    0,
    SpawnRoomTileAnimationActor_candidate,
    SpawnDoorActor,
    SpawnSwitchActor,
    SpawnTriggerZoneActor,
    SpawnWorldActor,
    SpawnNpcActor,
    SpawnTriggerRectActor,
    SpawnPushResetButtonActor,
    SpawnChestActor,
    SpawnSpongifyPadActor,
    SpawnFlamePillarActor,
    SpawnRaisingPlatformActor,
    SpawnPortraitDoorActor,
};
