#include "modes.h"
#include "serial.h"
#include "main.h"

void TickSerialCommIfActive(void)
{
    if ((g_dwGameModeFlags & SerialSessionActive) && g_dwSerialMode == 1)
        ExchangeSerialFrame();
}
