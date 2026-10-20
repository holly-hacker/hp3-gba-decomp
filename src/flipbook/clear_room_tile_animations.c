#include "mem.h"
#include "flipbook.h"

void ClearRoomTileAnimations(void)
{
    memset(g_aRoomTileAnimations, 0, MAX_ROOM_TILE_ANIMATIONS * sizeof(RoomTileAnimation));
    g_dwRoomTileAnimationCount = 0;
}
