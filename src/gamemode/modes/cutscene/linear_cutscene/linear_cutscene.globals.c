#include "types.h"
#include "cutscene/linear_cutscene.h"
#include "gen/graphics/cutscenes.h"

const u32 g_dwLinearCutsceneBg0Control = 0x3D03;
const u32 g_dwLinearCutsceneBg1Control = 0xBE09;

const LinearCutsceneEntry g_aLinearCutsceneTable[10] = {
    { gCutsceneDrawingsStartup002, 0x6C3, 0x204 },  // credits
    { gCutsceneDrawingsStartup003, 0x5AA, 1 },
    { gCutsceneDrawingsStartup004, 0x5AB, 1 },
    { gCutsceneDrawingsStartup005, 0x5AC, 1 },
    { gCutsceneDrawingsStartup006, 0x5AD, 1 },
    { gCutsceneDrawingsStartup007, 0x5AE, 1 },
    { gCutsceneDrawingsStartup008, 0x5AF, 1 },
    { gCutsceneDrawingsStartup009, 0x5B0, 1 },
    { gCutsceneDrawingsStartup010, 0x5B1, 1 },
    { gCutsceneDrawingsStartup011, 0x906, 1 },
};
