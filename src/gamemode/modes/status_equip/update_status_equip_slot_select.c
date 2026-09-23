#include "types.h"
#include "audio.h"
#include "display.h"
#include "game_modes.h"
#include "game_save.h"
#include "in_game_menu.h"
#include "input.h"
#include "status_equip.h"

void UpdateStatusEquipSlotSelect(void)
{
    s32 i;

    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        TickBlendFadeOut_candidate();
        if (g_GameModeStackContext.dwModeSubState == 0)
        {
            SetAlphaBlendTargets(0, 1);
            SetAlphaBlendCoefficients(0, 16);
            sub_0803A3A0();
            g_GameModeStackContext.dwModeState = 2;
        }
        break;

    case 2:
        // Fade the slot contents in.
        g_GameModeStackContext.dwModeSubState++;
        SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState,
                                  16 - g_GameModeStackContext.dwModeSubState);
        for (i = 0; i < 6; i++)
        {
            if (g_StatusEquipSlotSelect.apSlotItems[i] != NULL)
                sub_08026FE0(g_StatusEquipSlotSelect.apSlotItems[i],
                             g_GameModeStackContext.dwModeSubState);
        }
        if (g_GameModeStackContext.dwModeSubState == 8)
            g_GameModeStackContext.dwModeState = 3;
        break;

    case 3:
        if (g_wKeysPressed & KeyA)
        {
            if (sub_0803A678())
            {
                sub_080368CC(g_aStatusEquipSlots[g_bStatusEquipSlot].dwType);
                g_StatusEquipSlotSelect.nextMode = StatusEquipItemSelect;
                g_GameModeStackContext.dwModeState = 4;
            }
            else
                PlaySoundById(3);
        }
        else if (g_wKeysPressed & KeyB)
        {
            PlaySoundById(2);
            g_StatusEquipSlotSelect.nextMode = StatusEquipCharacterSelectLastCursor;
            g_GameModeStackContext.dwModeState = 4;
        }
        else if (g_wKeysPressed & KeyUp)
        {
            PlaySoundById(0);
            g_bStatusEquipSlot = g_aStatusEquipSlots[g_bStatusEquipSlot].bUp;
            sub_0803A630();
            sub_0803A590();
        }
        else if (g_wKeysPressed & KeyDown)
        {
            PlaySoundById(0);
            g_bStatusEquipSlot = g_aStatusEquipSlots[g_bStatusEquipSlot].bDown;
            sub_0803A630();
            sub_0803A590();
        }
        else if (g_wKeysPressed & KeyLeft)
        {
            PlaySoundById(0);
            g_bStatusEquipSlot = g_aStatusEquipSlots[g_bStatusEquipSlot].bLeft;
            sub_0803A630();
            sub_0803A590();
        }
        else if (g_wKeysPressed & KeyRight)
        {
            PlaySoundById(0);
            g_bStatusEquipSlot = g_aStatusEquipSlots[g_bStatusEquipSlot].bRight;
            sub_0803A630();
            sub_0803A590();
        }
        break;

    case 4:
        // Fade the slot contents out.
        g_GameModeStackContext.dwModeSubState--;
        SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeSubState,
                                  16 - g_GameModeStackContext.dwModeSubState);
        for (i = 0; i < 6; i++)
        {
            if (g_StatusEquipSlotSelect.apSlotItems[i] != NULL)
                sub_08026FE0(g_StatusEquipSlotSelect.apSlotItems[i],
                             g_GameModeStackContext.dwModeSubState);
        }
        if (g_GameModeStackContext.dwModeSubState == 0)
        {
            sub_0803A534();
            g_GameModeStackContext.dwModeState = 5;
        }
        break;

    case 5:
        if (g_GameModeStackContext.dwModeSubState == 0)
        {
            SetAlphaBlendCoefficients(16, 0);
            SetAlphaBlendTargets(0x14, 1);
        }
        sub_080321A8();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            sub_0803A604();
            g_GameModeStackContext.dwModeState = 6;
        }
        break;

    case 6:
        PushGameMode(g_StatusEquipSlotSelect.nextMode);
        break;
    }
}
