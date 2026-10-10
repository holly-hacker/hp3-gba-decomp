#include "types.h"
#include "serial/serial.h"
#include "hw/io_regs.h"

// Stops the link serial pump and marks the session as absent.
void DisableSerial(void)
{
    if (!(REG_SIOCNT & 4))
        REG_IE &= ~0x40;
    REG_IE &= ~0x80;
    REG_SIOMLT_SEND = 0xFFFF;
    g_SerialPlayerState.bUnk_0x04 = 0;
    g_SerialPlayerState.bPlayerId = -1;
}
