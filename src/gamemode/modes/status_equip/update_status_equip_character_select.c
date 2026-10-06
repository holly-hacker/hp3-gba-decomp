#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "menu/in_game_menu.h"
#include "hw/input.h"
#include "menu/status_equip.h"

void UpdateStatusEquipCharacterSelect(void)
{
    u32 slot;
    u32 previousSlot;

    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
            g_GameModeStackContext.dwModeState = 2;
        break;

    case 2:
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            g_StatusEquipCharacterSelect.nextMode = g_StatusEquipNextMode;
            g_GameModeStackContext.dwModeState = 3;
            g_dwStatusEquipCharacter = StatusEquipSlotToCharacter(g_bStatusEquipCharacterSlot);
        }
        else if (g_wKeysPressed & KeyB)
        {
            PlaySoundById(2);
            g_StatusEquipCharacterSelect.nextMode = g_StatusEquipReturnMode;
            g_GameModeStackContext.dwModeState = 3;
        }
        else if (g_wKeysPressed & KeyLeft)
        {
            slot = g_bStatusEquipCharacterSlot;
            previousSlot = slot;
            do
            {
                if (slot != 0)
                    slot--;
                else
                    slot = 2;
            } while (g_StatusEquipCharacterSelect.adwSlotPresent[slot] == 0);

            if (slot != previousSlot)
                PlaySoundById(0);
            sub_08035D98(slot);
        }
        else if (g_wKeysPressed & KeyRight)
        {
            slot = g_bStatusEquipCharacterSlot;
            previousSlot = slot;
            do
            {
                if (slot < 2)
                    slot++;
                else
                    slot = 0;
            } while (g_StatusEquipCharacterSelect.adwSlotPresent[slot] == 0);

            if (slot != previousSlot)
                PlaySoundById(0);
            sub_08035D98(slot);
        }
        break;

    case 3:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            sub_08035DC0();
            g_GameModeStackContext.dwModeState = 4;
        }
        break;

    case 4:
        PushGameMode(g_StatusEquipCharacterSelect.nextMode);
        break;
    }
}
