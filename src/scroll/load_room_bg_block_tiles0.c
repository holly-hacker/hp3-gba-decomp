#include "types.h"
#include "decompress.h"
#include "mem.h"
#include "scroll.h"

// Decompresses BG layer 0's block tile table (a block count, then the blocks) into a new heap
// block and takes the layer's size from its block map, which must already be loaded.
void LoadRoomBgBlockTiles0(const void *pBlockTiles, u32 unused8, u32 unusedC)
{
    u32 firstWord;

    g_pRoomBgLayer0TilesAlloc = AllocBlock(GetResourceDecompressedSize(pBlockTiles));
    g_RoomBgBlockData.apBlockTiles[0] = (u16 (*)[16])(g_pRoomBgLayer0TilesAlloc + 1);
    DecompressResource(pBlockTiles, g_pRoomBgLayer0TilesAlloc);
    g_adwBgBlockAttrOffset[0] = g_pRoomBgLayer0TilesAlloc[0] * 32;
    g_pRoomBgLayer0TilesAlloc++;

    g_wRoomBgLayer0TilesWide = g_pRoomBgLayer0MapAlloc[0] * 4;
    g_wRoomBgLayer0TilesHigh = g_pRoomBgLayer0MapAlloc[2] * 4;
    g_wRoomBgLayer0BlocksWide = g_pRoomBgLayer0MapAlloc[0];
    g_wRoomBgLayer0BlocksHigh = g_pRoomBgLayer0MapAlloc[2];
    g_RoomSizePixels.dwWidth = g_wRoomBgLayer0TilesWide << 3;
    g_RoomSizePixels.dwHeight = g_wRoomBgLayer0TilesHigh << 3;
    g_wRoomBgLayer0MapSize = 2 * g_wRoomBgLayer0BlocksWide * g_wRoomBgLayer0BlocksHigh;
    firstWord = g_pRoomBgLayer0TilesAlloc[0];
    g_dwRoomBgLayer0TileWord0 = firstWord;
}
