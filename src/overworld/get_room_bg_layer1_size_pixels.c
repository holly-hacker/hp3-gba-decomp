#include "types.h"
#include "overworld/room.h"

void GetRoomBgLayer1SizePixels(s32 *size)
{
    size[0] = g_wRoomBgLayer1TilesWide << 3;
    size[1] = g_wRoomBgLayer1TilesHigh << 3;
}
