#include "types.h"
#include "modes.h"
#include "input.h"
#include "serial/serial.h"

void ResetSerialSession(void)
{
    if (g_dwSerialMode == 1)
        DisableSerial();

    g_SerialLink.dwFlags &= ~SERIAL_FLAG_CLEARED_ON_RESET;
    g_dwGameModeFlags &= ~SerialSessionActive;
    g_SerialPlayerState.dwUnk_0x00 = -1;
    ResetKeyInput();
}
