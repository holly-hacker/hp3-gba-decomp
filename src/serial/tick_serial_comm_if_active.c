#include "types.h"
#include "game/game_modes.h"
#include "serial/serial.h"

void TickSerialCommIfActive_candidate(void)
{
    if ((g_dwGameModeFlags & SerialSessionActive) && g_dwSerialMode == 1)
        ExchangeSerialFrame_candidate();
}
