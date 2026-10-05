#include "types.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_RoomObjUnk8Sprite = {
    (void *)gButtonTiles, (void *)gButtonFrames,
};

// Indexed by the object's character id.
const ObjectGfxRecord *const g_apRoomObjUnk8AssetRecords[2] = {
    &g_RoomObjUnk8Sprite,
    &g_RoomObjUnk8Sprite,
};

const void *const g_apRoomObjUnk8EffectData[2] = {
    gButtonPalette,
    gButtonPalette,
};
