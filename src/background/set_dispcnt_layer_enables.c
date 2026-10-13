#include "types.h"
#include "hw/io_regs.h"

void SetDispcntLayerEnables(u16 layers)
{
    REG_DISPCNT = (REG_DISPCNT & 0xE0FF) | layers;
}
