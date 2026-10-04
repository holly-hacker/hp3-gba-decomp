#include "types.h"
#include "hw/io_regs.h"
#include "game/save.h"

void EepromTransferEnd(void)
{
    REG_DISPSTAT = g_wEepromSavedDispstat;
}
