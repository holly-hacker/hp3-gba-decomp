#include "types.h"
#include "mode7.h"

void SetFloorHorizonLineAndSkyScroll(s32 horizonLine, u32 scrollSky)
{
    g_nFloorHorizonLine = horizonLine;
    g_dwFloorScrollSky = scrollSky;
}
