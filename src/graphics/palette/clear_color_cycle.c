#include "graphics/palette.h"
#include "hw/mem.h"

void ClearColorCycle(ColorCycle *pCycle)
{
    memset(pCycle, 0, sizeof(ColorCycle));
}
