#include "types.h"
#include "actor_anim.h"
#include "pscreen_folio_bruti.h"
#include "pscreen_folio_universitas.h"

const u8 g_aFolioBrutiCursorAnim[] = {
    ANIM_FRAME(0, 5), ANIM_FRAME(1, 5), ANIM_FRAME(2, 5), ANIM_FRAME(3, 5),
    ANIM_FRAME(4, 5), ANIM_FRAME(5, 5), ANIM_FRAME(6, 5), ANIM_FRAME(7, 5),
    ANIM_FRAME(4, 5), ANIM_FRAME(5, 5), ANIM_FRAME(6, 5), ANIM_FRAME(7, 5),
    ANIM_FRAME(4, 5), ANIM_FRAME(5, 5), ANIM_FRAME(6, 5), ANIM_FRAME(7, 5),
    ANIM_FRAME(8, 5), ANIM_FRAME(9, 5), ANIM_FRAME(10, 5), ANIM_FRAME(11, 5),
    ANIM_JUMP(0),
};

// A single held frame, 14 bytes like the streams below.
const u8 g_aFolioBrutiDotUnknownAnim[14] = {
    ANIM_FRAME(4, 0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
    ANIM_FRAME(0, 0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
};

// One 14-byte stream per spell-effectiveness step.
const u8 g_aFolioBrutiDotAnims[4][14] = {
    {
        ANIM_FRAME(0, 0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
        ANIM_FRAME(0, 0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
    },
    {
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_JUMP(0), ANIM_FRAME(0, 0),
        ANIM_FRAME(0, 0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
    },
    {
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(1, 4),
        ANIM_JUMP(0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
    },
    {
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(2, 4), ANIM_FRAME(1, 4), ANIM_JUMP(0),
    },
};
