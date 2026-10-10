#include "types.h"
#include "mt19937.h"
#include "serial/serial.h"

// Applies the message received from each peer this round: key masks, idle markers and the RNG seed.
void ProcessSerialMessages(void)
{
    u32 i;
    SerialMessage *pMessage;

    g_dwSerialFlags &= ~SERIAL_FLAG_OWN_MESSAGE_SEEN;
    for (i = 0; i < g_bSerialPeerCount; i++)
    {
        pMessage = &g_aSerialRecvMessages[i];
        GetSerialPlayerId();
        if (pMessage->bSeq == g_abSerialLastRecvSeq[i] || pMessage->bType == SERIAL_MESSAGE_NONE)
            continue;

        g_abSerialLastRecvSeq[i] = pMessage->bSeq;
        g_awSerialKeysReceived[i] = 0;
        switch (pMessage->bType)
        {
        case SERIAL_MESSAGE_IDLE:
            g_awSerialKeysReceived[i] = 0xFF00;
            if (GetSerialPlayerId() == i)
                g_dwSerialFlags |= SERIAL_FLAG_OWN_MESSAGE_SEEN;
            break;
        case SERIAL_MESSAGE_KEYS:
            g_awSerialKeysReceived[i] = pMessage->wData;
            if (GetSerialPlayerId() == i)
                g_dwSerialFlags |= SERIAL_FLAG_OWN_MESSAGE_SEEN;
            break;
        case SERIAL_MESSAGE_SEED:
            Mt19937SetSeed(pMessage->wData);
            g_bSerialSeedReceived = 1;
            break;
        }
    }
    g_bSerialTick++;
}
