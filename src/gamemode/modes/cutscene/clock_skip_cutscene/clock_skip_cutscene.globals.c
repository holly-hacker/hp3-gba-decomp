#include "types.h"
#include "graphics/object.h"
#include "graphics/object_anim.h"
#include "cutscene/clock_skip_cutscene.h"
#include "gen/graphics/overworld.h"

const ObjectAssetRecord g_ClockSkipObject1Asset = {
    (void *)gClockSkipObject1Tiles, (void *)gClockSkipObject1Frames, (void *)gClockSkipObject1Palette, 0,
};

const ObjectAssetRecord g_ClockSkipObject2Asset = {
    (void *)gClockSkipObject2Tiles, (void *)gClockSkipObject2Frames, (void *)gClockSkipObject2Palette, 0,
};

// One animation per object.
const u8 g_ClockSkipAnimData[2][54] = {
    {
        ANIM_FRAME(0, 1), ANIM_FRAME(1, 1), ANIM_FRAME(2, 1), ANIM_FRAME(3, 1),
        ANIM_FRAME(4, 1), ANIM_FRAME(5, 1), ANIM_FRAME(6, 1), ANIM_FRAME(7, 1),
        ANIM_FRAME(8, 1), ANIM_FRAME(9, 1), ANIM_FRAME(10, 1), ANIM_FRAME(11, 1),
        ANIM_FRAME(12, 1), ANIM_FRAME(13, 1), ANIM_FRAME(14, 1), ANIM_FRAME(15, 1),
        ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(0, 12), ANIM_SOUND(19),
        ANIM_FRAME(1, 12), ANIM_SOUND(19),
        ANIM_FRAME(2, 12), ANIM_SOUND(19),
        ANIM_FRAME(3, 12), ANIM_SOUND(19),
        ANIM_FRAME(4, 12), ANIM_SOUND(19),
        ANIM_FRAME(5, 12), ANIM_SOUND(19),
        ANIM_FRAME(6, 12), ANIM_SOUND(19),
        ANIM_FRAME(7, 12), ANIM_SOUND(19),
        ANIM_FRAME(8, 12), ANIM_SOUND(19),
        ANIM_FRAME(9, 12), ANIM_SOUND(19),
        ANIM_FRAME(10, 12), ANIM_SOUND(19),
        ANIM_FRAME(11, 12), ANIM_SOUND(19),
        ANIM_JUMP(0),
    },
};
