#include "display.h"
#include "hw/io_regs.h"

u32 GetDispcntMode(void)
{
    return REG_DISPCNT & 7;
}
