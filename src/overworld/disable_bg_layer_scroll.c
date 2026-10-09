#include "types.h"
#include "overworld/room.h"

void DisableBgLayerScroll(u32 layer)
{
    g_adwBgScrollEnabled[layer] = 0;
}
