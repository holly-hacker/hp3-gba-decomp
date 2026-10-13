#include "types.h"
#include "hw/io_regs.h"

void ClearDispcntFlag(u16 flags)
{
    REG_DISPCNT &= ~flags;
}
