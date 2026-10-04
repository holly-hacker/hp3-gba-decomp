#include "types.h"
#include "hw/io_regs.h"
#include "hw/eeprom.h"
#include "game/save.h"

// Prepares for a run of EEPROM block transfers: saves DISPSTAT and clears
// it (no display-status IRQs during the transfer), acknowledges every
// pending interrupt, and selects the 8 KB EEPROM geometry.
void EepromTransferBegin(void)
{
    g_wEepromSavedDispstat = REG_DISPSTAT;
    REG_IF = 0x3FFF;
    REG_DISPSTAT = 0;
    EepromSelectInterface(0x40);
}
