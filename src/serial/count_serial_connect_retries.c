#include "types.h"
#include "serial/serial.h"

// Initial wait callback: lets SerialConnect wait 10 times, then aborts it and starts over.
s32 CountSerialConnectRetries(void)
{
    if (++g_dwSerialConnectRetries > 10)
    {
        g_dwSerialConnectRetries = 0;
        return 0;
    }
    return 1;
}
