#include "types.h"
#include "graphics/object_anim.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

const ObjectGfxRecord g_RoomChestSprite = {
    (void *)gChestTiles, (void *)gChestFrames,
};

// Indexed by the object's kind.
const ObjectGfxRecord *const g_apRoomChestAnimFrames[4] = {
    &g_RoomChestSprite,
    &g_RoomChestSprite,
    &g_RoomChestSprite,
    &g_RoomChestSprite,
};

// One animation block per kind. A closed chest starts at command 0, opening
// plays from command 2, and a chest whose flag is already set starts at
// command 8.
const u8 g_abRoomChestAnimData[4][100] = {
    {
        // 0
        ANIM_FRAME(15, 3), ANIM_END,
        // 2
        ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3),
        ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_END,
    },
    {
        // 0
        ANIM_FRAME(32, 3), ANIM_END,
        // 2
        ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3),
        ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_END,
        // 10
        ANIM_FRAME(32, 3), ANIM_FRAME(33, 3), ANIM_FRAME(34, 3), ANIM_FRAME(35, 3),
        ANIM_FRAME(36, 3), ANIM_FRAME(15, 3), ANIM_END,
    },
    {
        // 0
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
        ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1),
        ANIM_END,
        // 9
        ANIM_FRAME(7, 1), ANIM_FRAME(6, 1), ANIM_FRAME(5, 1), ANIM_FRAME(4, 1),
        ANIM_FRAME(3, 1), ANIM_FRAME(2, 1), ANIM_FRAME(1, 1), ANIM_FRAME(0, 1),
        ANIM_FRAME(31, 1), ANIM_END,
        // 19
        ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3),
        ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_FRAME(22, 2),
        ANIM_FRAME(23, 2), ANIM_FRAME(24, 2), ANIM_FRAME(25, 2), ANIM_FRAME(26, 2),
        ANIM_FRAME(27, 2), ANIM_FRAME(28, 2), ANIM_FRAME(29, 2), ANIM_FRAME(30, 2),
        ANIM_FRAME(31, 2), ANIM_END,
    },
    {
        // 0
        ANIM_FRAME(15, 3), ANIM_END,
        // 2
        ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_FRAME(18, 3),
        ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_END,
    },
};
