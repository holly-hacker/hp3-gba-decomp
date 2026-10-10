#include "types.h"
#include "hw/io_regs.h"
#include "gamecube.h"

// Per-frame driver: resets the link after a timeout and returns the JOYBUS_STATE_* of this
// frame. A completed transfer is reported once, then the state returns to connected.
u32 TickJoybusSession(void)
{
    u16 savedIme;
    u32 state;

    TickJoybusTimeout();

    savedIme = REG_IME;
    REG_IME = 0;

    state = g_JoybusLinkState.bState;
    if (state == JOYBUS_STATE_RECEIVED || state == JOYBUS_STATE_SENT)
        g_JoybusLinkState.bState = JOYBUS_STATE_CONNECTED;

    REG_IME = savedIme;
    return state;
}
