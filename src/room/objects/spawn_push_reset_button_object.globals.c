#include "types.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ActorGfxRecord g_RoomObjUnk8Sprite = {
    (void *)gButtonTiles, (void *)gButtonFrames,
};

// Indexed by the object's character id.
const ActorGfxRecord *const g_apRoomObjUnk8AssetRecords[2] = {
    &g_RoomObjUnk8Sprite,
    &g_RoomObjUnk8Sprite,
};

const void *const g_apRoomObjUnk8EffectData[2] = {
    gButtonPalette,
    gButtonPalette,
};
