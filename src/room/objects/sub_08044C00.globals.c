#include "types.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_aRoomObjUnk3Sprites[5] = {
    { (void *)gObjectSprite2_110Tiles, (void *)gObjectSprite2_110Frames },
    { (void *)gObjectSprite2_119Tiles, (void *)gObjectSprite2_119Frames },
    { (void *)gObjectSprite2_120Tiles, (void *)gObjectSprite2_120Frames },
    { (void *)gObjectSprite2_121Tiles, (void *)gObjectSprite2_121Frames },
    { (void *)gObjectSprite2_122Tiles, (void *)gObjectSprite2_122Frames },
};

// Indexed by the object's character id, 0-10; both lists end with NULL.
const ObjectGfxRecord *const g_apRoomObjUnk3AssetRecords[12] = {
    &g_aRoomObjUnk3Sprites[1],
    &g_aRoomObjUnk3Sprites[1],
    &g_aRoomObjUnk3Sprites[1],
    &g_aRoomObjUnk3Sprites[0],
    &g_aRoomObjUnk3Sprites[0],
    &g_aRoomObjUnk3Sprites[0],
    &g_aRoomObjUnk3Sprites[2],
    &g_aRoomObjUnk3Sprites[3],
    &g_aRoomObjUnk3Sprites[4],
    &g_aRoomObjUnk3Sprites[3],
    &g_aRoomObjUnk3Sprites[2],
    NULL,
};

const void *const g_apRoomObjUnk3EffectData[12] = {
    gObjectSprite2_122Palette,
    gObjectSprite2_122Palette,
    gObjectSprite2_122Palette,
    gObjectSprite2_110Palette,
    gObjectSprite2_110Palette,
    gObjectSprite2_110Palette,
    gObjectSprite2_123Palette,
    gObjectSprite2_124Palette,
    gObjectSprite2_125Palette,
    gObjectSprite2_124Palette,
    gObjectSprite2_123Palette,
    NULL,
};
