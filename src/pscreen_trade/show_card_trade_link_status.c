#include "background.h"
#include "font.h"
#include "text.h"
#include "pscreen_trade.h"

// Redraws only when the link comes up or goes down.
void ShowCardTradeLinkStatus(u32 linkUp)
{
    if (linkUp == 1)
    {
        if (g_CardTradeState.dwStatus == 0)
            FillBgTilemapRect(2, 0x10, 0xD, 0xD, 4, 0);
    }
    else if (g_CardTradeState.dwStatus == 1)
    {
        SelectTextFont(2, 0, -1);
        PrintTextBox(CARD_TRADE_LINK_STATUS_TILE, 0xB4, 0x68, 0x68, GetDialogText(0x653), 1);  // "Waiting for connection."
    }

    g_CardTradeState.dwStatus = linkUp;
}
