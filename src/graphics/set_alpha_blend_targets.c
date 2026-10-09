#include "types.h"
#include "hw/io_regs.h"

// Selects alpha blending with the layers in the `firstTargets` mask as the first target and
// those in `secondTargets` as the second.
void SetAlphaBlendTargets(u16 firstTargets, u16 secondTargets)
{
    REG_BLDCNT = firstTargets | 0x40 | (secondTargets << 8);
}
