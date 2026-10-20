#include "hw/io_regs.h"
#include "screen_transitions.h"

void SetFadeToBlack(u16 layerMask, u16 amount)
{
    REG_BLDCNT = layerMask | BLDCNT_DARKEN;
    if (amount > 0x10)
        amount = 0x10;
    REG_BLDY = amount;
}
