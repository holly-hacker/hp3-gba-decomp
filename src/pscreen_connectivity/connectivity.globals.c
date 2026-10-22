#include "types.h"
#include "pscreen_connectivity.h"
#include "gen/graphics/overworld.h"
#include "pscreen_save.h"

const ListMenuEntry g_aConnectivityGameCubeEntries[2] = {
    { ConfirmTradeScreen, 0x538, 0 },  // "Trade Cards"
    { GameCubeLink,       0x539, 0 },  // "Owl Care Kit"
};

const ListMenuEntry g_aConnectivityOwlNameEntries[2] = {
    { ConfirmTradeScreen, 0x538, 0 },  // "Trade Cards"
    { OwlNameSelect,      0x539, 0 },  // "Owl Care Kit"
};

const ListMenuEntry g_aConnectivityOwlCareEntries[2] = {
    { ConfirmTradeScreen, 0x538, 0 },  // "Trade Cards"
    { OwlCareMinigame,    0x539, 1 },  // "Owl Care Kit"
};

const ActorAssetRecord g_aConnectivityRowActors[2] = {
    { (void *)gInGameMenuIconConnectivityTiles, (void *)gInGameMenuIconConnectivityFrames, (const ObjPalette *)gInGameMenuIconConnectivityPalette, 0 },
    { (void *)gInGameMenuIconConnectivityTiles, (void *)gInGameMenuIconConnectivityFrames, (const ObjPalette *)gInGameMenuIconConnectivityPalette, 0 },
};

const ListMenuDefinition g_ConnectivityMenuTemplate = {
    0x534,  // title: "Connectivity"
    ARRAY_COUNT(g_aConnectivityGameCubeEntries),
    4,
    { 72, 26 },
    { 0, 16 },
    g_aConnectivityGameCubeEntries,
    ARRAY_COUNT(g_aConnectivityRowActors),
    { -32, 0 },
    g_aConnectivityRowActors,
    { -50, 8 },
};

// A copy of g_NewGameSlotConfirmationMenuDefinition, title included.
const ListMenuDefinition g_ConfirmTradeMenuDefinition = {
    // BUG: the trade confirmation screen shows "New Game" as its title; it should
    // be 0x538 ("Trade Cards").
    0x8CD,  // title: "New Game"
    2,
    2,
    { 112, 80 },
    { 0, 12 },
    g_aNoYesEntries,
    0,
    { 0, 0 },
    0,
    { -16, 3 },
};
