#include "types.h"
#include "overworld/room.h"
#include "scroll.h"

void EnableBgLayerScroll(u32 layer)
{
    g_adwBgScrollEnabled[layer] = 1;
}
