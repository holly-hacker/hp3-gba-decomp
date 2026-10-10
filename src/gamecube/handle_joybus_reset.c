#include "types.h"
#include "hw/io_regs.h"
#include "gamecube.h"

// Handles a JOY Bus reset from the GameCube: loads this cartridge's game code for the GameCube
// to read and restarts the handshake.
void HandleJoybusReset(void)
{
    REG_JOY_RECV;
    REG_JOY_TRANS = g_JoybusLinkState.dwGameCode;
    REG_JOYSTAT = 0x20;
    g_JoybusLinkState.bState = JOYBUS_STATE_IDLE;
    g_JoybusLinkState.bConnected = 0;
    g_JoybusLinkState.bHandshake = JOYBUS_HANDSHAKE_RESET;
}
