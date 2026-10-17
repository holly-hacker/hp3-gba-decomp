#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "cheat_level_and_quest.h"
#include "gen/graphics/menus.h"

// Largest value of each row: three character levels, then the quest.
const u8 g_abCheatLevelAndQuestMax[4] = { 99, 99, 99, 26 };

const u32 g_dwCheatLevelAndQuestBg0Control = 0x1E02;
const u32 g_dwCheatLevelAndQuestBg1Control = 0x1F09;

const ActorAssetRecord g_CheatLevelAndQuestAnimFrames = {
    (void *)gDebugMenuCursorTiles, (void *)gDebugMenuCursorFrames, (void *)gDebugMenuCursorPalette, 1,
};

// The cursor's sparkle loop.
const u8 g_CheatLevelAndQuestAnimData[] = {
    ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
    ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
    ANIM_JUMP(0),
};
