#include "types.h"
#include "serial/serial.h"

// The arguments are ignored.
u32 TickSerialSession(u32 unused0, u32 unused1)
{
    return UpdateSerialConnection();
}
