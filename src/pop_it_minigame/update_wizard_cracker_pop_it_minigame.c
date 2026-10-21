#include "types.h"
#include "background.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "save.h"
#include "pop_it_minigame.h"

void UpdateWizardCrackerPopItMinigame(void)
{
    u32 score;

    TickWizardCrackerPopItKinds();
    TickWizardCrackerPopItSelectionBlend();

    switch (g_GameModeStackContext.dwModeState)
    {
    case WizardCrackerPopItStateFadeIn:
        if (--g_GameModeStackContext.dwModeTimer == 0)
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStateSelect;
        break;
    case WizardCrackerPopItStateSelect:
        HandleWizardCrackerPopItCursorInput();
        if (g_wKeysPressed & KeyStart)
        {
            PlaySoundById(1);
            DrawWizardCrackerPopItPauseMenu();
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStatePauseMenu;
            g_GameModeStackContext.dwModeScratchB = 0;
        }
        else if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(0xA8);
            if (g_pWizardCrackerPopIt->dwSelectedCount != 0)
            {
                PopWizardCrackerPopItSelection();
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStatePopping;
            }
        }
        break;
    case WizardCrackerPopItStatePopping:
        HandleWizardCrackerPopItCursorInput();
        if (AreWizardCrackerPopItCrackersIdle())
        {
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStateSettling;
            g_pWizardCrackerPopIt->bLandSoundId = 0xAA;
        }
        break;
    case WizardCrackerPopItStateRoundWon:
        if (--g_GameModeStackContext.dwModeTimer == -1)
        {
            score = g_pWizardCrackerPopIt->dwScore;
            StartWizardCrackerPopItRound();
            g_pWizardCrackerPopIt->dwScore = score;
            if (score >
                g_saveManager.options.aadwHighScores[HighScoreWizardCrackerPopIt][g_GameModeStackContext.dwCurrentGameModeArg3])
                g_saveManager.options.aadwHighScores[HighScoreWizardCrackerPopIt][g_GameModeStackContext.dwCurrentGameModeArg3] =
                    score;

            FillBgTilemapRect(3, 0, 8, 0x1E, 6, 0);
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStateFadeIn;
            g_GameModeStackContext.dwModeTimer = 8;
            g_pWizardCrackerPopIt->dwPopBonus = 0;
            DrawWizardCrackerPopItScore();
        }
        break;
    case WizardCrackerPopItStateRoundLost:
        if (--g_GameModeStackContext.dwModeTimer == -1)
        {
            DrawWizardCrackerPopItResultsMenu();
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStateResultsMenu;
            g_GameModeStackContext.dwModeScratchB = 0;
            AddWizardCrackerPopItClearBonus();
            g_pWizardCrackerPopIt->dwPopBonus = 0;
            DrawWizardCrackerPopItScore();
        }
        break;
    case WizardCrackerPopItStateSettling:
        HandleWizardCrackerPopItCursorInput();
        if (SettleWizardCrackerPopItBoard())
        {
            RebuildWizardCrackerPopItGrid();
            if (HasWizardCrackerPopItMoves() == 1)
            {
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateSelect;
                ClampWizardCrackerPopItCursor();
                SelectWizardCrackerPopItGroup(g_pWizardCrackerPopIt->nCursorColumn, g_pWizardCrackerPopIt->nCursorRow);
                g_pWizardCrackerPopIt->dwPopBonus = 0;
                DrawWizardCrackerPopItScore();
            }
            else if (IsWizardCrackerPopItBoardClear())
            {
                PlayJingle(0x2B);
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateRoundWon;
                g_GameModeStackContext.dwModeTimer = 0x78;
            }
            else
            {
                PlayJingle(0x2D);
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
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateSelect;
                FillBgTilemapRect(3, 0, 8, 0x1E, 6, 0);
            }
            else if (g_GameModeStackContext.dwModeScratchB == 1)
            {
                StartWizardCrackerPopItRound();
                FillBgTilemapRect(3, 0, 8, 0x1E, 6, 0);
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateFadeIn;
                g_GameModeStackContext.dwModeTimer = 8;
            }
            else
            {
                QuitWizardCrackerPopItMinigame();
            }
        }
        else if (g_wKeysPressed & (KeyB | KeyStart))
        {
            PlaySoundById(2);
            g_GameModeStackContext.dwModeState = WizardCrackerPopItStateSelect;
            FillBgTilemapRect(3, 0, 8, 0x1E, 6, 0);
        }
        else if (StepCursorUpDown(&g_dwListMenuSelection, 0, 2, 1, 0))
        {
            PlaySoundById(0);
        }
        break;
    case WizardCrackerPopItStateResultsMenu:
        if (g_pWizardCrackerPopIt->dwScore >
            g_saveManager.options.aadwHighScores[HighScoreWizardCrackerPopIt][g_GameModeStackContext.dwCurrentGameModeArg3])
            g_saveManager.options.aadwHighScores[HighScoreWizardCrackerPopIt][g_GameModeStackContext.dwCurrentGameModeArg3] =
                g_pWizardCrackerPopIt->dwScore;

        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            if (g_GameModeStackContext.dwModeScratchB == 0)
            {
                StartWizardCrackerPopItRound();
                FillBgTilemapRect(3, 0, 8, 0x1E, 6, 0);
                g_GameModeStackContext.dwModeState = WizardCrackerPopItStateFadeIn;
                g_GameModeStackContext.dwModeTimer = 8;
            }
            else
            {
                QuitWizardCrackerPopItMinigame();
            }
        }
        else if (!(g_wKeysPressed & KeyB))
        {
            if (StepCursorUpDown(&g_GameModeStackContext.dwModeScratchB, 0, 1, 1, 0))
                PlaySoundById(0);
        }
        break;
    }
}
