#include "types.h"
#include "game/game_modes.h"
#include "link/link.h"

// Queues this frame's message and runs one exchange round. Returns 1 and drops the session if the
// round times out.
s32 ExchangeLinkFrame_candidate(void)
{
    if (g_dwGameModeFlags & LinkSessionActive)
    {
        if (g_dwLinkPollFlags_candidate & 1)
            QueueLinkMessage(LINK_MESSAGE_IDLE, 0);
        else
            QueueLinkMessage(LINK_MESSAGE_KEYS, 0);

        if (RunLinkExchange() == 1)
        {
            g_dwGameModeFlags &= ~LinkSessionActive;
            g_dwLinkFlags |= LINK_FLAG_CLOSED;
            ResetLinkSession();
            return 1;
        }

        if (g_dwLinkPollFlags_candidate & 1)
            QueueLinkMessage(LINK_MESSAGE_IDLE, 0);
        else
            QueueLinkMessage(LINK_MESSAGE_KEYS, 0);
    }
    return 0;
}
