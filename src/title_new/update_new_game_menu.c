#include "modes.h"
#include "input.h"
#include "title_load.h"
#include "title_new.h"
#include "pause_menu.h"

void UpdateNewGameMenu(void)
{
    g_GameModeStackContext.dwModeSubState += 2;

    switch (g_GameModeStackContext.dwModeState)
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
            g_GameModeStackContext.dwModeScratchB = 0;
            ResolveOverwriteConfirmation_candidate();
        }
        else if (g_wKeysPressed & (KeyUp | KeyDown))
        {
            MoveListMenuCursor();
        }
        break;
    }
}
