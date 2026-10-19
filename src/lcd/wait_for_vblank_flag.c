#include "lcd_inline.h"

// Busy-waits on DISPSTAT, unlike WaitForVBlankIntr, which sleeps until the
// interrupt.
void WaitForVBlankFlag(void)
{
    WaitForVBlankFlagInline();
}
