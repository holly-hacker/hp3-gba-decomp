#include "types.h"
#include "mem.h"
#include "screen_transitions.h"

void InitScreenTransitionState_candidate(void)
{
    SetScreenDarkenParams_candidate(0, 8);
    g_pScreenPaletteBackup = AllocZeroed(0x400);
}
