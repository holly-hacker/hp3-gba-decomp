#include "types.h"
#include "serial/serial.h"

// The argument is ignored; the connection is always opened for two players.
u32 StartSerialConnection(u32 unused)
{
    g_bSerialUnk03005A10 = 0;
    g_bSerialSeedReceived = 0;
    g_SerialLink.dwFlags &= ~SERIAL_FLAG_CLOSED;
    return SerialConnect(2);
}
