#include "interrupts.h"
#include "hw/io_regs.h"

void HandleTimer0Interrupt(void)
{
    g_pVBlankState->dwTimer0Count++;
    REG_IF = 8;
    g_wPendingIntrFlags |= 8;
}
