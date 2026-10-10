#include "types.h"
#include "hw/interrupts.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "gamecube.h"

// Ends the session: returns the link port to general-purpose mode, disables the JOY interrupt
// and frees both transfer buffers.
void TeardownJoybusHardware(void)
{
    u16 savedIme;

    savedIme = REG_IME;
    REG_IME = 0;

    REG_RCNT = 0x8000;
    REG_JOYSTAT = 0;
    REG_JOY_RECV;
    REG_JOYCNT = 0x47;
    REG_IE &= ~0x80;
    g_JoybusLinkState.bTimeoutCounter = 0;

    REG_IME = savedIme;

    ResetIntrFunc(0);
    FreeBlock(g_JoybusLinkState.pSendBuffer);
    FreeBlock(g_JoybusLinkState.pRecvBuffer);
    memset(&g_JoybusLinkState, 0, sizeof(g_JoybusLinkState));
}
