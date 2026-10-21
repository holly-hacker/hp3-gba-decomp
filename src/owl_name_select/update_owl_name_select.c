#include "background.h"
#include "modes.h"
#include "input.h"
#include "actor.h"
#include "pause_menu.h"
#include "owl_name_select.h"
#include "screen_transitions.h"

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
            ConfirmOwlNameSelectPage();
        else if (g_wKeysPressed & KeyB)
            CancelOwlNameSelectPage();
        else if (g_wKeysPressed & (KeyRight | KeyLeft))
            StepOwlNameSelectChoice();
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
                    DrawOwlNameSelectHeading();
                    DrawOwlNameSelectChoice();
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
                    ClearDispcntFlag(0x1000);
                    FreeAllActors(&g_ActiveActorListState.pHead);
                    g_GameModeStackContext.dwModeSubState = 0;
                    SetAlphaBlendTargets(8, 3);
                    SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeSubState,
                                              g_GameModeStackContext.dwModeSubState);
                    g_GameModeStackContext.dwModeState = 3;
                }
                else
                {
                    g_GameModeStackContext.dwCurrentGameModeArg1 = 0;
                    DrawOwlNameSelectHeading();
                    DrawOwlNameSelectChoice();
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
