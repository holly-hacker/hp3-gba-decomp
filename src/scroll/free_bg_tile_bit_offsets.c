#include "types.h"
#include "mem.h"
#include "scroll.h"

void FreeBgTileBitOffsets(void)
{
    FreeBlock(g_aBgTilesets[0].pTileBitOffsets);
    FreeBlock(g_aBgTilesets[1].pTileBitOffsets);
}
