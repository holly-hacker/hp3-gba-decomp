#include "types.h"
#include "decompress.h"
#include "mem.h"
#include "scroll.h"

// Decompresses BG layer 3's block tile table (a block count, then the blocks) into a new heap
// block and takes the layer's size from its block map, which must already be loaded.
void LoadRoomBgBlockTiles3(const void *pBlockTiles, u32 unused8, u32 unusedC)
{
    u32 firstWord;

    g_pRoomBgLayer3TilesAlloc = AllocBlock(GetResourceDecompressedSize(pBlockTiles));
    g_RoomBgBlockData.apBlockTiles[3] = (u16 (*)[16])(g_pRoomBgLayer3TilesAlloc + 1);
    DecompressResource(pBlockTiles, g_pRoomBgLayer3TilesAlloc);
    g_adwBgBlockAttrOffset[3] = g_pRoomBgLayer3TilesAlloc[0] * 32;
    g_pRoomBgLayer3TilesAlloc++;

    g_wRoomBgLayer3TilesWide = g_pRoomBgLayer3MapAlloc[0] * 4;
    g_wRoomBgLayer3TilesHigh = g_pRoomBgLayer3MapAlloc[2] * 4;
    g_wRoomBgLayer3BlocksWide = g_pRoomBgLayer3MapAlloc[0];
    g_wRoomBgLayer3BlocksHigh = g_pRoomBgLayer3MapAlloc[2];
    g_wRoomBgLayer3MapSize = 2 * g_wRoomBgLayer3BlocksWide * g_wRoomBgLayer3BlocksHigh;
    firstWord = g_pRoomBgLayer3TilesAlloc[0];
    g_dwRoomBgLayer3TileWord0 = firstWord;
}
