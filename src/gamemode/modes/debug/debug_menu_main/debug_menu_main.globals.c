#include "types.h"
#include "graphics/object.h"
#include "graphics/object_anim.h"
#include "menu/debug_menu.h"

const u32 g_dwDebugMenuMainBg0Control = 0x1E02;
const u32 g_dwDebugMenuMainBg1Control = 0x1F09;

const ObjectAssetRecord g_DebugMenuMainAnimFrames = {
    (void *)gDebugMenuCursorTiles, (void *)gDebugMenuCursorFrames, (void *)gDebugMenuCursorPalette, 1,
};

// The cursor's sparkle loop.
const u8 g_DebugMenuMainAnimData[] = {
    ANIM_FRAME(0, 3), ANIM_FRAME(1, 3), ANIM_FRAME(2, 3), ANIM_FRAME(3, 3),
    ANIM_FRAME(4, 3), ANIM_FRAME(5, 3), ANIM_FRAME(6, 3), ANIM_FRAME(7, 3),
    ANIM_JUMP(0),
};
