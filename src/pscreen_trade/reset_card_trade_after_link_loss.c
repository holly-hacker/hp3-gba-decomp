#include "modes.h"
#include "cursor.h"
#include "default_menu.h"
#include "pscreen_trade.h"

// Drops a trade in progress back to the menu and clears the peer's side.
void ResetCardTradeAfterLinkLoss(void)
{
    if (g_GameModeStackContext.dwModeState != 2)
    {
        SetMenuCursorVisible(g_pMenuCursorActor, 1);
        g_CardTradeState.aSides[CARD_TRADE_LOCAL].bReady = 0;
        g_CardTradeState.aSides[CARD_TRADE_LOCAL].bLocked = CARD_TRADE_NO_CARD;
        g_CardTradeState.aSides[CARD_TRADE_PEER].bLocked = CARD_TRADE_NO_CARD;
        ShowCardTradeMessage(CARD_TRADE_NO_MESSAGE);
        g_GameModeStackContext.dwModeState = 2;
        SetCardTradeSlotCard(CARD_TRADE_LOCAL, CARD_TRADE_NO_CARD);
    }

    g_CardTradeState.aSides[CARD_TRADE_PEER].bOffer = CARD_TRADE_NO_CARD;
    g_CardTradeState.aSides[CARD_TRADE_PEER].bReady = 0;
    SetCardTradeSlotCard(CARD_TRADE_PEER, CARD_TRADE_NO_CARD);
}
