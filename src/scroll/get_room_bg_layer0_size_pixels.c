#include "types.h"
#include "scroll.h"

void GetRoomBgLayer0SizePixels(s32 *size)
{
    size[0] = g_wRoomBgLayer0TilesWide << 3;
    size[1] = g_wRoomBgLayer0TilesHigh << 3;
}
