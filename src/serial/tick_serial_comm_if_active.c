#include "types.h"
#include "modes.h"
#include "serial.h"
#include "main.h"

void TickSerialCommIfActive_candidate(void)
{
    if ((g_dwGameModeFlags & SerialSessionActive) && g_dwSerialMode == 1)
        ExchangeSerialFrame_candidate();
}
