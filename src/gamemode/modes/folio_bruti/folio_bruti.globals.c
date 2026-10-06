#include "types.h"
#include "graphics/object.h"
#include "menu/folio_bruti.h"
#include "gen/graphics/overworld.h"

const u32 g_dwFolioBrutiBg3Control = 0x3F03;
const u32 g_dwFolioBrutiBg2Control = 0x3E03;
const u32 g_dwFolioBrutiBg1Control = 0x3D08;

// An all-black object palette, for a monster that has not been seen yet.
const u16 g_aFolioBrutiBlankObjPalette[16] = { 0 };

const ObjectGfxRecord g_aFolioBrutiObjectGfx[2] = {
    { (void *)gFolioBrutiCursorTiles, (void *)gFolioBrutiCursorFrames },
    { (void *)gFolioBrutiSpellDotTiles, (void *)gFolioBrutiSpellDotFrames },
};
