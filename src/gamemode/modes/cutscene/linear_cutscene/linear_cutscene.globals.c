#include "types.h"
#include "cutscene/linear_cutscene.h"
#include "gen/graphics/cutscenes.h"

const u32 g_dwLinearCutsceneBg0Control = 0x3D03;
const u32 g_dwLinearCutsceneBg1Control = 0xBE09;

const LinearCutsceneEntry g_aLinearCutsceneTable[10] = {
    { gCreditsGraphic, 0x6C3, 0x204 },  // credits
    { gIntroCutsceneGraphic, 0x5AA, 1 },
    { gHarryArrivedAtHogwartsCutsceneGraphic, 0x5AB, 1 },
    { gUnusedChristmasArrivedCutsceneGraphic, 0x5AC, 1 },
    { gSiriusBlackCutsceneGraphic, 0x5AD, 1 },
    { gPeterPettigrewCutsceneGraphic, 0x5AE, 1 },
    { gRonSleepingCutsceneGraphic, 0x5AF, 1 },
    { gTimeTurnerPermissionCutsceneGraphic, 0x5B0, 1 },
    { gHippogriffTookToAirCutsceneGraphic, 0x5B1, 1 },
    { gGameCompletedReplayCutsceneGraphic, 0x906, 1 },
};
