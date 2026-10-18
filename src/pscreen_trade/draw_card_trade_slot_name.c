#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "pscreen_trade.h"

void DrawCardTradeSlotName(u32 side, u32 card)
{
    const u8 *text;
    u32 column = side * 15;

    FillBgTilemapRect(2, column + 3, 9, 0xB, 3, 0);
    if (card != CARD_TRADE_NO_CARD)
    {
        SelectTextFont(2, 0, -1);
        text = GetDialogText(0x412 + card);  // "Fulbert the Fearful", ...
        PrintTextBox(side * CARD_TRADE_SLOT_NAME_TILES + CARD_TRADE_SLOT_NAME_TILE, column * 8 + 0x18, 0x48, 0x58, text, 0);
    }
}
