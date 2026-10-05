#include "types.h"
#include "hw/mem.h"
#include "graphics/display.h"

void InitScreenTransitionState_candidate(void)
{
    SetScreenDarkenParams_candidate(0, 8);
    g_pScreenPaletteBackup = AllocZeroed(0x400);
}
