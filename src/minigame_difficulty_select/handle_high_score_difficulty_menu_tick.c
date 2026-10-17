#include "types.h"
#include "sound.h"
#include "modes.h"
#include "save.h"
#include "input.h"
#include "minigame_menu.h"
#include "minigame_difficulty_select.h"
#include "buckbeak_minigame.h"
#include "boggart_minigame.h"
#include "pop_it_minigame.h"
#include "default_menu.h"

static inline void MoveCursorToSelectedRow(void)
{
    Actor *pCursor = g_pMenuCursorActor;
    u32 row = g_GameModeStackContext.dwModeScratchB;
    s32 x = 0x74;
    s32 y;

    if (row <= 2)
        x = 0x60;

    if (g_GameModeStackContext.dwModeScratchB <= 2)
        y = g_GameModeStackContext.dwModeScratchB * 16 + 0x30;
    else
        y = g_GameModeStackContext.dwModeScratchB * 16 + 0x48;

    SetActorMoveTargetWithDuration(pCursor, x, y, 5);
}

void HandleHighScoreDifficultyMenuTick(void)
{
    u32 lastRow;
    s32 i;

    UpdateMenuScreen();

    if (g_wKeysPressed & (KeyUp | KeyDown))
    {
        lastRow = MINIGAME_DIFFICULTY_COUNT - 1;
        PlaySoundById(0);
        if (g_saveManager.options.aadwHighScores[g_dwSelectedMinigame][0] != 0
            || g_saveManager.options.aadwHighScores[g_dwSelectedMinigame][1] != 0
            || g_saveManager.options.aadwHighScores[g_dwSelectedMinigame][2] != 0)
            lastRow = MINIGAME_ERASE_SCORES_ROW;

        if (g_wKeysPressed & KeyUp)
        {
            sub_0802CB80(g_GameModeStackContext.dwModeScratchB, 1);
            g_GameModeStackContext.dwModeScratchB = g_GameModeStackContext.dwModeScratchB == 0
                ? lastRow
                : g_GameModeStackContext.dwModeScratchB - 1;
            sub_0802CB80(g_GameModeStackContext.dwModeScratchB, 6);
        }
        else if (g_wKeysPressed & KeyDown)
        {
            sub_0802CB80(g_GameModeStackContext.dwModeScratchB, 1);
            g_GameModeStackContext.dwModeScratchB = g_GameModeStackContext.dwModeScratchB < lastRow
                ? g_GameModeStackContext.dwModeScratchB + 1
                : 0;
            sub_0802CB80(g_GameModeStackContext.dwModeScratchB, 6);
        }

        if (g_GameModeStackContext.dwModeScratchB < MINIGAME_DIFFICULTY_COUNT)
            sub_0802CC44(g_GameModeStackContext.dwModeScratchB);

        MoveCursorToSelectedRow();
    }
    else if (g_wKeysPressed & KeyA)
    {
        PlaySoundById(1);
        if (g_GameModeStackContext.dwModeScratchB < MINIGAME_DIFFICULTY_COUNT)
        {
            switch (g_dwSelectedMinigame)
            {
            case 0:
                g_dwWizardCrackerPopItForceOverworldExit = 0;
                break;
            case 1:
                g_dwBuckbeakMinigameForceOverworldExit = 0;
                break;
            case 2:
                g_dwBoggartMinigameScriptFlag_candidate = 0;
                break;
            }

            if (g_dwSelectedMinigame <= 3)
                PushGameMode_3(g_aeMinigameDifficultyModes[g_dwSelectedMinigame], 6, g_dwSelectedMinigame,
                               g_GameModeStackContext.dwModeScratchB);
        }
        else
        {
            for (i = 0; i < MINIGAME_DIFFICULTY_COUNT; i++)
                g_saveManager.options.aadwHighScores[g_dwSelectedMinigame][i] = 0;

            sub_0802CB80(g_GameModeStackContext.dwModeScratchB, 1);
            g_GameModeStackContext.dwModeScratchB = 0;
            sub_0802CB80(g_GameModeStackContext.dwModeScratchB, 6);
            sub_0802CC44(g_GameModeStackContext.dwModeScratchB);
            MoveCursorToSelectedRow();
            SyncSaveOptionsPausingKrawall();
        }
    }
    else if (g_wKeysPressed & KeyB)
    {
        PlaySoundById(2);
        PushGameMode_2(MinigameMenu, 6, g_dwSelectedMinigame);
    }
}
