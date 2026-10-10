#include "types.h"
#include "serial/serial.h"

void CloseSerialSession(void)
{
    g_SerialLink.dwFlags |= SERIAL_FLAG_CLOSED;
    ResetSerialSession();
}
