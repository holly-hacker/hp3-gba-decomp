#include "types.h"
#include "hw/io_regs.h"

void SetBgMode(u16 mode)
{
    REG_DISPCNT = (REG_DISPCNT & 0xFFF8) | mode;
}
