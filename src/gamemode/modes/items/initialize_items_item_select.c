#include "types.h"
#include "game/game_modes.h"
#include "menu/in_game_menu.h"
#include "menu/items_menu.h"
#include "menu/main_menu.h"
#include "font.h"
#include "text.h"

void InitializeItemsItemSelect(void)
{
    u8 *text;

    g_GameModeStackContext.dwModeState = 1;
    StartMenuFadeIn();
    BeginMenuScreen(0x531, 9, 0);

    g_ItemsItemSelect.dwHasItems = OpenFilteredItemList(g_ItemsItemSelect.dwFilter, 0x34, 0x36, 1, 0, 3, -1);
    if (g_ItemsItemSelect.dwHasItems != 0)
    {
        SetItemListCallbacks(sub_0803975C, sub_080397FC);
        sub_0803975C(GetItemListSelection());
    }
    else
    {
        SelectTextFont(2, 0, -1);
        text = GetDialogText(0x667);
        DrawTextLines(0x40, 0x78, 0x48, 0xC0, 0x20, &text, 1);
    }
}
