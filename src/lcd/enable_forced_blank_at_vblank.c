#include "lcd_inline.h"

void EnableForcedBlankAtVBlank(void)
{
    WaitForVBlankFlagInline();
    REG_DISPCNT |= DISPCNT_FORCED_BLANK;
}
