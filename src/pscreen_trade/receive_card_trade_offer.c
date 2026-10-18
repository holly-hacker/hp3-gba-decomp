#include "serial.h"
#include "pscreen_trade.h"

// Link receive callback: the peer's word is its offer in the low byte and its ready flag in bit 8.
void ReceiveCardTradeOffer(u32 word, u32 playerId)
{
    CardTradeSide *pPeer;

    if (playerId != GetSerialPlayerId())
    {
        pPeer = &g_CardTradeState.aSides[CARD_TRADE_PEER];
        pPeer->bOffer = word;
        pPeer->bReady = (word >> 8) & 1;
    }
}
