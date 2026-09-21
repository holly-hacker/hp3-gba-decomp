#include "types.h"
#include "audio.h"
#include "game_modes.h"
#include "input.h"
#include "main_menu.h"
#include "minigame_menu.h"
#include "save.h"

void HandleMinigameSelectMenuConfirm(void)
{
    sub_0801E0D8();

    switch (g_GameModeStackContext.dwModeState_candidate)
    {
    case 1:
        if (TickMinigameSwitchFadeOut_candidate())
            SwapMinigameSelection_candidate();
        break;

    case 2:
        TickMinigameSwitchFadeIn_candidate();
        break;

    case 0:
        if (StepWrappedSelectionHorizontal_candidate(&g_GameModeStackContext.dwCurrentGameModeArg2, 0, 3, 1, 0))
        {
            SetObjectMoveTargetWithDuration_candidate(g_pMenuCursorObject,
                                                      g_GameModeStackContext.dwCurrentGameModeArg2 * 0x20 + 0x48, 0x70, 8);
            BeginMinigameSwitchFade_candidate();
            g_GameModeStackContext.dwModeState_candidate = 1;
            PlaySoundById(0);
            break;
        }

        if (g_wKeysPressed & KeyA)
        {
            if ((g_GameModeStackContext.dwCurrentGameModeArg2 == 0
                     ? g_saveManager.header.bHeaderFlags.all & flMinigame1Unlocked
                 : g_GameModeStackContext.dwCurrentGameModeArg2 == 1
                     ? g_saveManager.header.bHeaderFlags.all & flMinigame2Unlocked
                 : g_GameModeStackContext.dwCurrentGameModeArg2 == 2
                     ? g_saveManager.header.bHeaderFlags.all & flMinigame3Unlocked
                     : g_saveManager.header.bHeaderFlags.all & flMinigame4Unlocked) != 0)
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
