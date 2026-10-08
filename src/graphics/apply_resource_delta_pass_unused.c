#include "types.h"
#include "graphics/graphics.h"

// An unreferenced copy of ApplyResourceDeltaPass.
void ApplyResourceDeltaPassUnused(u16 *pData, u32 size)
{
    u32 i;

    for (i = 1; i < size / 2; i++)
        pData[i] += pData[i - 1];
}
