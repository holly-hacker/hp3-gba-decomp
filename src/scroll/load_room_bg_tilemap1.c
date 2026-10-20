#include "types.h"
#include "decompress.h"
#include "mem.h"
#include "scroll.h"

// Decompresses BG layer 1's block map into a new heap block.
void LoadRoomBgTilemap1(const void *pTilemap)
{
    g_pRoomBgLayer1MapAlloc = AllocBlock(GetResourceDecompressedSize(pTilemap));
    g_RoomBgBlockData.apBlockMaps[1] = (u16 *)(g_pRoomBgLayer1MapAlloc + 4);
    DecompressResource(pTilemap, g_pRoomBgLayer1MapAlloc);
    g_RoomBgAux.bFlags &= ~5;
}
