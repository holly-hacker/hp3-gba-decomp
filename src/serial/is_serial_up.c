#include "types.h"
#include "serial/serial.h"

// True while exactly two terminals, in slots 0 and 1, answer the serial interrupt.
u32 IsSerialUp(void)
{
    if (g_dwSerialPlayerCount == 2 && g_bSerialPlayerMask == 3)
        return 1;
    return 0;
}
