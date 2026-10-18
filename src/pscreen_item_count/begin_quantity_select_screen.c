#include "types.h"
#include "pscreen_items.h"
#include "pscreen_item_count.h"
#include "font.h"
#include "text.h"
#include "cursor.h"
#include "default_menu.h"
#include "items.h"

void BeginQuantitySelectScreen(void)
{
    const u8 *text;
    Actor *pArrow;

    BeginMenuScreen(0x531, 9, 0);  // "Items"
    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(2, 0, -1);
    SetTextMacro1String(GetDialogText(GetRewardNameStringId_candidate(g_dwItemUseItem)));
    SetTextMacro2Number(GetItemQuantity(g_dwItemUseItem));
    text = GetDialogText(0x404);  // "How many potions do you want to use (max @2) ?"
    DrawTextLines(0x60, 0x78, 0x40, 0xA0, 0x18, &text, 1);
    DrawSelectedQuantity();

    pArrow = SpawnMenuCursorActor(5);
    SetMenuCursorPosition(pArrow, 0x60, 0x66);
    pArrow->oam.objMode = 1;
    pArrow = SpawnMenuCursorActor(5);
    SetMenuCursorPosition(pArrow, 0x90, 0x66);
    pArrow->oam.hFlip = 1;
    pArrow->oam.objMode = 1;
}
