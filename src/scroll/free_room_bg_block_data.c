#include "types.h"
#include "mem.h"
#include "scroll.h"

// Frees each BG layer's block map and block tile table loaded for the previous room.
void FreeRoomBgBlockData(void)
{
    if (g_pRoomBgLayer0MapAlloc != NULL)
        FreeBlock(g_pRoomBgLayer0MapAlloc);
    if (g_pRoomBgLayer1MapAlloc != NULL)
        FreeBlock(g_pRoomBgLayer1MapAlloc);
    if (g_pRoomBgLayer2MapAlloc != NULL)
        FreeBlock(g_pRoomBgLayer2MapAlloc);
    if (g_pRoomBgLayer3MapAlloc != NULL)
        FreeBlock(g_pRoomBgLayer3MapAlloc);
    if (g_pRoomBgLayer0TilesAlloc != NULL)
        FreeBlock(--g_pRoomBgLayer0TilesAlloc);
    if (g_pRoomBgLayer1TilesAlloc != NULL)
        FreeBlock(--g_pRoomBgLayer1TilesAlloc);
    if (g_pRoomBgLayer2TilesAlloc != NULL)
        FreeBlock(--g_pRoomBgLayer2TilesAlloc);
    if (g_pRoomBgLayer3TilesAlloc != NULL)
        FreeBlock(--g_pRoomBgLayer3TilesAlloc);
}
