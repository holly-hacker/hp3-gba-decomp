#include "types.h"
#include "mem.h"
#include "vram.h"

// Frees every OBJ tile at once and clears any pending deferred frees.
void FreeAllObjVramTiles(void)
{
    memset(g_abObjTileAllocBitmap, 0, 0x80);
    memset(g_abObjTileFreeMask, 0xFF, 0x80);
}
