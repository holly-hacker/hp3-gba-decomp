#include "interrupts.h"
#include "hw/io_regs.h"

// Clears the VCount interrupt enable and its DISPSTAT IRQ bit.
void DisableVCountInterrupt(void)
{
    REG_IE &= ~4;
    REG_DISPSTAT &= ~0x20;
}
