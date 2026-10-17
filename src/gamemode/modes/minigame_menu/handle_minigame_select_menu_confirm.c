#include "types.h"
#include "graphics/audio.h"
#include "modes.h"
#include "input.h"
#include "title.h"
#include "menu/minigame_menu.h"
#include "game/save.h"
#include "default_menu.h"
#include "minigame_difficulty_select.h"

void HandleMinigameSelectMenuConfirm(void)
{
    UpdateMenuScreen();

    switch (g_GameModeStackContext.dwModeState)
    {
    case 1:
        if (TickMinigameSwitchFadeOut_candidate())
            SwapMinigameSelection_candidate();
        break;

    case 2:
        TickMinigameSwitchFadeIn_candidate();
        break;

    case 0:
        if (StepCursorLeftRight(&g_GameModeStackContext.dwCurrentGameModeArg2, 0, 3, 1, 0))
        {
            SetActorMoveTargetWithDuration(g_pMenuCursorActor,
                                                      g_GameModeStackContext.dwCurrentGameModeArg2 * 0x20 + 0x48, 0x70, 8);
            BeginMinigameSwitchFade_candidate();
            g_GameModeStackContext.dwModeState = 1;
            PlaySoundById(0);
            break;
        }

        if (g_wKeysPressed & KeyA)
        {
            if ((g_GameModeStackContext.dwCurrentGameModeArg2 == 0
                     ? g_saveManager.header.bHeaderFlags.all & flWizardCrackerPopItUnlocked
                 : g_GameModeStackContext.dwCurrentGameModeArg2 == 1
                     ? g_saveManager.header.bHeaderFlags.all & flBuckbeakUnlocked
                 : g_GameModeStackContext.dwCurrentGameModeArg2 == 2
                     ? g_saveManager.header.bHeaderFlags.all & flBoggartUnlocked
                     : g_saveManager.header.bHeaderFlags.all & flTeaLeafDivinationUnlocked) != 0)
            {
                PlaySoundById(1);
                if (g_GameModeStackContext.dwCurrentGameModeArg2 == 3)
                {
                    if (!(g_saveManager.header.bHeaderFlags.all & flTeaLeafDivinationIntroShown))
                    {
                        g_saveManager.header.bHeaderFlags.all |= flTeaLeafDivinationIntroShown;
                        DisableKrawall();
                        SyncSaveHeaderIfDirty();
                        EnableKrawall();
                        PushGameMode_3(HelpTopicScreen, 6, 3, 0);
                    }
                    else
                    {
                        PushGameMode_3(DivinationTeaMinigame, 6, 0, 0);
                    }
                }
                else
                {
                    g_dwSelectedMinigame = g_GameModeStackContext.dwCurrentGameModeArg2;
                    PushGameMode_2(MinigameDifficultySelect, 6, g_GameModeStackContext.dwCurrentGameModeArg2);
                }
            }
            else
            {
                PlaySoundById(3);
            }
        }
        else if (g_wKeysPressed & KeyB)
        {
            PlaySoundById(2);
            PushGameMode(MainMenu);
            g_dwPendingGameMode.dwCurrentGameModeArg2 = MainMenuMiniGames;
        }
        break;
    }
}
