#include "types.h"
#include "menu/in_game_menu.h"
#include "gen/graphics/menus.h"
#include "gen/graphics/overworld.h"

// The pause menu's rows.
const ListMenuEntry g_aInGameMenuEntries[6] = {
    { StatusEquipCharacterSelect, 0x530, 0, 0 },
    { ItemsSectionSelect,         0x531, 0, 0 },
    { Folios,                     0x532, 0, 0 },
    { GameSave,                   0x533, 0, 1 },
    { Connectivity,               0x534, 0, 0 },
    { Help,                       0x535, 0, 0 },
};

// One icon per row.
const ListMenuRowObject g_aInGameMenuRowObjects[6] = {
    { (void *)gObjectSprite019Tiles, (void *)gObjectSprite019Frames, (const ObjPalette *)gObjectSprite019Palette, 0 },
    { (void *)gMenuSprite004Tiles,   (void *)gMenuSprite004Frames,   (const ObjPalette *)gMenuSprite004Palette,   0 },
    { (void *)gObjectSprite020Tiles, (void *)gObjectSprite020Frames, (const ObjPalette *)gObjectSprite020Palette, 0 },
    { (void *)gObjectSprite021Tiles, (void *)gObjectSprite021Frames, (const ObjPalette *)gObjectSprite021Palette, 0 },
    { (void *)gObjectSprite022Tiles, (void *)gObjectSprite022Frames, (const ObjPalette *)gObjectSprite022Palette, 0 },
    { (void *)gObjectSprite023Tiles, (void *)gObjectSprite023Frames, (const ObjPalette *)gObjectSprite023Palette, 0 },
};

const ListMenuDefinition g_InGameMenuDefinition = {
    0x537,
    ARRAY_COUNT(g_aInGameMenuEntries),
    4,
    0,
    72, 26,
    0, 16,
    g_aInGameMenuEntries,
    ARRAY_COUNT(g_aInGameMenuRowObjects),
    0,
    -32, 0,
    g_aInGameMenuRowObjects,
    -48, 8,
};
