#include "types.h"
#include "actor.h"

void GetOamShapeSizeDims(u32 shape, u32 size, s32 *dims)
{
    dims[0] = g_aOamShapeSizes[shape][size].bWidth;
    dims[1] = g_aOamShapeSizes[shape][size].bHeight;
}
