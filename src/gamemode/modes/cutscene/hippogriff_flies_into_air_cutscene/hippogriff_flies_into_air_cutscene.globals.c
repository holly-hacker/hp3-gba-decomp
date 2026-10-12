#include "types.h"
#include "cutscene/hippogriff_flies_into_air_cutscene.h"
#include "gen/graphics/minigames/boggart.h"

const u32 g_dwHippogriffFliesIntoAirBg0Control = 0x3D03;

// The hippogriff.
const ActorAssetRecord g_HippogriffFliesIntoAirAsset = {
    (void *)gHippogriffFliesIntoAirTiles, (void *)gHippogriffFliesIntoAirFrames,
    (void *)gHippogriffFliesIntoAirPalette, 2,
};

const ActorAssetRecord g_HippogriffFliesIntoAirAsset2 = {
    (void *)gHippogriffFliesIntoAir2Tiles, (void *)gHippogriffFliesIntoAir2Frames,
    (void *)gHippogriffFliesIntoAir2Palette, 0,
};
