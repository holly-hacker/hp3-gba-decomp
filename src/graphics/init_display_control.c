#include "graphics/display.h"
#include "hw/io_regs.h"

// Mode 4 with 1D OBJ tile mapping and BG0-3 and OBJ all enabled.
void InitDisplayControl(void)
{
    REG_DISPCNT = 0x1F44;
}
