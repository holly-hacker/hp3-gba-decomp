#include "types.h"
#include "font.h"

// Returns the entry of a 32-tile-wide tilemap covering pixel (x, y).
u16 *GetTilemapEntryAt(u16 *pTilemap, s32 x, s32 y)
{
    y /= 8;
    x /= 8;
    return &pTilemap[y * 32 + x];
}
