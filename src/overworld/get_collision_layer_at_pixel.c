#include "types.h"
#include "overworld/terrain.h"

// Returns the draw layer (1-4) stored in the top two bits of the collision behavior byte at a
// room pixel; 1 outside the room.
u32 GetCollisionLayerAtPixel(PixelPoint pixel)
{
    u32 block;
    u32 cell;

    if (pixel.x > g_RoomSizePixels.dwWidth || pixel.y > g_RoomSizePixels.dwHeight)
        return 1;

    block = COLLISION_BLOCK_PATTERN_ID(
        g_pRoomCollisionTilemap[(pixel.x >> 5) + (pixel.y >> 5) * (g_RoomSizePixels.dwWidth >> 5)]);
    cell = ((pixel.x >> 3) & 3) | ((pixel.y >> 1) & 0xC);
    return (g_pRoomCollisionBehaviorTable[block * 16 | cell] >> 6) + 1;
}
