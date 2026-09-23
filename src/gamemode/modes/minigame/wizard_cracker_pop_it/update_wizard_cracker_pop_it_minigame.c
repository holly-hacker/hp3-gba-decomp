#include "types.h"
#include "audio.h"
#include "debug_menu.h"
#include "game_modes.h"
#include "input.h"
#include "minigame_menu.h"
#include "save.h"
#include "wizard_cracker_pop_it.h"

void UpdateWizardCrackerPopItMinigame(void)
{
    u32 score;

    sub_08033710();
    sub_080331D4();

    switch (g_GameModeStackContext.dwModeState)
    {
    case WizardCrackerPopItStateFadeIn:
        if (--g_GameModeStackContext.dwModeTimer == 0)
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStateWaitStart;
        break;
    case WizardCrackerPopItStateWaitStart:
        sub_08032E5C();
        if (g_wKeysPressed & KeyStart)
        {
            PlaySoundById(1);
            sub_08033C30();
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStatePauseMenu;
            g_GameModeStackContext.dwModeScratchB = 0;
        }
        else if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(0xA8);
            if (g_pWizardCrackerPopIt->dwUnk19C != 0)
            {
                sub_080330C8();
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateRoundSetup;
            }
        }
        break;
    case WizardCrackerPopItStateRoundSetup:
        sub_08032E5C();
        if (sub_08033B74())
        {
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStatePlaying;
            g_pWizardCrackerPopIt->bUnk18C = 0xAA;
        }
        break;
    case WizardCrackerPopItStateRoundWon:
        if (--g_GameModeStackContext.dwModeTimer == -1)
        {
            score = g_pWizardCrackerPopIt->dwScore;
            sub_08032AA8();
            g_pWizardCrackerPopIt->dwScore = score;
            if (score >
                g_saveManager.adwWizardCrackerPopItHighScores[g_GameModeStackContext.dwCurrentGameModeArg3])
                g_saveManager.adwWizardCrackerPopItHighScores[g_GameModeStackContext.dwCurrentGameModeArg3] =
                    score;

            sub_080075C0(3, 0, 8, 0x1E, 6, 0);
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStateFadeIn;
            g_GameModeStackContext.dwModeTimer = 8;
            g_pWizardCrackerPopIt->dwUnk1A4 = 0;
            sub_08033BE4();
        }
        break;
    case WizardCrackerPopItStateRoundLost:
        if (--g_GameModeStackContext.dwModeTimer == -1)
        {
            sub_08033CE0();
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStateResultsMenu;
            g_GameModeStackContext.dwModeScratchB = 0;
            sub_080328FC();
            g_pWizardCrackerPopIt->dwUnk1A4 = 0;
            sub_08033BE4();
        }
        break;
    case WizardCrackerPopItStatePlaying:
        sub_08032E5C();
        if (sub_08032CFC())
        {
            sub_08032B88();
            if (sub_0803296C() == 1)
            {
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateWaitStart;
                sub_08032894();
                sub_08033B28(g_pWizardCrackerPopIt->dwUnk190, g_pWizardCrackerPopIt->dwUnk194);
                g_pWizardCrackerPopIt->dwUnk1A4 = 0;
                sub_08033BE4();
            }
            else if (sub_08033CA0())
            {
                PlaySoundEffect_candidate(0x2B);
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateRoundWon;
                g_GameModeStackContext.dwModeTimer = 0x78;
            }
            else
            {
                PlaySoundEffect_candidate(0x2D);
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateRoundLost;
                g_GameModeStackContext.dwModeTimer = 0x28;
            }
        }
        break;
    case WizardCrackerPopItStatePauseMenu:
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            if (g_GameModeStackContext.dwModeScratchB == 0)
            {
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateWaitStart;
                sub_080075C0(3, 0, 8, 0x1E, 6, 0);
            }
            else if (g_GameModeStackContext.dwModeScratchB == 1)
            {
                sub_08032AA8();
                sub_080075C0(3, 0, 8, 0x1E, 6, 0);
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateFadeIn;
                g_GameModeStackContext.dwModeTimer = 8;
            }
            else
            {
                sub_08033D6C();
            }
        }
        else if (g_wKeysPressed & (KeyB | KeyStart))
        {
            PlaySoundById(2);
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStateWaitStart;
            sub_080075C0(3, 0, 8, 0x1E, 6, 0);
        }
        else if (StepWrappedSelectionVertical_candidate(&g_dwListMenuSelection, 0, 2, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    case WizardCrackerPopItStateResultsMenu:
        if (g_pWizardCrackerPopIt->dwScore >
            g_saveManager.adwWizardCrackerPopItHighScores[g_GameModeStackContext.dwCurrentGameModeArg3])
            g_saveManager.adwWizardCrackerPopItHighScores[g_GameModeStackContext.dwCurrentGameModeArg3] =
                g_pWizardCrackerPopIt->dwScore;

        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            if (g_GameModeStackContext.dwModeScratchB == 0)
            {
                sub_08032AA8();
                sub_080075C0(3, 0, 8, 0x1E, 6, 0);
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateFadeIn;
                g_GameModeStackContext.dwModeTimer = 8;
            }
            else
            {
                sub_08033D6C();
            }
        }
        else if (!(g_wKeysPressed & KeyB))
        {
            if (StepWrappedSelectionVertical_candidate(&g_GameModeStackContext.dwModeScratchB, 0, 1, 1, 0))
                PlaySoundById(0);
        }
        break;
    }
}
