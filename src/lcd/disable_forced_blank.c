#include "lcd.h"
#include "hw/io_regs.h"

void DisableForcedBlank(void)
{
    REG_DISPCNT &= ~DISPCNT_FORCED_BLANK;
}
