#include "types.h"
#include "hw/vblank.h"
#include "serial/serial.h"

// Requests the 0xB0CA handshake and waits for it to complete, for at least 20 frames.
void WaitForSerialHandshake(void)
{
    u32 frames = 0;

    g_SerialLink.dwFlags |= SERIAL_FLAG_HANDSHAKE;
    while (!(g_SerialLink.dwFlags & SERIAL_FLAG_CLEARED_ON_RESET) || frames < 20)
    {
        frames++;
        WaitForVBlankIntr();
    }
    g_SerialLink.dwFlags &= ~SERIAL_FLAG_HANDSHAKE;
}
