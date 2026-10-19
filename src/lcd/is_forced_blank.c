#include "lcd.h"
#include "hw/io_regs.h"

u16 IsForcedBlank(void)
{
    return REG_DISPCNT & DISPCNT_FORCED_BLANK;
}
