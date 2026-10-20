#include "types.h"
#include "decompress.h"
#include "mem.h"
#include "scroll.h"

// Decompresses BG layer 3's block map into a new heap block.
void LoadRoomBgTilemap3(const void *pTilemap)
{
    g_pRoomBgLayer3MapAlloc = AllocBlock(GetResourceDecompressedSize(pTilemap));
    g_RoomBgBlockData.apBlockMaps[3] = (u16 *)(g_pRoomBgLayer3MapAlloc + 4);
    DecompressResource(pTilemap, g_pRoomBgLayer3MapAlloc);
    g_RoomBgAux.bFlags &= ~5;
}
