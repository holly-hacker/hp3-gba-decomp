#include "types.h"
#include "graphics/object_anim.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_RoomObjUnkCSprite = {
    (void *)gObjectSprite2_111Tiles, (void *)gObjectSprite2_111Frames,
};

// The constructor starts the object at command 2, or at 0 when its third
// record argument is nonzero.
const u8 g_abRoomObjUnkCAnimData[46] = {
    // 0
    ANIM_FRAME(0, 3), ANIM_END,
    // 2
    ANIM_FRAME(1, 3), ANIM_END,
    // 4
    ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1), ANIM_FRAME(4, 1),
    ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1), ANIM_FRAME(8, 1),
    ANIM_FRAME(9, 1), ANIM_END,
    // 14
    ANIM_FRAME(8, 2), ANIM_FRAME(7, 2), ANIM_FRAME(6, 2), ANIM_FRAME(5, 2),
    ANIM_FRAME(4, 2), ANIM_FRAME(3, 2), ANIM_FRAME(2, 2), ANIM_FRAME(1, 2),
    ANIM_END,
};
