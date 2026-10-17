#include "types.h"
#include "background.h"
#include "game/items.h"
#include "graphics/display.h"
#include "font.h"
#include "text.h"
#include "dialog.h"
#include "store.h"
#include "items.h"

void DrawShopBuyPrice(u32 item)
{
    const u8 *text;

    ClearBgTilemapRect(1, 0x11, 0x10, 0xC, 3);
    SetTextTargetFromBgControl(g_dwFredAndGeorgesShopBg1Control);
    SelectTextFont(1, 0, -1);
    SetTextMacro1Number(GetItemBuyPrice(item));
    text = GetDialogText(0x548);  // "Price: @1 Sickles"
    DrawTextLines(0x61, 0xDF, 0x84, 0x50, 0x20, &text, 2);
}
