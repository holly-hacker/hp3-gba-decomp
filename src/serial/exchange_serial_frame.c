#include "types.h"
#include "game/game_modes.h"
#include "serial/serial.h"

// Queues this frame's message and runs one exchange round. Returns 1 and drops the session if the
// round times out.
s32 ExchangeSerialFrame_candidate(void)
{
    if (g_dwGameModeFlags & SerialSessionActive)
    {
        if (g_dwSerialPollFlags_candidate & 1)
            QueueSerialMessage(SERIAL_MESSAGE_IDLE, 0);
        else
            QueueSerialMessage(SERIAL_MESSAGE_KEYS, 0);

        if (RunSerialExchange() == 1)
        {
            g_dwGameModeFlags &= ~SerialSessionActive;
            g_SerialLink.dwFlags |= SERIAL_FLAG_CLOSED;
            ResetSerialSession();
            return 1;
        }

        if (g_dwSerialPollFlags_candidate & 1)
            QueueSerialMessage(SERIAL_MESSAGE_IDLE, 0);
        else
            QueueSerialMessage(SERIAL_MESSAGE_KEYS, 0);
    }
    return 0;
}
