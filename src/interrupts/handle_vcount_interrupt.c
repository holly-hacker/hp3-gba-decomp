#include "interrupts.h"
#include "hw/io_regs.h"

void HandleVCountInterrupt(void)
{
    if (g_pVBlankState->pVCountCallback != NULL)
        g_pVBlankState->pVCountCallback();

    g_pVBlankState->dwVCountCount++;
    REG_IF = 4;
    g_wPendingIntrFlags |= 4;
}
