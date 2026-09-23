#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "game_save.h"
#include "in_game_menu.h"
#include "input.h"
#include "status_equip.h"

void UpdateStatusEquipItemSelect(void)
{
    u32 leave;

    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickBlendFadeOut_candidate();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 2;
        break;

    case 2:
        if (g_StatusEquipItemSelect.pItemList != NULL)
            sub_08027048();

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
                sub_08032138();
                g_StatusEquipItemSelect.nextMode = StatusEquipSlotSelect;
                g_GameModeStackContext.dwModeState = 3;
            }
        }
        break;

    case 3:
        sub_080321A8();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
            PushGameMode(g_StatusEquipItemSelect.nextMode);
        break;
    }
}
