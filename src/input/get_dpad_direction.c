#include "input.h"

Direction GetDpadDirection(void)
{
    return g_abDpadDirection[(g_wKeysHeld & (KeyRight | KeyLeft | KeyUp | KeyDown)) >> 4];
}
