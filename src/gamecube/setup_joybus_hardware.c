#include "types.h"
#include "hw/io_regs.h"
#include "gamecube.h"

// Switches the link port to JOY Bus mode with the JOY interrupt enabled and clears the session
// flags. Only a reset outside InitJoybusSession passes RCNT through general-purpose mode first.
void SetupJoybusHardware(void)
{
    u16 savedIme;

    savedIme = REG_IME;
    REG_IME = 0;

    if (g_JoybusLinkState.bInitialSetup == 0)
        REG_RCNT = 0x8000;
    REG_RCNT = 0xC000;
    REG_JOYSTAT = 0;
    REG_JOY_RECV;
    REG_JOY_TRANS = 0;
    REG_JOYCNT = 0x47;
    REG_IF = 0x80;

    g_JoybusLinkState.bTimeoutCounter = 0;
    g_JoybusLinkState.bState = JOYBUS_STATE_IDLE;
    g_JoybusLinkState.bConnected = 0;
    g_JoybusLinkState.bHandshake = JOYBUS_HANDSHAKE_NONE;
    g_JoybusLinkState.bInitialSetup = 0;

    REG_IME = savedIme;
}
