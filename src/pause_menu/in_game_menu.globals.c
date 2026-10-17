#include "types.h"
#include "pause_menu.h"
#include "gen/graphics/menus.h"
#include "gen/graphics/overworld.h"

// The pause menu's rows.
const ListMenuEntry g_aInGameMenuEntries[6] = {
    { StatusEquipCharacterSelect, 0x530, 0 },  // "Status/Equip"
    { ItemsSectionSelect,         0x531, 0 },  // "Items"
    { Folios,                     0x532, 0 },  // "Folios"
    { GameSave,                   0x533, 1 },  // "Save Game"
    { Connectivity,               0x534, 0 },  // "Connectivity"
    { Help,                       0x535, 0 },  // "Help"
};

// One icon per row.
const ListMenuRowActor g_aInGameMenuRowActors[6] = {
    { (void *)gInGameMenuIconStatusEquipTiles, (void *)gInGameMenuIconStatusEquipFrames, (const ObjPalette *)gInGameMenuIconStatusEquipPalette, 0 },
    { (void *)gInGameMenuIconItemsTiles,   (void *)gInGameMenuIconItemsFrames,   (const ObjPalette *)gInGameMenuIconItemsPalette,   0 },
    { (void *)gInGameMenuIconFoliosTiles, (void *)gInGameMenuIconFoliosFrames, (const ObjPalette *)gInGameMenuIconFoliosPalette, 0 },
    { (void *)gInGameMenuIconSaveTiles, (void *)gInGameMenuIconSaveFrames, (const ObjPalette *)gInGameMenuIconSavePalette, 0 },
    { (void *)gInGameMenuIconConnectivityTiles, (void *)gInGameMenuIconConnectivityFrames, (const ObjPalette *)gInGameMenuIconConnectivityPalette, 0 },
    { (void *)gInGameMenuIconHelpTiles, (void *)gInGameMenuIconHelpFrames, (const ObjPalette *)gInGameMenuIconHelpPalette, 0 },
};

const ListMenuDefinition g_InGameMenuDefinition = {
    0x537,  // title: "Menu"
    ARRAY_COUNT(g_aInGameMenuEntries),
    4,
    { 72, 26 },
    { 0, 16 },
    g_aInGameMenuEntries,
    ARRAY_COUNT(g_aInGameMenuRowActors),
    { -32, 0 },
    g_aInGameMenuRowActors,
    { -48, 8 },
};
