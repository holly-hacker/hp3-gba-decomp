#include "hw/vblank.h"
#include "hw/io_regs.h"

// Enables the VCount interrupt and its DISPSTAT IRQ, adding `line` to the
// DISPSTAT VCount-setting field.
void EnableVCountInterrupt(u32 line)
{
    REG_IE |= 4;
    REG_DISPSTAT |= 0x20 | (line << 8);
}
