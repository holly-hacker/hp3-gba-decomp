#include "types.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "graphics/display.h"
#include "hw/input.h"
#include "hw/mem.h"
#include "menu/in_game_menu.h"
#include "menu/owl_name_select.h"

void UpdateOwlNameSelect(void)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case 0:
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
        {
            if (g_GameModeStackContext.dwModeState == 0)
            {
                g_GameModeStackContext.dwModeSubState = 0x10;
                SetAlphaBlendTargets(0x14, 0xB);
                SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                                          g_GameModeStackContext.dwModeSubState);
                EnableBg(2);
                SetDispcntFlag(0x1000);
                g_GameModeStackContext.dwModeState = 1;
            }
            else
                g_GameModeStackContext.dwModeState = 2;
        }
        break;

    case 2:
        if (g_wKeysPressed & KeyA)
            sub_080306B8();
        else if (g_wKeysPressed & KeyB)
            sub_080306F0();
        else if (g_wKeysPressed & (KeyRight | KeyLeft))
            sub_08030478();
        break;

    case 3:
    case 4:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            if (g_GameModeStackContext.dwModeScratchA == 0)
            {
                if (g_GameModeStackContext.dwModeState == 4)
                {
                    g_GameModeStackContext.dwCurrentGameModeArg1 = 1;
                    sub_080305F0();
                    sub_08030644();
                    g_GameModeStackContext.dwModeState = 1;
                }
                else
                    PushGameMode(OwlCareMinigame);
            }
            else if (g_GameModeStackContext.dwModeState == 4)
            {
                if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
                {
                    ClearBgTilemap(2);
                    sub_08007434(0x1000);
                    FreeAllObjects(&g_ActiveObjectListState.pHead);
                    g_GameModeStackContext.dwModeSubState = 0;
                    SetAlphaBlendTargets(8, 3);
                    SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                                              g_GameModeStackContext.dwModeSubState);
                    g_GameModeStackContext.dwModeState = 3;
                }
                else
                {
                    g_GameModeStackContext.dwCurrentGameModeArg1 = 0;
                    sub_080305F0();
                    sub_08030644();
                    g_GameModeStackContext.dwModeState = 1;
                }
            }
            else
            {
                SetDispcntFlag(0x1000);
                PushGameMode(Connectivity);
            }
        }
        break;
    }
}
