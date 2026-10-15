#include "interrupts.h"
#include "hw/io_regs.h"

void HandleTimer3Interrupt(void)
{
    g_pVBlankState->dwTimer3Count++;
    REG_IF = 0x40;
    g_wPendingIntrFlags |= 0x40;
}
