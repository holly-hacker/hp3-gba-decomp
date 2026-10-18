#include "pscreen_trade.h"

void SetCardTradeSlotCard(u32 side, u32 card)
{
    CardTradeSide *pSide = &g_CardTradeState.aSides[side];

    if (pSide->bShownCard != card)
    {
        pSide->bShownCard = card;
        RespawnCardTradeCardActor(side, card);
        DrawCardTradeSlotName(side, card);
    }
}
