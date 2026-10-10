#include "types.h"
#include "hw/interrupts.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "gamecube.h"

// Game code the GameCube title must send.
static const char sGameCubeGameCode[] = "GAZE";

// Starts a GameCube link session: allocates both transfer buffers, installs the JOY interrupt
// handler and switches the link port to JOY Bus mode.
void InitJoybusSession(JoybusCommandCallback pfnCommand, u32 recvCommandMax, u32 sendCommandMax)
{
    u16 savedIme;

    savedIme = REG_IME;
    REG_IME = 0;

    memset(&g_JoybusLinkState, 0, sizeof(g_JoybusLinkState));
    g_JoybusLinkState.wRecvCommandMax = recvCommandMax;
    g_JoybusLinkState.wSendCommandMax = sendCommandMax;
    g_JoybusLinkState.pRecvBuffer = AllocBlock(JOYBUS_BUFFER_SIZE);
    g_JoybusLinkState.pSendBuffer = AllocBlock(JOYBUS_BUFFER_SIZE);
    g_JoybusLinkState.pfnCommand = pfnCommand;
    g_JoybusLinkState.bInitialSetup = 1;
    SetupJoybusHardware();

    SetIntrFunc(0, HandleJoybusInterrupt);
    REG_IE |= 0x80;
    g_JoybusLinkState.dwGameCode = g_dwRomHeaderGameCode;
    g_JoybusLinkState.dwExpectedPeerGameCode = *(const u32 *)sGameCubeGameCode;

    REG_IME = savedIme;
}
