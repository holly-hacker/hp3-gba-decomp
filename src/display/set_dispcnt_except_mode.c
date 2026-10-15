#include "display.h"
#include "hw/io_regs.h"

void SetDispcntExceptMode(u16 value)
{
    REG_DISPCNT = (REG_DISPCNT & 7) | value;
}
