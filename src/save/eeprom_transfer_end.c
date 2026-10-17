#include "hw/io_regs.h"
#include "save.h"

void EepromTransferEnd(void)
{
    REG_DISPSTAT = g_wEepromSavedDispstat;
}
