#include "types.h"
#include "serial/serial.h"

u32 IsSerialFrameReady(void)
{
    if (g_SerialLink.dwFlags & SERIAL_FLAG_FRAME_READY)
        return 1;
    return 0;
}
