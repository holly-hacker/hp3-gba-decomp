#include "types.h"
#include "particles.h"
#include "modes.h"
#include "mem.h"
#include "pscreen_trade.h"
#include "pause_menu.h"
#include "gen/graphics/cutscenes.h"
#include "default_menu.h"
#include "screen_transitions.h"

void InitializeCardTrade(void)
{
    ClearObjPaletteSlots();

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 1)
    {
        g_GameModeStackContext.dwModeState = 2;
        g_CardTradeState.bLocalOffer = g_GameModeStackContext.dwCurrentGameModeArg2;
        g_CardTradeState.bUnk07 = CARD_TRADE_NO_CARD;
        g_CardTradeState.bUnk0B = CARD_TRADE_NO_CARD;
        BeginPauseMenuScreen(0);
        BuildListMenu(&g_CardTradeMenuDefinition);
        LoadMenuScreenOverlay(gCardTradeOverlay, 0, 0);
        RefreshCardTradeSlots();
        SpawnCardTradeCardActors();
        PlayScreenTransitionInByIndex(0x3F, 2);
    }
    else
    {
        g_GameModeStackContext.dwModeState = 0;
        memset(&g_CardTradeState, 0, sizeof(CardTradeState));
        g_CardTradeState.bLocalOffer = CARD_TRADE_NO_CARD;
        g_CardTradeState.bPeerOffer = CARD_TRADE_NO_CARD;
        g_CardTradeState.bUnk07 = CARD_TRADE_NO_CARD;
        g_CardTradeState.bUnk0B = CARD_TRADE_NO_CARD;
        StartMenuOverlayFadeIn();
        LoadMenuScreenOverlay(gCardTradeOverlay, 0, 0);
    }

    SetSerialCallbacks(ReceiveCardTradeOffer, GetCardTradeSendWord);
    InitSerialSession();
    StartSerialConnection(2);
    g_CardTradeState.dwStatus = 1;
}
