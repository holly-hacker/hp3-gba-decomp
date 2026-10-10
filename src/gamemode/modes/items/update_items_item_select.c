#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "menu/in_game_menu.h"
#include "input.h"
#include "menu/items_menu.h"
#include "menu/status_equip.h"

void UpdateItemsItemSelect(void)
{
    u32 item;

    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
        {
            SetAlphaBlendTargets(0, 1);
            g_GameModeStackContext.dwModeState = 2;
        }
        break;

    case 2:
        if (g_ItemsItemSelect.dwHasItems != 0)
        {
            TickItemList();
            if (g_wKeysPressed & KeyA)
            {
                if (sub_08039818())
                {
                    PlaySoundById(1);
                    item = GetItemListSelection();
                    SetItemUseItem(item);
                    if (sub_08026D34(item))
                    {
                        // Choose which party member uses it first.
                        g_ItemsItemSelect.nextMode = StatusEquipCharacterSelect;
                        g_StatusEquipReturnMode = ItemsItemSelect;
                        g_StatusEquipNextMode = QuantitySelectScreen;
                    }
                    else
                        g_ItemsItemSelect.nextMode = ItemUseScreen;

                    SetAlphaBlendTargets(0x14, 1);
                    g_GameModeStackContext.dwModeState = 3;
                }
                else
                    PlaySoundById(3);
            }
        }

        if ((g_wKeysPressed & KeyB) || ((g_wKeysPressed & KeyA) && g_ItemsItemSelect.dwHasItems == 0))
        {
            PlaySoundById(2);
            SetAlphaBlendTargets(0x14, 1);
            g_ItemsItemSelect.nextMode = ItemsSectionSelect;
            g_GameModeStackContext.dwModeState = 3;
        }
        break;

    case 3:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
            PushGameMode(g_ItemsItemSelect.nextMode);
        break;
    }
}
