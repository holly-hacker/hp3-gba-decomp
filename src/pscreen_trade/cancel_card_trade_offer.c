#include "modes.h"
#include "cursor.h"
#include "default_menu.h"
#include "pscreen_trade.h"

void CancelCardTradeOffer(void)
{
    SetMenuCursorVisible(g_pMenuCursorActor, 1);
    g_CardTradeState.aSides[CARD_TRADE_LOCAL].bReady = 0;
    g_CardTradeState.aSides[CARD_TRADE_LOCAL].bLocked = CARD_TRADE_NO_CARD;
    g_CardTradeState.aSides[CARD_TRADE_PEER].bLocked = CARD_TRADE_NO_CARD;
    ShowCardTradeMessage(CARD_TRADE_NO_MESSAGE);
    g_GameModeStackContext.dwModeState = 2;
}
