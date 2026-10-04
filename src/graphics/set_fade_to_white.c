#include "graphics/display.h"
#include "hw/io_regs.h"

void SetFadeToWhite(u16 layerMask, u16 amount)
{
    REG_BLDCNT = layerMask | 0x80;
    if (amount > 0x10)
        amount = 0x10;
    REG_BLDY = amount;
}
