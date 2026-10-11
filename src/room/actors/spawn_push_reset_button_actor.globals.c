#include "types.h"
#include "overworld/room_actor.h"
#include "gen/graphics/overworld.h"

const ActorGfxRecord g_RoomActorUnk8Sprite = {
    (void *)gButtonTiles, (void *)gButtonFrames,
};

// Indexed by the actor's character id.
const ActorGfxRecord *const g_apRoomActorUnk8AssetRecords[2] = {
    &g_RoomActorUnk8Sprite,
    &g_RoomActorUnk8Sprite,
};

const void *const g_apRoomActorUnk8EffectData[2] = {
    gButtonPalette,
    gButtonPalette,
};
