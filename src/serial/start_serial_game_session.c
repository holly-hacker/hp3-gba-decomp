#include "types.h"
#include "game/game_modes.h"
#include "mt19937.h"
#include "serial/serial.h"

// Runs once the handshake completes: the parent picks the shared RNG seed and sends it, a child
// answers with an idle message.
void StartSerialGameSession(void)
{
    g_dwGameModeFlags |= SerialSessionActive;
    g_bSerialPeerCount = GetSerialPlayerCount();
    g_bSerialLocalPlayerId = GetSerialPlayerId();
    if (g_bSerialLocalPlayerId == 0)
        QueueSerialMessage(SERIAL_MESSAGE_SEED, Mt19937RandMax(0xFFFF));
    else
        QueueSerialMessage(SERIAL_MESSAGE_IDLE, 0);
}
