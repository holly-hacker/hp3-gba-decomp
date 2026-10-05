#include "types.h"
#include "menu/options.h"
#include "gen/graphics/menus.h"
#include "gen/graphics/overworld.h"
#ifndef VERSION_JP
#include "gen/graphics/menus/us.h"
#endif

// The left column's option icons, then two objects each on the music and
// sound volume rows (x 170).
const OptionsMenuItem g_aOptionsMenuItems[OPTIONS_MENU_ITEM_COUNT] = {
    { gObjectSprite105Tiles, gObjectSprite105Frames, 0, 0, gObjectSprite105Palette, 46, 40 },
    { gObjectSprite106Tiles, gObjectSprite106Frames, 0, 0, gObjectSprite106Palette, 46, 60 },
    { gObjectSprite107Tiles, gObjectSprite107Frames, 0, 0, gObjectSprite107Palette, 46, 80 },
#ifndef VERSION_JP
    { gOptionIconUs001Tiles, gOptionIconUs001Frames, 0, 0, gOptionIconUs001Palette, 46, 100 },
#endif
    { gObjectSprite2_001Tiles, gObjectSprite2_001Frames, 0, 0, gObjectSprite2_001Palette, 170, 45 },
    { gObjectSprite2_001Tiles, gObjectSprite2_001Frames, 0, 0, gObjectSprite2_001Palette, 170, 65 },
    { gDebugMenuCursorTiles, gDebugMenuCursorFrames, 0, 0, gDebugMenuCursorPalette, 170, 47 },
    { gDebugMenuCursorTiles, gDebugMenuCursorFrames, 0, 0, gDebugMenuCursorPalette, 170, 67 },
};
