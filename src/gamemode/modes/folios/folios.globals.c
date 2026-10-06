#include "types.h"
#include "menu/folios.h"
#include "gen/graphics/overworld.h"

const ListMenuEntry g_aFoliosEntries[2] = {
    { FolioUniversitas, 0x40D, 0, 1 },  // "Folio Universitas"
    { FolioBruti,       0x8F4, 0, 1 },  // "Folio Bruti"
};

const ListMenuRowObject g_aFoliosRowObjects[2] = {
    { (void *)gInGameMenuIconFoliosTiles, (void *)gInGameMenuIconFoliosFrames, (const ObjPalette *)gInGameMenuIconFoliosPalette, 0 },
    { (void *)gInGameMenuIconFoliosTiles, (void *)gInGameMenuIconFoliosFrames, (const ObjPalette *)gInGameMenuIconFoliosPalette, 0 },
};

const ListMenuDefinition g_FoliosMenuDefinition = {
    0x532,  // title: "Folios"
    ARRAY_COUNT(g_aFoliosEntries),
    4,
    0,
    72, 26,
    0, 16,
    g_aFoliosEntries,
    ARRAY_COUNT(g_aFoliosRowObjects),
    0,
    -32, 0,
    g_aFoliosRowObjects,
    -48, 8,
};
