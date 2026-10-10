#include "types.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "hw/vblank.h"
#include "serial/serial.h"

// True once more than SERIAL_TIMEOUT_VBLANKS vblanks have passed since the last exchange.
static inline s32 HasSerialExchangeTimedOut(void)
{
    if ((s32)(g_pVBlankState->dwVBlankCount - g_dwSerialLastExchangeTime) > SERIAL_TIMEOUT_VBLANKS)
        return 1;
    return 0;
}

// Waits for the serial interrupt to deliver the other side's message, applies it, and starts the
// next round. Returns 1 if a wait ran longer than SERIAL_TIMEOUT_VBLANKS.
s32 RunSerialExchange(void)
{
    if (g_SerialLink.dwFlags & SERIAL_FLAG_CLOSED)
    {
        g_SerialLink.dwFlags |= SERIAL_FLAG_CLOSED;
        ResetSerialSession();
        return 0;
    }

    do
    {
        while (!(g_SerialLink.dwFlags & SERIAL_FLAG_FRAME_READY))
        {
            if (HasSerialExchangeTimedOut())
            {
                g_SerialLink.dwFlags |= SERIAL_FLAG_TIMED_OUT;
                return 1;
            }
        }

        while (!(g_SerialLink.dwFlags & SERIAL_FLAG_TRANSFER_DONE))
        {
            if (!(g_SerialLink.dwFlags & SERIAL_FLAG_TRANSFER_STARTED) && g_SerialPlayerState.dwUnk_0x00 == -1)
            {
                g_SerialLink.dwFlags |= SERIAL_FLAG_TRANSFER_KICKED;
                g_SerialLink.dwFlags |= SERIAL_FLAG_TRANSFER_STARTED;
                if (g_SerialPlayerState.bPlayerId == 0)
                {
                    REG_SIOMLT_SEND = 0xC0DE;
                    REG_SIOCNT |= 0x80;
                    REG_TM3CNT_H = 0xC0;
                }
            }
            if (HasSerialExchangeTimedOut())
            {
                g_SerialLink.dwFlags |= SERIAL_FLAG_TIMED_OUT;
                return 1;
            }
        }

        g_SerialLink.dwFlags &= ~SERIAL_FLAG_TRANSFER_DONE;
        g_SerialLink.dwFlags &= ~SERIAL_FLAG_TRANSFER_STARTED;
    } while (!(g_SerialLink.dwFlags & SERIAL_FLAG_ROUND_COMPLETE));

    ProcessSerialMessages();
    g_SerialLink.dwFlags &= ~SERIAL_FLAG_FRAME_READY;
    g_SerialLink.dwFlags &= ~SERIAL_FLAG_ROUND_COMPLETE;
    g_dwSerialExchangeCount++;
    if (g_SerialPlayerState.bPlayerId == 0)
    {
        REG_SIOMLT_SEND = 0xBEEF;
        REG_SIOCNT |= 0x80;
        REG_TM3CNT_H = 0xC0;
    }
    g_dwSerialLastExchangeTime = g_pVBlankState->dwVBlankCount;
    memset(&g_SerialSendMessage, 0, sizeof(SerialMessage));
    return 0;
}
