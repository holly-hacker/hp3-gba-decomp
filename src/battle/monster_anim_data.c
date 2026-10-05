#include "types.h"
#include "graphics/object_anim.h"
#include "battle/battle.h"

// Each monster's battle animation, played with its g_pMonsterGraphicsTable
// battle sprite.
const u8 g_pMonsterAnimFrameTable[69][96] = {
    {  // 0: Ruby Fire Crab
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 4), ANIM_FRAME(7, 4), ANIM_FRAME(8, 4), ANIM_FRAME(9, 4),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 5), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 4), ANIM_FRAME(15, 4), ANIM_FRAME(16, 4), ANIM_FRAME(17, 2),
        ANIM_EVENT(0), ANIM_FRAME(17, 9), ANIM_FRAME(16, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(14, 3), ANIM_FRAME(13, 3), ANIM_FRAME(12, 3), ANIM_FRAME(11, 3),
        ANIM_FRAME(10, 3), ANIM_END,
    },
    {  // 1: Emerald Fire Crab
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 4), ANIM_FRAME(7, 4), ANIM_FRAME(8, 4), ANIM_FRAME(9, 4),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 5), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 4), ANIM_FRAME(15, 4), ANIM_FRAME(16, 4), ANIM_FRAME(17, 2),
        ANIM_EVENT(0), ANIM_FRAME(17, 9), ANIM_FRAME(16, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(14, 3), ANIM_FRAME(13, 3), ANIM_FRAME(12, 3), ANIM_FRAME(11, 3),
        ANIM_FRAME(10, 3), ANIM_END,
    },
    {  // 2: Sapphire Fire Crab
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 4), ANIM_FRAME(7, 4), ANIM_FRAME(8, 4), ANIM_FRAME(9, 4),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 5), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 4), ANIM_FRAME(15, 4), ANIM_FRAME(16, 4), ANIM_FRAME(17, 2),
        ANIM_EVENT(0), ANIM_FRAME(17, 9), ANIM_FRAME(16, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(14, 3), ANIM_FRAME(13, 3), ANIM_FRAME(12, 3), ANIM_FRAME(11, 3),
        ANIM_FRAME(10, 3), ANIM_END,
    },
    {  // 3: Cornish Pixie
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_EVENT(255), ANIM_END_ARG(255),
    },
    {  // 4: Rat
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 5: Albino Rat
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 6: Plague Rat
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 7: Clabbert
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 8), ANIM_FRAME(8, 4), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 3),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 4), ANIM_FRAME(16, 2), ANIM_FRAME(17, 4),
        ANIM_FRAME(18, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 8: Suit of Armor (Footman)
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 9: Suit of Armor (Cavalier)
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 10: Suit of Armor (Paladin)
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 11: Suit of Armor (Squire)
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 12: Suit of Armor (Swordsman)
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 13: Suit of Armor (Crusader)
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 14: Suit of Armor (Knight)
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 4), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 15: Funnelweb Spider
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 16: Brown Recluse Spider
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 17: Large Spider
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 18: Redback Spider
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 19: Giant Spider
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 5), ANIM_FRAME(8, 2), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 20: Cocoon Spider
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 5), ANIM_FRAME(8, 2), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 21: Whitetail Spider
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 5), ANIM_FRAME(8, 2), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 22: Flobberworm
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 2), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 5), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 4), ANIM_EVENT(0), ANIM_FRAME(14, 4), ANIM_FRAME(15, 2),
        ANIM_FRAME(16, 2), ANIM_END,
    },
    {  // 23: Snail
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 2), ANIM_FRAME(8, 5), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 5), ANIM_FRAME(12, 2), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 1), ANIM_FRAME(16, 2), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 24: Large Orange Snail
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 2), ANIM_FRAME(8, 5), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 5), ANIM_FRAME(12, 2), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 1), ANIM_FRAME(16, 2), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 25: Flailtail Snail
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 2), ANIM_FRAME(8, 5), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 5), ANIM_FRAME(12, 2), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 1), ANIM_FRAME(16, 2), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 26: Bat
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 3), ANIM_FRAME(13, 1),
        ANIM_EVENT(0), ANIM_FRAME(13, 10), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(16, 3), ANIM_END,
    },
    {  // 27: Fruitbat
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 3), ANIM_FRAME(13, 1),
        ANIM_EVENT(0), ANIM_FRAME(13, 10), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(16, 3), ANIM_END,
    },
    {  // 28: Mortis Bat
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 3), ANIM_FRAME(13, 1),
        ANIM_EVENT(0), ANIM_FRAME(13, 10), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(16, 3), ANIM_END,
    },
    {  // 29: Dragonfly
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 5), ANIM_FRAME(8, 1), ANIM_FRAME(9, 2),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_EVENT(255), ANIM_END_ARG(255),
    },
    {  // 30: Imperial Dragonfly
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 5), ANIM_FRAME(8, 1), ANIM_FRAME(9, 2),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_EVENT(255), ANIM_END_ARG(255),
    },
    {  // 31: Horklump
        // 0
        ANIM_FRAME(0, 5), ANIM_FRAME(1, 5), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 5), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 2), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 4), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 3), ANIM_FRAME(21, 3),
        ANIM_FRAME(22, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 32: Snake
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 6), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 4), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 4), ANIM_FRAME(15, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 33: Spitting Snake
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 6), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 4), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 4), ANIM_FRAME(15, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 34: Wasp
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 3), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 6), ANIM_FRAME(15, 4), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 35: Tarantula Hawk Wasp
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 3), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 6), ANIM_FRAME(15, 4), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 36: Bowtruckle
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 4), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 5), ANIM_FRAME(11, 1), ANIM_FRAME(12, 1), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 5), ANIM_FRAME(15, 1), ANIM_FRAME(16, 2), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 3), ANIM_FRAME(20, 4), ANIM_FRAME(21, 3),
        ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 37: Oaken Bowtruckle
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 4), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 5), ANIM_FRAME(11, 1), ANIM_FRAME(12, 1), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 5), ANIM_FRAME(15, 1), ANIM_FRAME(16, 2), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 3), ANIM_FRAME(20, 4), ANIM_FRAME(21, 3),
        ANIM_FRAME(22, 3), ANIM_FRAME(23, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 38: Doxy
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 1), ANIM_FRAME(16, 1), ANIM_FRAME(17, 1),
        ANIM_FRAME(18, 4), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 39: Doxy Queen
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 1), ANIM_FRAME(16, 1), ANIM_FRAME(17, 1),
        ANIM_FRAME(18, 4), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 40: Hinkypunk
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 6), ANIM_FRAME(8, 4), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 2),
        ANIM_EVENT(255), ANIM_FRAME(13, 2), ANIM_FRAME(14, 4), ANIM_FRAME(15, 6),
        ANIM_FRAME(16, 3), ANIM_END_ARG(255),
    },
    {  // 41: Gytrash
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 4),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 4), ANIM_FRAME(12, 3), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 5), ANIM_FRAME(15, 2), ANIM_FRAME(16, 5), ANIM_FRAME(17, 5),
        ANIM_FRAME(18, 4), ANIM_FRAME(19, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 42: Grindylow
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 6), ANIM_FRAME(8, 2), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 3), ANIM_FRAME(12, 5), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 5), ANIM_FRAME(16, 2), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 4), ANIM_EVENT(0), ANIM_END,
    },
    {  // 43: Red Cap
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 6), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 1), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 5), ANIM_FRAME(19, 6), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 44: Armored Red Cap
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 6), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 4), ANIM_FRAME(12, 1), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 5), ANIM_FRAME(19, 6), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 45: Salamander
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 3), ANIM_FRAME(8, 2), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 3), ANIM_FRAME(12, 4), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 2), ANIM_EVENT(0), ANIM_FRAME(14, 2), ANIM_FRAME(15, 1),
        ANIM_FRAME(16, 2), ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4),
        ANIM_FRAME(3, 4), ANIM_FRAME(4, 4), ANIM_END,
    },
    {  // 46: Amazonian Salamander
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 3), ANIM_FRAME(8, 2), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 3), ANIM_FRAME(12, 4), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 2), ANIM_EVENT(0), ANIM_FRAME(14, 2), ANIM_FRAME(15, 1),
        ANIM_FRAME(16, 2), ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4),
        ANIM_FRAME(3, 4), ANIM_FRAME(4, 4), ANIM_END,
    },
    {  // 47: Peruvian Salamander
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 3), ANIM_FRAME(8, 2), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 3), ANIM_FRAME(12, 4), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 2), ANIM_EVENT(0), ANIM_FRAME(14, 2), ANIM_FRAME(15, 1),
        ANIM_FRAME(16, 2), ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4),
        ANIM_FRAME(3, 4), ANIM_FRAME(4, 4), ANIM_END,
    },
    {  // 48: Charmed Skeleton
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 6), ANIM_FRAME(8, 3), ANIM_FRAME(9, 2),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 4), ANIM_FRAME(11, 3), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_EVENT(255), ANIM_FRAME(13, 1), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2),
        ANIM_FRAME(16, 2), ANIM_FRAME(17, 24), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2),
        ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_END_ARG(255),
    },
    {  // 49: Jinxed Skeleton
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 6), ANIM_FRAME(8, 3), ANIM_FRAME(9, 2),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 4), ANIM_FRAME(11, 3), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_EVENT(255), ANIM_FRAME(13, 1), ANIM_FRAME(14, 2), ANIM_FRAME(15, 2),
        ANIM_FRAME(16, 2), ANIM_FRAME(17, 24), ANIM_FRAME(18, 2), ANIM_FRAME(19, 2),
        ANIM_FRAME(20, 3), ANIM_FRAME(21, 3), ANIM_END_ARG(255),
    },
    {  // 50: Tree Frog
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 2),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 51: Wide-mouth Toad
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 2),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 52: Bullfrog
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 2), ANIM_FRAME(13, 2),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_FRAME(16, 2), ANIM_FRAME(17, 2),
        ANIM_FRAME(18, 2), ANIM_FRAME(19, 2), ANIM_FRAME(20, 2), ANIM_FRAME(21, 2),
        ANIM_EVENT(0), ANIM_END,
    },
    {  // 53: Flesh-eating Slug (not in game, needs to be in file for coders - no need to translate)
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 2), ANIM_FRAME(8, 5), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 5), ANIM_FRAME(12, 2), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 1), ANIM_FRAME(16, 2), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 54: Whomping Willow
        // 0
        ANIM_FRAME(0, 9), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(3, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(4, 6), ANIM_FRAME(3, 3), ANIM_FRAME(2, 3), ANIM_FRAME(1, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 6),
        ANIM_FRAME(4, 8), ANIM_EVENT(255), ANIM_FRAME(4, 8), ANIM_FRAME(2, 3),
        ANIM_FRAME(1, 3), ANIM_FRAME(0, 3), ANIM_END_ARG(255),
    },
    {  // 55: Forest Troll
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 2), ANIM_FRAME(8, 6), ANIM_FRAME(9, 1),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 5), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 4), ANIM_FRAME(17, 4),
        ANIM_FRAME(18, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 56: River Troll
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 1), ANIM_FRAME(7, 2), ANIM_FRAME(8, 6), ANIM_FRAME(9, 1),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 2), ANIM_FRAME(12, 5), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 4), ANIM_FRAME(17, 4),
        ANIM_FRAME(18, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 57: Venemous Tentacula
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 3), ANIM_FRAME(13, 3),
        ANIM_FRAME(14, 12), ANIM_EVENT(0), ANIM_END,
    },
    {  // 58: 'The Monster Book of Monsters'
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_MOVE_DOWN_RIGHT(3), ANIM_FRAME(11, 3), ANIM_MOVE_DOWN_RIGHT(3),
        ANIM_FRAME(12, 3), ANIM_MOVE_DOWN_RIGHT(3), ANIM_FRAME(13, 3), ANIM_MOVE_DOWN_RIGHT(3),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_EVENT(0), ANIM_FRAME(0, 4),
        ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(1, 2), ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(2, 3),
        ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(3, 3), ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(4, 3),
        ANIM_FRAME(5, 3), ANIM_END,
    },
    {  // 59: Giant Rat
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 5), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 3), ANIM_FRAME(13, 4),
        ANIM_FRAME(14, 3), ANIM_FRAME(15, 3), ANIM_FRAME(16, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 60: Crabbe
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 6), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 5), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 3), ANIM_EVENT(255), ANIM_FRAME(15, 4), ANIM_FRAME(16, 1),
        ANIM_END_ARG(255),
    },
    {  // 61: Draco
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 6), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 2), ANIM_FRAME(11, 3), ANIM_FRAME(12, 5), ANIM_EVENT(255),
        ANIM_FRAME(13, 6), ANIM_FRAME(14, 3), ANIM_END_ARG(255),
    },
    {  // 62: Goyle
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
        ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 6), ANIM_FRAME(7, 4), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 3), ANIM_FRAME(12, 5), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 3), ANIM_EVENT(255), ANIM_FRAME(15, 4), ANIM_FRAME(16, 1),
        ANIM_END_ARG(255),
    },
    {  // 63: Lupin Werewolf
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 1), ANIM_SOUND(53), ANIM_FRAME(10, 2), ANIM_FRAME(11, 3),
        ANIM_FRAME(12, 3), ANIM_FRAME(13, 3), ANIM_FRAME(14, 3), ANIM_FRAME(15, 3),
        ANIM_FRAME(16, 3), ANIM_FRAME(17, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 64: Snake
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 6), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 4), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 4), ANIM_FRAME(15, 3), ANIM_EVENT(0), ANIM_END,
    },
    {  // 65: Brown Recluse Spider
        // 0
        ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 2), ANIM_FRAME(7, 5), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_FRAME(11, 5), ANIM_FRAME(12, 1), ANIM_FRAME(13, 1),
        ANIM_FRAME(14, 1), ANIM_FRAME(15, 2), ANIM_FRAME(16, 3), ANIM_FRAME(17, 3),
        ANIM_FRAME(18, 3), ANIM_FRAME(19, 3), ANIM_FRAME(20, 3), ANIM_EVENT(0),
        ANIM_END,
    },
    {  // 66: 'The Monster Book of Monsters'
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_MOVE_DOWN_RIGHT(3), ANIM_FRAME(11, 3), ANIM_MOVE_DOWN_RIGHT(3),
        ANIM_FRAME(12, 3), ANIM_MOVE_DOWN_RIGHT(3), ANIM_FRAME(13, 3), ANIM_MOVE_DOWN_RIGHT(3),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_EVENT(0), ANIM_FRAME(0, 4),
        ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(1, 2), ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(2, 3),
        ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(3, 3), ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(4, 3),
        ANIM_FRAME(5, 3), ANIM_END,
    },
    {  // 67: 'The Monster Book of Monsters'
        // 0
        ANIM_FRAME(0, 4), ANIM_FRAME(1, 2), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
        ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_JUMP(0),
        // 7
        ANIM_FRAME(6, 3), ANIM_FRAME(7, 3), ANIM_FRAME(8, 3), ANIM_FRAME(9, 3),
        ANIM_END,
        // 12
        ANIM_FRAME(10, 3), ANIM_MOVE_DOWN_RIGHT(3), ANIM_FRAME(11, 3), ANIM_MOVE_DOWN_RIGHT(3),
        ANIM_FRAME(12, 3), ANIM_MOVE_DOWN_RIGHT(3), ANIM_FRAME(13, 3), ANIM_MOVE_DOWN_RIGHT(3),
        ANIM_FRAME(14, 2), ANIM_FRAME(15, 2), ANIM_EVENT(0), ANIM_FRAME(0, 4),
        ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(1, 2), ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(2, 3),
        ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(3, 3), ANIM_MOVE_UP_LEFT(3), ANIM_FRAME(4, 3),
        ANIM_FRAME(5, 3), ANIM_END,
    },
    { 0 },  // 68: Native of Fiji. Has a heavily jeweled shell.
};

// The battle shadow's animation, played with g_MonsterShadowGfxRow.
const u8 g_MonsterShadowAnimData[96] = {
    // 0
    ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4), ANIM_FRAME(3, 4),
    ANIM_FRAME(4, 4), ANIM_FRAME(5, 4), ANIM_JUMP(0),
    // 7
    ANIM_FRAME(6, 1), ANIM_FRAME(7, 3), ANIM_FRAME(8, 2), ANIM_FRAME(9, 3),
    ANIM_END,
    // 12
    ANIM_FRAME(10, 2), ANIM_FRAME(11, 3), ANIM_FRAME(12, 4), ANIM_FRAME(13, 1),
    ANIM_FRAME(14, 2), ANIM_EVENT(0), ANIM_FRAME(14, 2), ANIM_FRAME(15, 1),
    ANIM_FRAME(16, 2), ANIM_FRAME(0, 4), ANIM_FRAME(1, 4), ANIM_FRAME(2, 4),
    ANIM_FRAME(3, 4), ANIM_FRAME(4, 4), ANIM_END,
};
