#include "interrupts.h"
#include "hw/io_regs.h"

void HandleHBlankInterrupt(void)
{
    if (g_pVBlankState->pHBlankCallback != NULL)
        g_pVBlankState->pHBlankCallback();

    g_pVBlankState->dwHBlankCount++;
    REG_IF = 2;
    g_wPendingIntrFlags |= 2;
}
