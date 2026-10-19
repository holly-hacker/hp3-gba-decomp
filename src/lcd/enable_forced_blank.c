#include "lcd.h"
#include "hw/io_regs.h"

void EnableForcedBlank(void)
{
    REG_DISPCNT |= DISPCNT_FORCED_BLANK;
}
