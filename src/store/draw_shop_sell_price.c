#include "types.h"
#include "game/items.h"
#include "graphics/display.h"
#include "font.h"
#include "graphics/text.h"
#include "menu/dialog.h"
#include "shop.h"

void DrawShopSellPrice(u32 item)
{
    u8 *text;

    ClearBgTilemapRect(1, 0x11, 0x10, 0xC, 3);
    SetTextTargetFromBgControl(g_dwFredAndGeorgesShopBg1Control);
    SelectTextFont(1, 0, -1);
    SetTextMacro1Number(GetItemSellPrice(item));
    text = GetDialogText(0x547);  // "Sell price: @1 Sickles"
    DrawTextLines(0x61, 0xDF, 0x84, 0x50, 0x20, &text, 2);
}
