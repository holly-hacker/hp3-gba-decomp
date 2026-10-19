#include "lcd_inline.h"

void DisableForcedBlankAtVBlank(void)
{
    WaitForVBlankFlagInline();
    REG_DISPCNT &= ~DISPCNT_FORCED_BLANK;
}
