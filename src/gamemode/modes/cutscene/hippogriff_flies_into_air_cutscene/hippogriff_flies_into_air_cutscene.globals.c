#include "types.h"
#include "cutscene/hippogriff_flies_into_air_cutscene.h"
#include "gen/graphics/minigames/riddikulus.h"

const u32 g_dwHippogriffFliesIntoAirBg0Control = 0x3D03;

// The hippogriff.
const ObjectAssetRecord g_HippogriffFliesIntoAirAsset = {
    (void *)gHippogriffFliesIntoAirTiles, (void *)gHippogriffFliesIntoAirFrames,
    (void *)gHippogriffFliesIntoAirPalette, 2,
};

const ObjectAssetRecord g_HippogriffFliesIntoAirAsset2 = {
    (void *)gHippogriffFliesIntoAir2Tiles, (void *)gHippogriffFliesIntoAir2Frames,
    (void *)gHippogriffFliesIntoAir2Palette, 0,
};
