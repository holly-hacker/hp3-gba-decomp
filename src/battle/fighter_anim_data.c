#include "types.h"
#include "graphics/object_anim.h"
#include "battle/battle.h"

// Each party fighter's animation per animation state, paired with the
// sprites in g_aFighterAnimTable; see SetPlayerObjectAnim.
const u8 g_aFighterAnimDataTable[4][10][58] = {
    {  // Harry
        {  // 0
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
            ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        },
        {  // 1
            ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_EVENT(0), ANIM_FRAME(2, 2),
            ANIM_FRAME(3, 3), ANIM_FRAME(4, 2), ANIM_FRAME(5, 3), ANIM_FRAME(6, 9),
            ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_END,
        },
        {  // 2
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 4),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 2), ANIM_FRAME(6, 2), ANIM_FRAME(7, 2),
            ANIM_SOUND(130), ANIM_FRAME(8, 2), ANIM_FRAME(9, 1), ANIM_FRAME(10, 2),
            ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 2),
            ANIM_SOUND(31), ANIM_END,
        },
        {  // 3
            ANIM_FRAME(0, 1), ANIM_SOUND(26), ANIM_FRAME(0, 3), ANIM_FRAME(1, 3),
            ANIM_END,
        },
        {  // 4
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_END,
        },
        {  // 5
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_END,
        },
        {  // 6
            ANIM_FRAME(0, 0), ANIM_END,
        },
        {  // 7
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(1, 4),
            ANIM_JUMP(0),
        },
        {  // 8
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 2), ANIM_FRAME(3, 4),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 2),
            ANIM_FRAME(8, 3), ANIM_END,
        },
        {  // 9
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 6),
            ANIM_FRAME(4, 4), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_JUMP(3),
        },
    },
    {  // Hermione
        {  // 0
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
            ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        },
        {  // 1
            ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_EVENT(0), ANIM_FRAME(2, 2),
            ANIM_FRAME(3, 3), ANIM_FRAME(4, 2), ANIM_FRAME(5, 3), ANIM_FRAME(6, 9),
            ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_END,
        },
        {  // 2
            ANIM_FRAME(0, 1), ANIM_FRAME(1, 3), ANIM_FRAME(2, 1), ANIM_FRAME(3, 2),
            ANIM_FRAME(4, 9), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3),
            ANIM_FRAME(11, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
            ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(5, 3), ANIM_FRAME(4, 6),
            ANIM_FRAME(12, 2), ANIM_FRAME(13, 2), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
            ANIM_END,
        },
        {  // 3
            ANIM_FRAME(0, 1), ANIM_SOUND(26), ANIM_FRAME(0, 3), ANIM_FRAME(1, 3),
            ANIM_END,
        },
        {  // 4
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_END,
        },
        {  // 5
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_END,
        },
        {  // 6
            ANIM_FRAME(0, 0), ANIM_END,
        },
        {  // 7
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(1, 4),
            ANIM_JUMP(0),
        },
        {  // 8
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 2), ANIM_FRAME(3, 4),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 2),
            ANIM_FRAME(8, 3), ANIM_END,
        },
        {  // 9
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 6),
            ANIM_FRAME(4, 4), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_JUMP(3),
        },
    },
    {  // Ron
        {  // 0
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
            ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        },
        {  // 1
            ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_EVENT(0), ANIM_FRAME(2, 2),
            ANIM_FRAME(3, 3), ANIM_FRAME(4, 2), ANIM_FRAME(5, 3), ANIM_FRAME(6, 9),
            ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_END,
        },
        {  // 2
            ANIM_FRAME(0, 2), ANIM_FRAME(1, 2), ANIM_FRAME(2, 2), ANIM_FRAME(3, 4),
            ANIM_FRAME(4, 2), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 2),
            ANIM_EVENT(0), ANIM_FRAME(7, 2), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
            ANIM_END,
        },
        {  // 3
            ANIM_FRAME(0, 1), ANIM_SOUND(26), ANIM_FRAME(0, 3), ANIM_FRAME(1, 3),
            ANIM_END,
        },
        {  // 4
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_END,
        },
        {  // 5
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_END,
        },
        {  // 6
            ANIM_FRAME(0, 0), ANIM_END,
        },
        {  // 7
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(1, 4),
            ANIM_JUMP(0),
        },
        {  // 8
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 2), ANIM_FRAME(3, 4),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 2),
            ANIM_FRAME(8, 3), ANIM_END,
        },
        {  // 9
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 6),
            ANIM_FRAME(4, 2), ANIM_FRAME(5, 3), ANIM_FRAME(6, 4), ANIM_FRAME(7, 2),
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(3, 6), ANIM_JUMP(3),
        },
    },
    {  // Buckbeak
        {  // 0
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
            ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        },
        {  // 1
            ANIM_FRAME(0, 1), ANIM_SOUND(57), ANIM_FRAME(0, 1), ANIM_FRAME(1, 5),
            ANIM_FRAME(2, 1), ANIM_FRAME(3, 2), ANIM_FRAME(4, 1), ANIM_FRAME(5, 4),
            ANIM_FRAME(6, 5), ANIM_FRAME(7, 1), ANIM_EVENT(0), ANIM_FRAME(8, 1),
            ANIM_END,
        },
        {  // 2
            ANIM_FRAME(0, 2), ANIM_FRAME(1, 5), ANIM_FRAME(2, 1), ANIM_FRAME(3, 2),
            ANIM_FRAME(4, 1), ANIM_FRAME(5, 4), ANIM_FRAME(6, 5), ANIM_FRAME(7, 1),
            ANIM_EVENT(0), ANIM_FRAME(8, 1), ANIM_END,
        },
        {  // 3
            ANIM_FRAME(0, 1), ANIM_SOUND(26), ANIM_FRAME(0, 3), ANIM_FRAME(1, 3),
            ANIM_END,
        },
        {  // 4
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 3), ANIM_FRAME(2, 2), ANIM_FRAME(3, 3),
            ANIM_END,
        },
        {  // 5
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 3), ANIM_FRAME(2, 2), ANIM_FRAME(3, 3),
            ANIM_END,
        },
        {  // 6
            ANIM_FRAME(0, 0), ANIM_END,
        },
        {  // 7
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(1, 4),
            ANIM_JUMP(0),
        },
        {  // 8
            ANIM_FRAME(0, 4), ANIM_FRAME(1, 3), ANIM_FRAME(2, 1), ANIM_FRAME(3, 4),
            ANIM_FRAME(4, 2), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_END,
        },
        {  // 9
            ANIM_FRAME(0, 3), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 6),
            ANIM_FRAME(4, 2), ANIM_FRAME(5, 3), ANIM_FRAME(6, 4), ANIM_FRAME(7, 2),
            ANIM_FRAME(8, 3), ANIM_FRAME(9, 3), ANIM_FRAME(10, 3), ANIM_FRAME(11, 3),
            ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(3, 6), ANIM_JUMP(3),
        },
    },
};
