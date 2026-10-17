#include "types.h"
#include "pscreen_folio.h"
#include "gen/graphics/overworld.h"

const ListMenuEntry g_aFoliosEntries[2] = {
    { FolioUniversitas, 0x40D, 1 },  // "Folio Universitas"
    { FolioBruti,       0x8F4, 1 },  // "Folio Bruti"
};

const ListMenuRowActor g_aFoliosRowActors[2] = {
    { (void *)gInGameMenuIconFoliosTiles, (void *)gInGameMenuIconFoliosFrames, (const ObjPalette *)gInGameMenuIconFoliosPalette, 0 },
    { (void *)gInGameMenuIconFoliosTiles, (void *)gInGameMenuIconFoliosFrames, (const ObjPalette *)gInGameMenuIconFoliosPalette, 0 },
};

const ListMenuDefinition g_FoliosMenuDefinition = {
    0x532,  // title: "Folios"
    ARRAY_COUNT(g_aFoliosEntries),
    4,
    { 72, 26 },
    { 0, 16 },
    g_aFoliosEntries,
    ARRAY_COUNT(g_aFoliosRowActors),
    { -32, 0 },
    g_aFoliosRowActors,
    { -48, 8 },
};
