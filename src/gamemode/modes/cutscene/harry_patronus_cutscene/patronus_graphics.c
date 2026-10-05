#include "types.h"
#include "cutscene/harry_patronus_cutscene.h"
#include "gen/graphics/cutscenes.h"

// BG graphics the cutscene cycles through (see g_bPatronusGraphicIndex).
const u8 *const g_apPatronusGraphics[6] = {
    gPatronusCutscene001,
    gPatronusCutscene002,
    gPatronusCutscene003,
    gPatronusCutscene004,
    gPatronusCutscene005,
    gPatronusCutscene006,
};
