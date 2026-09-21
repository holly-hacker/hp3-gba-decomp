#include "types.h"
#include "audio.h"
#include "battle.h"
#include "display.h"
#include "game_modes.h"
#include "game_save.h"
#include "in_game_menu.h"
#include "input.h"
#include "main_menu.h"

void UpdateInGameMenu(void)
{
    sub_0801E0D8();

    switch (g_GameModeStackContext.dwModeState_candidate)
    {
    case 0:
    case 1:
        TickBlendFadeOut_candidate();
        if (g_GameModeStackContext.dwModeSubState_candidate == 0)
        {
            if (g_GameModeStackContext.dwModeState_candidate == 0)
            {
                g_GameModeStackContext.dwModeState_candidate = 1;
                sub_080320A4();
                BuildListMenu_candidate(g_InGameMenuDefinition);
            }
            else
                g_GameModeStackContext.dwModeState_candidate = 2;
        }
        break;

    case 2:
        if (g_wKeysPressed & KeyA)
        {
            if (g_GameModeStackContext.dwModeScratchB_candidate == 0)
                sub_080323AC();
            SelectInGameMenuEntry_candidate();
        }
        else if (g_wKeysPressed & (KeyUp | KeyDown))
        {
            sub_0803227C();
        }
        else if (g_wKeysPressed & (KeyB | KeyStart))
        {
            PlaySoundById(2);
            PushGameMode_2(Overworld, 2, g_bCurrentRoomId);
        }
        break;

    case 3:
    case 4:
        sub_080321A8();
        if (g_GameModeStackContext.dwModeSubState_candidate == 0x10)
        {
            sub_0803232C();
            if (g_GameModeStackContext.dwModeState_candidate == 3)
            {
                g_GameModeStackContext.dwModeState_candidate = 4;
                sub_0803217C();
            }
            else
            {
                if (g_aInGameMenuEntries[g_GameModeStackContext.dwModeScratchB_candidate].dwImmediate != 0)
                    g_dwInGameMenuReturnMode = InGameMenu;
                else
                    g_dwInGameMenuReturnMode = InGameMenuFadeIn;

                if (g_GameModeStackContext.dwModeScratchB_candidate == 0)
                    g_dwInGameMenuSubModeArg = 0xE;
                else
                    g_dwInGameMenuSubModeArg = 0;

                PushGameMode(g_aInGameMenuEntries[g_GameModeStackContext.dwModeScratchB_candidate].mode);
            }
        }
        break;
    }
}
