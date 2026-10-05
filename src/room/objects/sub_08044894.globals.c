#include "types.h"
#include "graphics/object_anim.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_aRoomFlamePillarSprites[3] = {
    { (void *)gFlamePillar001Tiles, (void *)gFlamePillar001Frames },
    { (void *)gFlamePillar002Tiles, (void *)gFlamePillar002Frames },
    { (void *)gFlamePillar003Tiles, (void *)gFlamePillar003Frames },
};

// Indexed by the object's character id.
const ObjectGfxRecord *const g_apRoomFlamePillarAnimFrames[3] = {
    &g_aRoomFlamePillarSprites[0],
    &g_aRoomFlamePillarSprites[1],
    &g_aRoomFlamePillarSprites[2],
};

const void *const g_apRoomFlamePillarEffectData[3] = {
    gFlamePillar003Palette,
    gFlamePillar003Palette,
    gFlamePillar003Palette,
};

const u8 g_abRoomFlamePillarAnimData[22] = {
    // 0
    ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
    ANIM_FRAME(4, 3), ANIM_JUMP(2),
    // 6
    ANIM_FRAME(2, 3), ANIM_FRAME(1, 3), ANIM_FRAME(0, 3), ANIM_FRAME(5, 3),
    ANIM_END,
};
