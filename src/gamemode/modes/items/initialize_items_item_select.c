#include "types.h"
#include "game_modes.h"
#include "in_game_menu.h"
#include "items_menu.h"
#include "main_menu.h"
#include "text.h"

void InitializeItemsItemSelect(void)
{
    u8 *text;

    g_GameModeStackContext.dwModeState = 1;
    sub_080320A4();
    sub_0801E05C(0x531, 9, 0);

    g_ItemsItemSelect.dwHasItems = sub_08027AF4(g_ItemsItemSelect.dwFilter, 0x34, 0x36, 1, 0, 3, -1);
    if (g_ItemsItemSelect.dwHasItems != 0)
    {
        sub_08027C08(sub_0803975C, sub_080397FC);
        sub_0803975C(sub_08027BDC());
    }
    else
    {
        SelectTextFont(2, 0, -1);
        text = GetDialogText(0x667);
        DrawTextLines(0x40, 0x78, 0x48, 0xC0, 0x20, &text, 1);
    }
}
