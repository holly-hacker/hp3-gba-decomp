#include "title_options.h"
#include "gen/graphics/menus.h"
#include "gen/graphics/overworld.h"
#ifndef VERSION_JP
#include "gen/graphics/menus/us.h"
#endif

// The left column's option icons, then two actors each on the music and
// sound volume rows (x 170).
const OptionsMenuItem g_aOptionsMenuItems[OPTIONS_MENU_ITEM_COUNT] = {
    { { (void *)gOptionsIconSoundTiles, (void *)gOptionsIconSoundFrames, 0, 0 }, gOptionsIconSoundPalette, 46, 40 },
    { { (void *)gOptionsIconMusicTiles, (void *)gOptionsIconMusicFrames, 0, 0 }, gOptionsIconMusicPalette, 46, 60 },
    { { (void *)gOptionsIconBrightnessTiles, (void *)gOptionsIconBrightnessFrames, 0, 0 }, gOptionsIconBrightnessPalette, 46, 80 },
#ifndef VERSION_JP
    { { (void *)gOptionsIconLanguageTiles, (void *)gOptionsIconLanguageFrames, 0, 0 }, gOptionsIconLanguagePalette, 46, 100 },
#endif
    { { (void *)gActorSprite2_001Tiles, (void *)gActorSprite2_001Frames, 0, 0 }, gActorSprite2_001Palette, 170, 45 },
    { { (void *)gActorSprite2_001Tiles, (void *)gActorSprite2_001Frames, 0, 0 }, gActorSprite2_001Palette, 170, 65 },
    { { (void *)gDebugMenuCursorTiles, (void *)gDebugMenuCursorFrames, 0, 0 }, gDebugMenuCursorPalette, 170, 47 },
    { { (void *)gDebugMenuCursorTiles, (void *)gDebugMenuCursorFrames, 0, 0 }, gDebugMenuCursorPalette, 170, 67 },
};
