#include "types.h"
#include "overworld/room.h"

// Returns a pointer to the block map entry covering pixel (x, y) on BG `layer`, or the first
// entry of a null map for an invalid layer.
u16 *GetRoomBgBlockMapEntryPtr(u16 x, u16 y, u8 layer)
{
    u16 blockX;
    u16 blockY;
    u16 index;
    u16 *pMap;

    blockX = x >> 5;
    blockY = y >> 5;
    switch (layer)
    {
    case 0:
        index = blockX + blockY * g_wRoomBgLayer0BlocksWide;
        pMap = g_RoomBgBlockData.apBlockMaps[0];
        break;
    case 1:
        index = blockX + blockY * g_wRoomBgLayer1BlocksWide;
        pMap = g_RoomBgBlockData.apBlockMaps[1];
        break;
    case 2:
        index = blockX + blockY * g_wRoomBgLayer2BlocksWide;
        pMap = g_RoomBgBlockData.apBlockMaps[2];
        break;
    case 3:
        index = blockX + blockY * g_wRoomBgLayer3BlocksWide;
        pMap = g_RoomBgBlockData.apBlockMaps[3];
        break;
    default:
        index = 0;
        pMap = 0;
        break;
    }
    return pMap + index;
}
