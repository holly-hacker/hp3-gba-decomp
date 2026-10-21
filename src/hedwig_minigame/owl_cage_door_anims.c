#include "types.h"
#include "actor_anim.h"

// The four animations of the cage door, selected by SetOwlCageDoorAnim.
const u8 g_abOwlCageDoorAnim0[4] = {
    ANIM_FRAME(0, 0),
};

const u8 g_abOwlCageDoorAnim1[12] = {
    ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3), ANIM_FRAME(4, 3), ANIM_END,
};

const u8 g_abOwlCageDoorAnim2[4] = {
    ANIM_FRAME(4, 0),
};

const u8 g_abOwlCageDoorAnim3[12] = {
    ANIM_FRAME(3, 3), ANIM_FRAME(2, 3), ANIM_FRAME(1, 3), ANIM_FRAME(0, 3), ANIM_END,
};
