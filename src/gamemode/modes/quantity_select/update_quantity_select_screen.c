#include "types.h"
#include "game/items.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "graphics/audio.h"
#include "hw/input.h"
#include "menu/in_game_menu.h"
#include "menu/items_menu.h"
#include "menu/quantity_select.h"

void UpdateQuantitySelectScreen(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 2;
        break;

    case 2:
        if (g_wKeysPressed & KeyLeft)
        {
            if (g_GameModeStackContext.dwModeScratchB > 1)
            {
                g_GameModeStackContext.dwModeScratchB--;
                sub_0803950C();
                PlaySoundById(0);
            }
        }
        else if (g_wKeysPressed & KeyRight)
        {
            if (g_GameModeStackContext.dwModeScratchB < GetItemQuantity(g_dwItemUseItem))
            {
                g_GameModeStackContext.dwModeScratchB++;
                sub_0803950C();
                PlaySoundById(0);
            }
        }
        else if (g_wKeysPressed & KeyA)
        {
            g_dwItemUseQuantity = g_GameModeStackContext.dwModeScratchB;
            g_GameModeStackContext.dwCurrentGameModeArg2 = ItemUseScreen;
            g_GameModeStackContext.dwModeState = 3;
        }
        else if (g_wKeysPressed & KeyB)
        {
            g_GameModeStackContext.dwCurrentGameModeArg2 = StatusEquipCharacterSelect;
            g_GameModeStackContext.dwModeState = 3;
        }
        break;

    case 3:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            sub_08039564();
            PushGameMode(g_GameModeStackContext.dwCurrentGameModeArg2);
        }
        break;
    }
}
