#include "types.h"
#include "hw/io_regs.h"

void SetDispcntFlag(u16 flags)
{
    REG_DISPCNT |= flags;
}
