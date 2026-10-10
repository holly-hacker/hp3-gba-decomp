#include "types.h"
#include "hw/io_regs.h"
#include "hw/vblank.h"
#include "serial/serial.h"

// Returns 0 without a session, 6 if this terminal's ID is out of range (dropping the session),
// otherwise the number of answering terminals. A session that stops exchanging is restarted.
u32 UpdateSerialConnection(void)
{
    u32 elapsed;

    if (g_SerialPlayerState.bPlayerId == -1)
        return 0;

    if (g_SerialPlayerState.bPlayerId >= (s32)g_dwSerialMaxPlayers)
    {
        g_SerialPlayerState.bPlayerCount = 0;
        g_SerialPlayerState.bPlayerId = -1;
        g_SerialLink.dwFlags |= SERIAL_FLAG_PLAYER_ID_ERROR;
        REG_IE &= ~0x80;
        REG_SIOMLT_SEND = 0xFFFF;
        return 6;
    }

    elapsed = g_pVBlankState->dwVBlankCount - g_dwSerialLastExchangeTime;
    if (g_dwSerialPlayerCount != 0 && elapsed > 3)
    {
        g_dwSerialPlayerCount = 0;
        g_bSerialPlayerMask = 0;
        InitSerialSession();
    }
    return g_dwSerialPlayerCount;
}
