#include "types.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_RoomObjUnk8Sprite = {
    (void *)gObjectSprite2_110Tiles, (void *)gObjectSprite2_110Frames,
};

// Indexed by the object's character id.
const ObjectGfxRecord *const g_apRoomObjUnk8AssetRecords[2] = {
    &g_RoomObjUnk8Sprite,
    &g_RoomObjUnk8Sprite,
};

const void *const g_apRoomObjUnk8EffectData[2] = {
    gObjectSprite2_110Palette,
    gObjectSprite2_110Palette,
};
