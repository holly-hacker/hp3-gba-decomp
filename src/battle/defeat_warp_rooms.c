#include "battle/battle.h"

// Room id the overworld warps to after a battle defeat, indexed by
// g_abQuestEventState[QUEST_DEFEAT_WARP_SELECTOR] (set by the
// SetDefeatWarpSelector room-script opcode). Read by CheckBattleDefeat.
const u32 g_aDefeatWarpRoomId[20] = {
    0x29,  // 0: Leaky Cauldron - Harry's Room
    0x06,  // 1: Hogwarts Express - Passenger Car
    0x21,  // 2: Hospital Wing
    0x04,  // 3: Transfiguration Classroom Maze
    0x02,  // 4: Potions Classroom Maze
    0x0C,  // 5: Hagrid's Garden Maze
    0x19,  // 6: Rooftop
    0x2C,  // 7: Shrieking Shack Path
    0x0F,  // 8: Hogwarts Grounds - Whomping Willow
    0x2B,  // 9: Shrieking Shack - Interior
    0x2D,  // 10: Shrieking Shack - Path 2
    0x2E,  // 11: Shrieking Shack - Path 3
    0x2F,  // 12: Shrieking Shack - Path 4
    0x30,  // 13: Shrieking Shack - Path 5
    0x31,  // 14: Shrieking Shack - Path 6
    0x27,  // 15: Leaky Cauldron - Cellar 2
    0x26,  // 16: Leaky Cauldron - Cellar 1
    0x0E,  // 17: Path to Hagrid's Hut
    0x05,  // 18: Hogwarts Express - Baggage Car
    0x19,  // 19: Rooftop
};
