#include "types.h"
#include "game_modes.h"
#include "input.h"
#include "main_menu.h"

void UpdateNewGameMenu(void)
{
    g_GameModeStackContext.dwModeSubState_candidate += 2;

    switch (g_GameModeStackContext.dwModeState_candidate)
    {
    case 0:
        if (HandleSaveSlotInput_candidate())
            SelectNewGameSlot_candidate();
        break;

    case 1:
        if (g_wKeysPressed & KeyA)
        {
            ResolveOverwriteConfirmation_candidate();
        }
        else if (g_wKeysPressed & KeyB)
        {
            g_GameModeStackContext.dwModeScratchB_candidate = 0;
            ResolveOverwriteConfirmation_candidate();
        }
        else if (g_wKeysPressed & (KeyUp | KeyDown))
        {
            sub_0803227C();
        }
        break;
    }
}
