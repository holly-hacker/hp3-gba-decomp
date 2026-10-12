#include "types.h"
#include "actor_anim.h"
#include "combat_result.h"

// Frames 0-27 for 1 tick each, then frame 28 for 120 ticks, looping.
const u8 g_abCombatResultLevelUpSparkleAnim[] = {
    ANIM_FRAME(0, 1),  ANIM_FRAME(1, 1),  ANIM_FRAME(2, 1),  ANIM_FRAME(3, 1),
    ANIM_FRAME(4, 1),  ANIM_FRAME(5, 1),  ANIM_FRAME(6, 1),  ANIM_FRAME(7, 1),
    ANIM_FRAME(8, 1),  ANIM_FRAME(9, 1),  ANIM_FRAME(10, 1), ANIM_FRAME(11, 1),
    ANIM_FRAME(12, 1), ANIM_FRAME(13, 1), ANIM_FRAME(14, 1), ANIM_FRAME(15, 1),
    ANIM_FRAME(16, 1), ANIM_FRAME(17, 1), ANIM_FRAME(18, 1), ANIM_FRAME(19, 1),
    ANIM_FRAME(20, 1), ANIM_FRAME(21, 1), ANIM_FRAME(22, 1), ANIM_FRAME(23, 1),
    ANIM_FRAME(24, 1), ANIM_FRAME(25, 1), ANIM_FRAME(26, 1), ANIM_FRAME(27, 1),
    ANIM_FRAME(28, 120),
    ANIM_JUMP(0),
};

// Text macro 1 for the XP line, which is printed without a unit.
const u8 g_sCombatResultMacro1Space[] = " ";
