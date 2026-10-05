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
    { gOptionsIconSoundTiles, gOptionsIconSoundFrames, 0, 0, gOptionsIconSoundPalette, 46, 40 },
    { gOptionsIconMusicTiles, gOptionsIconMusicFrames, 0, 0, gOptionsIconMusicPalette, 46, 60 },
    { gOptionsIconBrightnessTiles, gOptionsIconBrightnessFrames, 0, 0, gOptionsIconBrightnessPalette, 46, 80 },
#ifndef VERSION_JP
    { gOptionsIconLanguageTiles, gOptionsIconLanguageFrames, 0, 0, gOptionsIconLanguagePalette, 46, 100 },
#endif
    { gObjectSprite2_001Tiles, gObjectSprite2_001Frames, 0, 0, gObjectSprite2_001Palette, 170, 45 },
    { gObjectSprite2_001Tiles, gObjectSprite2_001Frames, 0, 0, gObjectSprite2_001Palette, 170, 65 },
    { gDebugMenuCursorTiles, gDebugMenuCursorFrames, 0, 0, gDebugMenuCursorPalette, 170, 47 },
    { gDebugMenuCursorTiles, gDebugMenuCursorFrames, 0, 0, gDebugMenuCursorPalette, 170, 67 },
};
