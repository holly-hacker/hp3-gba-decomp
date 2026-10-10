#include "types.h"
#include "menu/items_menu.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "menu/in_game_menu.h"
#include "input.h"
#include "menu/status_equip.h"

void UpdateStatusEquipItemSelect(void)
{
    u32 leave;

    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 2;
        break;

    case 2:
        if (g_StatusEquipItemSelect.pItemList != NULL)
            TickItemList();

        if (g_wKeysPressed & (KeyA | KeyB))
        {
            leave = 1;
            if (g_StatusEquipItemSelect.dwHasItems == 0)
                PlaySoundById(2);
            else if (g_wKeysPressed & KeyA)
            {
                if (!sub_080368E4())
                {
                    leave = 0;
                    PlaySoundById(3);
                }
            }
            else if (g_wKeysPressed & KeyB)
                PlaySoundById(2);

            if (leave)
            {
                StartMenuFadeOut();
                g_StatusEquipItemSelect.nextMode = StatusEquipSlotSelect;
                g_GameModeStackContext.dwModeState = 3;
            }
        }
        break;

    case 3:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
            PushGameMode(g_StatusEquipItemSelect.nextMode);
        break;
    }
}
