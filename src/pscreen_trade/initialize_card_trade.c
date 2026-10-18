#include "modes.h"
#include "mem.h"
#include "pscreen_trade.h"
#include "pause_menu.h"
#include "gen/graphics/cutscenes.h"
#include "default_menu.h"
#include "screen_transitions.h"
#include "serial.h"

void InitializeCardTrade(void)
{
    ClearObjPaletteSlots();

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 1)
    {
        g_GameModeStackContext.dwModeState = 2;
        g_CardTradeState.aSides[CARD_TRADE_LOCAL].bOffer = g_GameModeStackContext.dwCurrentGameModeArg2;
        g_CardTradeState.aSides[CARD_TRADE_LOCAL].bShownCard = CARD_TRADE_NO_CARD;
        g_CardTradeState.aSides[CARD_TRADE_PEER].bShownCard = CARD_TRADE_NO_CARD;
        BeginPauseMenuScreen(0);
        BuildListMenu(&g_CardTradeMenuDefinition);
        LoadMenuScreenOverlay(gCardTradeOverlay, 0, 0);
        RefreshCardTradeSlots();
        SpawnCardTradeReadyIcons();
        PlayScreenTransitionInByIndex(0x3F, 2);
    }
    else
    {
        g_GameModeStackContext.dwModeState = 0;
        memset(&g_CardTradeState, 0, sizeof(CardTradeState));
        g_CardTradeState.aSides[CARD_TRADE_LOCAL].bOffer = CARD_TRADE_NO_CARD;
        g_CardTradeState.aSides[CARD_TRADE_PEER].bOffer = CARD_TRADE_NO_CARD;
        g_CardTradeState.aSides[CARD_TRADE_LOCAL].bShownCard = CARD_TRADE_NO_CARD;
        g_CardTradeState.aSides[CARD_TRADE_PEER].bShownCard = CARD_TRADE_NO_CARD;
        StartMenuOverlayFadeIn();
        LoadMenuScreenOverlay(gCardTradeOverlay, 0, 0);
    }

    SetSerialCallbacks(ReceiveCardTradeOffer, GetCardTradeSendWord);
    InitSerialSession();
    StartSerialConnection(2);
    g_CardTradeState.dwStatus = 1;
}
