#include "lcd.h"
#include "hw/io_regs.h"

u32 IsInVBlank(void)
{
    return REG_DISPSTAT & DISPSTAT_VBLANK;
}
