#include "types.h"
#include "actor.h"
#include "actor_anim.h"
#include "cheat.h"
#include "gen/graphics/menus.h"

const u32 g_dwCheatBg0Control = 0x1E02;
const u32 g_dwCheatBg1Control = 0x1F09;

const ActorAssetRecord g_CheatAnimFrames = {
    (void *)gDebugMenuCursorTiles, (void *)gDebugMenuCursorFrames, (void *)gDebugMenuCursorPalette, 1,
};

// The cursor's sparkle loop.
const u8 g_CheatAnimData[] = {
    ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
    ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
    ANIM_JUMP(0),
};
