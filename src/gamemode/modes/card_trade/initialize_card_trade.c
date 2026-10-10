#include "types.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "game/game_modes.h"
#include "hw/mem.h"
#include "menu/card_trade.h"
#include "menu/in_game_menu.h"
#include "menu/main_menu.h"
#include "gen/graphics/cutscenes.h"

void InitializeCardTrade(void)
{
    ClearResourceCacheSlots();

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
        SpawnCardTradeCardObjects();
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
