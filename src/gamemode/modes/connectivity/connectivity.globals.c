#include "types.h"
#include "menu/connectivity.h"
#include "gen/graphics/overworld.h"

const ListMenuEntry g_aConnectivityGameCubeEntries[2] = {
    { ConfirmTradeScreen, 0x538, 0, 0 },  // "Trade Cards"
    { GameCubeLink,       0x539, 0, 0 },  // "Owl Care Kit"
};

const ListMenuEntry g_aConnectivityOwlNameEntries[2] = {
    { ConfirmTradeScreen, 0x538, 0, 0 },  // "Trade Cards"
    { OwlNameSelect,      0x539, 0, 0 },  // "Owl Care Kit"
};

const ListMenuEntry g_aConnectivityOwlCareEntries[2] = {
    { ConfirmTradeScreen, 0x538, 0, 0 },  // "Trade Cards"
    { OwlCareMinigame,    0x539, 0, 1 },  // "Owl Care Kit"
};

const ListMenuRowObject g_aConnectivityRowObjects[2] = {
    { (void *)gInGameMenuIconConnectivityTiles, (void *)gInGameMenuIconConnectivityFrames, (const ObjPalette *)gInGameMenuIconConnectivityPalette, 0 },
    { (void *)gInGameMenuIconConnectivityTiles, (void *)gInGameMenuIconConnectivityFrames, (const ObjPalette *)gInGameMenuIconConnectivityPalette, 0 },
};

const ListMenuDefinition g_ConnectivityMenuTemplate = {
    0x534,  // title: "Connectivity"
    ARRAY_COUNT(g_aConnectivityGameCubeEntries),
    4,
    0,
    72, 26,
    0, 16,
    g_aConnectivityGameCubeEntries,
    ARRAY_COUNT(g_aConnectivityRowObjects),
    0,
    -32, 0,
    g_aConnectivityRowObjects,
    -50, 8,
};

const ListMenuDefinition g_ConfirmTradeMenuDefinition = {
    0x8CD,  // title: "New Game"
    2,
    2,
    0,
    112, 80,
    0, 12,
    g_aConfirmTradeEntries,
    0,
    0,
    0, 0,
    0,
    -16, 3,
};
