#include "types.h"
#include "hw/interrupts.h"
#include "hw/io_regs.h"
#include "hw/vblank.h"
#include "serial/serial.h"

// Waits for the multiplayer line to become ready, announces this terminal with SERIAL_WORD_CONNECT
// and installs SerialTimer3Intr: the parent drives transfers from Timer 3, a child answers from
// the serial interrupt. Returns 5 if a session is already set up, 7 if the wait callback aborted,
// otherwise UpdateSerialConnection's result.
u32 SerialConnect(u32 maxPlayers)
{
    g_dwSerialMaxPlayers = maxPlayers;
    if (g_SerialLink.dwFlags & (SERIAL_FLAG_PLAYER_ID_ERROR | SERIAL_FLAG_CLEARED_ON_RESET))
        return 5;

    REG_SIOMLT_SEND = 0xFFFF;
    while (!(REG_SIOCNT & 8) || (REG_SIOCNT & 0x80))
    {
        if (g_SerialPlayerState.pfnWaitCallback != NULL && !g_SerialPlayerState.pfnWaitCallback())
            return 7;
    }

    REG_SIOMLT_SEND = SERIAL_WORD_CONNECT;
    if (!(REG_SIOCNT & 4))
    {
        SetIntrFunc(0, SerialTimer3Intr);
        REG_IE |= 0x40;
        REG_TM3CNT_L = SERIAL_TIMER_RELOAD;
        if (!(REG_SIOCNT & 4))
        {
            REG_SIOCNT |= 0x80;
            REG_TM3CNT_H = 0xC0;
        }
    }
    else
    {
        SetIntrFunc(0, SerialTimer3Intr);
        REG_IE |= 0x80;
    }
    WaitForVBlankIntr();
    return UpdateSerialConnection();
}
