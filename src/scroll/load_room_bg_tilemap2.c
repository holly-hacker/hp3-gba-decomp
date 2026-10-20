#include "types.h"
#include "decompress.h"
#include "mem.h"
#include "scroll.h"

// Decompresses BG layer 2's block map into a new heap block.
void LoadRoomBgTilemap2(const void *pTilemap)
{
    g_pRoomBgLayer2MapAlloc = AllocBlock(GetResourceDecompressedSize(pTilemap));
    g_RoomBgBlockData.apBlockMaps[2] = (u16 *)(g_pRoomBgLayer2MapAlloc + 4);
    DecompressResource(pTilemap, g_pRoomBgLayer2MapAlloc);
    g_RoomBgAux.bFlags &= ~5;
}
