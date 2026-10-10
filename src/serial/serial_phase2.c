#include "types.h"
#include "hw/vblank.h"
#include "serial/serial.h"

// Wait callback installed once the handshake completes: true once SERIAL_TIMEOUT_VBLANKS have
// passed since the last exchange.
s32 SerialPhase2(void)
{
    if ((s32)(g_pVBlankState->dwVBlankCount - g_dwSerialLastExchangeTime) > SERIAL_TIMEOUT_VBLANKS)
        return 1;
    return 0;
}
