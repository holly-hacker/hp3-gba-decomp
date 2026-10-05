#include "types.h"
#include "hw/mem.h"
#include "overworld/room.h"

void InitRoomTileAnimationTable(void)
{
    g_aRoomTileAnimations = AllocZeroed(MAX_ROOM_TILE_ANIMATIONS * sizeof(RoomTileAnimation));
    g_dwRoomTileAnimationCount = 0;
}
