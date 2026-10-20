#include "types.h"
#include "decompress.h"
#include "mem.h"
#include "scroll.h"

// Decompresses BG layer 0's block map into a new heap block.
void LoadRoomBgTilemap0(const void *pTilemap)
{
    g_pRoomBgLayer0MapAlloc = AllocBlock(GetResourceDecompressedSize(pTilemap));
    g_RoomBgBlockData.apBlockMaps[0] = (u16 *)(g_pRoomBgLayer0MapAlloc + 4);
    DecompressResource(pTilemap, g_pRoomBgLayer0MapAlloc);
    g_bUnk030059B0 = 0;
    g_RoomBgAux.bFlags &= ~3;
    g_RoomBgAux.aPosB[0] = 0x10000;
    g_RoomBgAux.aPosB[1] = 0x10000;
    g_RoomBgAux.aPosA[0] = 0x10000;
    g_RoomBgAux.aPosA[1] = 0x10000;
}
