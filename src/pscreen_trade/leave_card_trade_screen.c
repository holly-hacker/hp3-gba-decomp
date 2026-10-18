#include "sound.h"
#include "modes.h"
#include "pause_menu.h"
#include "pscreen_trade.h"

void LeaveCardTradeScreen(void)
{
    g_CardTradeState.aSides[CARD_TRADE_LOCAL].bOffer = CARD_TRADE_NO_CARD;
    StartMenuFadeOut();
    g_GameModeStackContext.dwModeState = 4;
    g_GameModeStackContext.dwModeScratchA = 1;
    PlaySoundById(2);
}
