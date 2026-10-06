#include "types.h"
#include "graphics/object_anim.h"
#include "menu/folio_bruti.h"
#include "menu/folio_universitas.h"

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

const u8 g_aFolioUniversitasCursorAnim[] = {
    ANIM_FRAME(0, 5), ANIM_FRAME(1, 5), ANIM_FRAME(2, 5), ANIM_FRAME(3, 5),
    ANIM_FRAME(4, 5), ANIM_FRAME(5, 5), ANIM_FRAME(6, 5), ANIM_FRAME(7, 5),
    ANIM_FRAME(4, 5), ANIM_FRAME(5, 5), ANIM_FRAME(6, 5), ANIM_FRAME(7, 5),
    ANIM_FRAME(4, 5), ANIM_FRAME(5, 5), ANIM_FRAME(6, 5), ANIM_FRAME(7, 5),
    ANIM_FRAME(8, 5), ANIM_FRAME(9, 5), ANIM_FRAME(10, 5), ANIM_FRAME(11, 5),
    ANIM_JUMP(0),
};

const u8 g_aFolioUniversitasBattleCursorAnim[] = {
    ANIM_FRAME(12, 5), ANIM_FRAME(13, 5), ANIM_FRAME(14, 5), ANIM_FRAME(15, 5),
    ANIM_FRAME(16, 5), ANIM_FRAME(17, 5), ANIM_FRAME(18, 5), ANIM_FRAME(19, 5),
    ANIM_FRAME(16, 5), ANIM_FRAME(17, 5), ANIM_FRAME(18, 5), ANIM_FRAME(19, 5),
    ANIM_FRAME(16, 5), ANIM_FRAME(17, 5), ANIM_FRAME(18, 5), ANIM_FRAME(19, 5),
    ANIM_FRAME(20, 5), ANIM_FRAME(21, 5), ANIM_FRAME(22, 5), ANIM_FRAME(23, 5),
    ANIM_JUMP(0),
};

// Button prompt animations, 18 bytes each; the Folio Universitas screen shows the first two.
const u8 g_aFolioButtonPromptAnims[4][18] = {
    {
        ANIM_FRAME(2, 7), ANIM_FRAME(1, 7), ANIM_FRAME(0, 30),
        ANIM_JUMP(0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
        ANIM_FRAME(0, 0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
    },
    {
        ANIM_FRAME(17, 7), ANIM_FRAME(16, 7), ANIM_FRAME(15, 30),
        ANIM_JUMP(0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
        ANIM_FRAME(0, 0), ANIM_FRAME(0, 0), ANIM_FRAME(0, 0),
    },
    {
        ANIM_FRAME(30, 2), ANIM_FRAME(31, 2), ANIM_FRAME(32, 2),
        ANIM_FRAME(33, 2), ANIM_FRAME(34, 2), ANIM_FRAME(35, 2),
        ANIM_FRAME(36, 2), ANIM_FRAME(9, 30), ANIM_JUMP(0),
    },
    {
        ANIM_FRAME(23, 2), ANIM_FRAME(24, 2), ANIM_FRAME(25, 2),
        ANIM_FRAME(26, 2), ANIM_FRAME(27, 2), ANIM_FRAME(28, 2),
        ANIM_FRAME(29, 2), ANIM_FRAME(6, 30), ANIM_JUMP(0),
    },
};
