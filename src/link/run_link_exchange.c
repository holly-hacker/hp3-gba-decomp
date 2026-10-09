#include "types.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "hw/vblank.h"
#include "link/link.h"

// True once more than LINK_TIMEOUT_VBLANKS vblanks have passed since the last exchange.
static inline s32 HasLinkExchangeTimedOut(void)
{
    if ((s32)(g_pVBlankState->dwVBlankCount - g_dwLinkLastExchangeTime) > LINK_TIMEOUT_VBLANKS)
        return 1;
    return 0;
}

// Waits for the serial interrupt to deliver the other side's message, applies it, and starts the
// next round. Returns 1 if a wait ran longer than LINK_TIMEOUT_VBLANKS.
s32 RunLinkExchange(void)
{
    if (g_dwLinkFlags & LINK_FLAG_CLOSED)
    {
        g_dwLinkFlags |= LINK_FLAG_CLOSED;
        ResetLinkSession();
        return 0;
    }

    do
    {
        while (!(g_dwLinkFlags & LINK_FLAG_FRAME_READY))
        {
            if (HasLinkExchangeTimedOut())
            {
                g_dwLinkFlags |= LINK_FLAG_TIMED_OUT;
                return 1;
            }
        }

        while (!(g_dwLinkFlags & LINK_FLAG_TRANSFER_DONE))
        {
            if (!(g_dwLinkFlags & LINK_FLAG_TRANSFER_STARTED) && g_LinkPlayerState.dwUnk_0x00 == -1)
            {
                g_dwLinkFlags |= LINK_FLAG_TRANSFER_KICKED;
                g_dwLinkFlags |= LINK_FLAG_TRANSFER_STARTED;
                if (g_LinkPlayerState.bPlayerId == 0)
                {
                    REG_SIOMLT_SEND = 0xC0DE;
                    REG_SIOCNT |= 0x80;
                    REG_TM3CNT_H = 0xC0;
                }
            }
            if (HasLinkExchangeTimedOut())
            {
                g_dwLinkFlags |= LINK_FLAG_TIMED_OUT;
                return 1;
            }
        }

        g_dwLinkFlags &= ~LINK_FLAG_TRANSFER_DONE;
        g_dwLinkFlags &= ~LINK_FLAG_TRANSFER_STARTED;
    } while (!(g_dwLinkFlags & LINK_FLAG_ROUND_COMPLETE));

    ProcessLinkMessages();
    g_dwLinkFlags &= ~LINK_FLAG_FRAME_READY;
    g_dwLinkFlags &= ~LINK_FLAG_ROUND_COMPLETE;
    g_dwLinkExchangeCount++;
    if (g_LinkPlayerState.bPlayerId == 0)
    {
        REG_SIOMLT_SEND = 0xBEEF;
        REG_SIOCNT |= 0x80;
        REG_TM3CNT_H = 0xC0;
    }
    g_dwLinkLastExchangeTime = g_pVBlankState->dwVBlankCount;
    memset(&g_LinkSendMessage, 0, sizeof(LinkMessage));
    return 0;
}
