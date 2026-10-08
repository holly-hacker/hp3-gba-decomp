#include "types.h"
#include "graphics/graphics.h"

// Integrates delta-coded halfwords in place: each becomes the running sum.
void ApplyResourceDeltaPass(u16 *pData, u32 size)
{
    u32 i;

    for (i = 1; i < size / 2; i++)
        pData[i] += pData[i - 1];
}
