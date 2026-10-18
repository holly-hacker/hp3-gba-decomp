#include "pscreen_trade.h"

// Link send callback; see ReceiveCardTradeOffer.
u32 GetCardTradeSendWord(void)
{
    CardTradeSide *pLocal = &g_CardTradeState.aSides[CARD_TRADE_LOCAL];

    return 0xA000 | ((pLocal->bReady & 1) << 8) | pLocal->bOffer;
}
