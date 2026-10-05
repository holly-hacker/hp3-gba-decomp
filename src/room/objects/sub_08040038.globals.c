#include "types.h"
#include "graphics/object_anim.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_aRoomSpongifyPadSprites[4] = {
    { (void *)gSpongifyPadRug001Tiles, (void *)gSpongifyPadRug001Frames },
    { (void *)gSpongifyPadRug002Tiles, (void *)gSpongifyPadRug002Frames },
    { (void *)gSpongifyPadLeavesTiles, (void *)gSpongifyPadLeavesFrames },
    { (void *)gOverworldSpellEffect007Tiles, (void *)gOverworldSpellEffect007Frames },
};

// Indexed by the object's character id.
const ObjectGfxRecord *const g_apRoomSpongifyPadAnimFrames[3] = {
    &g_aRoomSpongifyPadSprites[0],
    &g_aRoomSpongifyPadSprites[1],
    &g_aRoomSpongifyPadSprites[2],
};

const void *const g_apRoomSpongifyPadEffectData[3] = {
    gSpongifyPadLeavesPalette,
    gSpongifyPadLeavesPalette,
    gObjectSprite2_115Palette,
};

// Command 5 is sub_08040680's spell effect.
const u8 g_abRoomSpongifyPadAnimData[30] = {
    // 0
    ANIM_FRAME(0, 9), ANIM_FRAME(1, 9), ANIM_JUMP(0),
    0, 0, 0, 0,  // unused
    // 5
    ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
    ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_FRAME(24, 3), ANIM_FRAME(25, 3),
    ANIM_FRAME(42, 3), ANIM_END,
};
