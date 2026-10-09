#include "types.h"
#include "mt19937.h"
#include "link/link.h"

// Applies the message received from each peer this round: key masks, idle markers and the RNG seed.
void ProcessLinkMessages(void)
{
    u32 i;
    LinkMessage *pMessage;

    g_dwLinkFlags &= ~LINK_FLAG_OWN_MESSAGE_SEEN;
    for (i = 0; i < g_bLinkPeerCount; i++)
    {
        pMessage = &g_aLinkRecvMessages[i];
        GetLinkPlayerId();
        if (pMessage->bSeq == g_abLinkLastRecvSeq[i] || pMessage->bType == LINK_MESSAGE_NONE)
            continue;

        g_abLinkLastRecvSeq[i] = pMessage->bSeq;
        g_awLinkKeysReceived[i] = 0;
        switch (pMessage->bType)
        {
        case LINK_MESSAGE_IDLE:
            g_awLinkKeysReceived[i] = 0xFF00;
            if (GetLinkPlayerId() == i)
                g_dwLinkFlags |= LINK_FLAG_OWN_MESSAGE_SEEN;
            break;
        case LINK_MESSAGE_KEYS:
            g_awLinkKeysReceived[i] = pMessage->wData;
            if (GetLinkPlayerId() == i)
                g_dwLinkFlags |= LINK_FLAG_OWN_MESSAGE_SEEN;
            break;
        case LINK_MESSAGE_SEED:
            Mt19937SetSeed(pMessage->wData);
            g_bLinkSeedReceived = 1;
            break;
        }
    }
    g_bLinkTick++;
}
