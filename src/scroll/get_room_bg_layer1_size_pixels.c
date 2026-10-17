#include "types.h"
#include "scroll.h"

void GetRoomBgLayer1SizePixels(s32 *size)
{
    size[0] = g_wRoomBgLayer1TilesWide << 3;
    size[1] = g_wRoomBgLayer1TilesHigh << 3;
}
