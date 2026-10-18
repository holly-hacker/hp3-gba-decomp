#include "background.h"
#include "font.h"
#include "text.h"
#include "pscreen_trade.h"

void ShowCardTradeMessage(u32 textId)
{
    FillBgTilemapRect(2, 1, 0x12, 0x1C, 2, 0);
    if (textId != CARD_TRADE_NO_MESSAGE)
    {
        SelectTextFont(2, 6, -1);
        PrintTextBox(CARD_TRADE_MESSAGE_TILE, 0x78, 0x90, 0xE0, GetDialogText(textId), 1);
    }
}
