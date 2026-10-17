#include "types.h"
#include "scroll.h"

void DisableBgLayerScroll(u32 layer)
{
    g_adwBgScrollEnabled[layer] = 0;
}
