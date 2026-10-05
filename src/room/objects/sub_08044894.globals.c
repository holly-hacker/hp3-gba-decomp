#include "types.h"
#include "graphics/object_anim.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_aRoomObjUnkBSprites[3] = {
    { (void *)gObjectSprite2_116Tiles, (void *)gObjectSprite2_116Frames },
    { (void *)gObjectSprite2_117Tiles, (void *)gObjectSprite2_117Frames },
    { (void *)gObjectSprite2_118Tiles, (void *)gObjectSprite2_118Frames },
};

// Indexed by the object's character id.
const ObjectGfxRecord *const g_apRoomObjUnkBAnimFrames[3] = {
    &g_aRoomObjUnkBSprites[0],
    &g_aRoomObjUnkBSprites[1],
    &g_aRoomObjUnkBSprites[2],
};

const void *const g_apRoomObjUnkBEffectData[3] = {
    gObjectSprite2_118Palette,
    gObjectSprite2_118Palette,
    gObjectSprite2_118Palette,
};

const u8 g_abRoomObjUnkBAnimData[22] = {
    // 0
    ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
    ANIM_FRAME(4, 3), ANIM_JUMP(2),
    // 6
    ANIM_FRAME(2, 3), ANIM_FRAME(1, 3), ANIM_FRAME(0, 3), ANIM_FRAME(5, 3),
    ANIM_END,
};
