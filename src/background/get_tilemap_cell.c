#include "types.h"
#include "background.h"

u16 GetTilemapCell(const u16 *pTilemap, u32 x, u32 y, u32 stride)
{
    pTilemap = pTilemap + y * stride + x;
    return *pTilemap;
}
