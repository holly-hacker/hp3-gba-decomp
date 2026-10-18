#include "types.h"
#include "font.h"
#include "text.h"
#include "default_menu.h"
#include "pscreen_items.h"

void DrawItemUseResult(u32 textId)
{
    const u8 *text;

    BeginMenuScreen(0x531, 9, 0);  // "Items"
    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(2, 0, -1);
    text = GetDialogText(textId);
    DrawTextLines(0x60, 0x78, 0x48, 0xC0, 0x18, &text, 1);
}
