#include "types.h"
#include "decompress.h"
#include "mem.h"
#include "scroll.h"

// Decompresses BG layer 1's block tile table (a block count, then the blocks) into a new heap
// block and takes the layer's size from its block map, which must already be loaded.
void LoadRoomBgBlockTiles1(const void *pBlockTiles, u32 unused8, u32 unusedC)
{
    u32 firstWord;

    g_pRoomBgLayer1TilesAlloc = AllocBlock(GetResourceDecompressedSize(pBlockTiles));
    g_RoomBgBlockData.apBlockTiles[1] = (u16 (*)[16])(g_pRoomBgLayer1TilesAlloc + 1);
    DecompressResource(pBlockTiles, g_pRoomBgLayer1TilesAlloc);
    g_adwBgBlockAttrOffset[1] = g_pRoomBgLayer1TilesAlloc[0] * 32;
    g_pRoomBgLayer1TilesAlloc++;

    g_wRoomBgLayer1TilesWide = g_pRoomBgLayer1MapAlloc[0] * 4;
    g_wRoomBgLayer1TilesHigh = g_pRoomBgLayer1MapAlloc[2] * 4;
    g_wRoomBgLayer1BlocksWide = g_pRoomBgLayer1MapAlloc[0];
    g_wRoomBgLayer1BlocksHigh = g_pRoomBgLayer1MapAlloc[2];
    g_wRoomBgLayer1MapSize = 2 * g_wRoomBgLayer1BlocksWide * g_wRoomBgLayer1BlocksHigh;
    firstWord = g_pRoomBgLayer1TilesAlloc[0];
    g_dwRoomBgLayer1TileWord0 = firstWord;
}
