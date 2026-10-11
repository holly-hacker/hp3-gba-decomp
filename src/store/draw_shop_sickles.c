#include "types.h"
#include "game/save.h"
#include "font.h"
#include "text.h"
#include "menu/dialog.h"
#include "menu/menu.h"
#include "shop.h"

void DrawShopSickles(void)
{
    u8 *text;

    ClearShopSicklesBox();
    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(3, 0, -1);
    SetTextMacro1Number(GetSickles());
    text = GetDialogText(0x53E);  // "Sickles @1"
    DrawTextLines(0x40, 0xE, 0x88, 0xC0, 0x18, &text, 0);
    SetTextTargetFromBgControl(g_dwFredAndGeorgesShopBg1Control);
}
