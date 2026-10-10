#include "types.h"
#include "hw/io_regs.h"
#include "gamecube.h"

// Counts frames without a JOY interrupt; past 10 the link is reset and 1 is returned.
u32 TickJoybusTimeout(void)
{
    if (g_JoybusLinkState.bTimeoutCounter <= 10)
    {
        REG_IME = 0;
        g_JoybusLinkState.bTimeoutCounter++;
        REG_IME = 1;
        return 0;
    }

    g_JoybusLinkState.bTimedOut = 1;
    g_JoybusLinkState.bError = JOYBUS_ERROR_TIMEOUT;
    SetupJoybusHardware();
    return 1;
}
