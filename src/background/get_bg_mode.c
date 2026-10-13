#include "types.h"
#include "hw/io_regs.h"

u32 GetBgMode(void)
{
    return REG_DISPCNT & 7;
}
