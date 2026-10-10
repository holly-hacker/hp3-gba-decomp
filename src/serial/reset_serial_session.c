#include "types.h"
#include "game/game_modes.h"
#include "hw/input.h"
#include "serial/serial.h"

void ResetSerialSession(void)
{
    if (g_dwSerialMode == 1)
        DisableSerial();

    g_dwSerialFlags &= ~SERIAL_FLAG_CLEARED_ON_RESET;
    g_dwGameModeFlags &= ~SerialSessionActive;
    g_SerialPlayerState.dwUnk_0x00 = -1;
    ResetKeyInput();
}
