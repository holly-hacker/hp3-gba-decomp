#include "types.h"
#include "graphics/display.h"

void SetScreenDarkenParams_candidate(u32 arg0, u32 stepTicks)
{
    g_dwUnk03005638 = arg0;
    g_dwScreenDarkenStepTicks_candidate = stepTicks;
}
