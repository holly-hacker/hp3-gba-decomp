#include "types.h"
#include "graphics/object_anim.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_aRoomObjUnkASprites[4] = {
    { (void *)gObjectSprite2_112Tiles, (void *)gObjectSprite2_112Frames },
    { (void *)gObjectSprite2_113Tiles, (void *)gObjectSprite2_113Frames },
    { (void *)gObjectSprite2_114Tiles, (void *)gObjectSprite2_114Frames },
    { (void *)gOverworldSpellEffect007Tiles, (void *)gOverworldSpellEffect007Frames },
};

// Indexed by the object's character id.
const ObjectGfxRecord *const g_apRoomObjUnkAAnimFrames[3] = {
    &g_aRoomObjUnkASprites[0],
    &g_aRoomObjUnkASprites[1],
    &g_aRoomObjUnkASprites[2],
};

const void *const g_apRoomObjUnkAEffectData[3] = {
    gObjectSprite2_114Palette,
    gObjectSprite2_114Palette,
    gObjectSprite2_115Palette,
};

// Command 5 is sub_08040680's spell effect.
const u8 g_abRoomObjUnkAAnimData[30] = {
    // 0
    ANIM_FRAME(0, 9), ANIM_FRAME(1, 9), ANIM_JUMP(0),
    0, 0, 0, 0,  // unused
    // 5
    ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
    ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_FRAME(24, 3), ANIM_FRAME(25, 3),
    ANIM_FRAME(42, 3), ANIM_END,
};
