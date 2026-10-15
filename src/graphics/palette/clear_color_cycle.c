#include "graphics/palette.h"
#include "mem.h"

void ClearColorCycle(ColorCycle *pCycle)
{
    memset(pCycle, 0, sizeof(ColorCycle));
}
