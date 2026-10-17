#include "mem.h"
#include "flipbook.h"

void InitRoomTileAnimationTable(void)
{
    g_aRoomTileAnimations = AllocZeroed(MAX_ROOM_TILE_ANIMATIONS * sizeof(RoomTileAnimation));
    g_dwRoomTileAnimationCount = 0;
}
