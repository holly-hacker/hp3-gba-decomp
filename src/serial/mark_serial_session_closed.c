#include "types.h"
#include "serial/serial.h"

void MarkSerialSessionClosed(void)
{
    g_SerialLink.dwFlags |= SERIAL_FLAG_CLOSED;
}
