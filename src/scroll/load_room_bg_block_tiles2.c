#include "types.h"
#include "decompress.h"
#include "mem.h"
#include "scroll.h"

// Decompresses BG layer 2's block tile table (a block count, then the blocks) into a new heap
// block and takes the layer's size from its block map, which must already be loaded.
void LoadRoomBgBlockTiles2(const void *pBlockTiles, u32 unused8, u32 unusedC)
{
    u32 firstWord;

    g_pRoomBgLayer2TilesAlloc = AllocBlock(GetResourceDecompressedSize(pBlockTiles));
    g_RoomBgBlockData.apBlockTiles[2] = (u16 (*)[16])(g_pRoomBgLayer2TilesAlloc + 1);
    DecompressResource(pBlockTiles, g_pRoomBgLayer2TilesAlloc);
    g_adwBgBlockAttrOffset[2] = g_pRoomBgLayer2TilesAlloc[0] * 32;
    g_pRoomBgLayer2TilesAlloc++;

    g_wRoomBgLayer2TilesWide = g_pRoomBgLayer2MapAlloc[0] * 4;
    g_wRoomBgLayer2TilesHigh = g_pRoomBgLayer2MapAlloc[2] * 4;
    g_wRoomBgLayer2BlocksWide = g_pRoomBgLayer2MapAlloc[0];
    g_wRoomBgLayer2BlocksHigh = g_pRoomBgLayer2MapAlloc[2];
    g_wRoomBgLayer2MapSize = 2 * g_wRoomBgLayer2BlocksWide * g_wRoomBgLayer2BlocksHigh;
    firstWord = g_pRoomBgLayer2TilesAlloc[0];
    g_dwRoomBgLayer2TileWord0 = firstWord;
}
