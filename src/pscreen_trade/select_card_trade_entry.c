#include "sound.h"
#include "modes.h"
#include "cursor.h"
#include "default_menu.h"
#include "screen_transitions.h"
#include "serial.h"
#include "pscreen_trade.h"
#include "pscreen_folio_universitas.h"

void SelectCardTradeEntry(void)
{
    switch (g_GameModeStackContext.dwModeScratchB)
    {
    case 0:  // "Choose Card"
        PlaySoundById(1);
        PlayScreenTransitionOutByIndex(0x3F, 2);
        PushGameMode_2(FolioUniversitas, FolioUniversitasPickCard,
                       g_CardTradeState.aSides[CARD_TRADE_LOCAL].bOffer != CARD_TRADE_NO_CARD
                           ? g_CardTradeState.aSides[CARD_TRADE_LOCAL].bOffer : 0);
        break;

    case 1:  // "Trade Cards"
        if (IsSerialUp() == 1
            && g_CardTradeState.aSides[CARD_TRADE_LOCAL].bOffer != g_CardTradeState.aSides[CARD_TRADE_PEER].bOffer)
        {
            SetMenuCursorVisible(g_pMenuCursorActor, 0);
            g_CardTradeState.aSides[CARD_TRADE_LOCAL].bReady = 1;
            g_CardTradeState.aSides[CARD_TRADE_LOCAL].bLocked = g_CardTradeState.aSides[CARD_TRADE_LOCAL].bOffer;
            g_CardTradeState.aSides[CARD_TRADE_PEER].bLocked = g_CardTradeState.aSides[CARD_TRADE_PEER].bOffer;
            ShowCardTradeMessage(0x8CA);  // "Ready for Trade..."
            g_GameModeStackContext.dwModeState = 5;
            g_GameModeStackContext.dwModeTimer = 3;
            PlaySoundById(1);
        }
        else
            PlaySoundById(3);
        break;

    case 2:  // "Exit"
        LeaveCardTradeScreen();
        break;
    }
}
