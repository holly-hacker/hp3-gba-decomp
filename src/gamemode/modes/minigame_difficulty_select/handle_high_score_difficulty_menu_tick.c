#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "game/save.h"
#include "hw/input.h"
#include "menu/main_menu.h"
#include "menu/minigame_menu.h"
#include "menu/minigame_difficulty_select.h"
#include "minigame/hippogriff_glide.h"
#include "minigame/riddikulus.h"
#include "minigame/wizard_cracker_pop_it.h"

static inline void MoveCursorToSelectedRow(void)
{
    Object *pCursor = g_pMenuCursorObject;
    u32 row = g_GameModeStackContext.dwModeScratchB;
    s32 x = 0x74;
    s32 y;

    if (row <= 2)
        x = 0x60;

    if (g_GameModeStackContext.dwModeScratchB <= 2)
        y = g_GameModeStackContext.dwModeScratchB * 16 + 0x30;
    else
        y = g_GameModeStackContext.dwModeScratchB * 16 + 0x48;

    SetObjectMoveTargetWithDuration_candidate(pCursor, x, y, 5);
}

void HandleHighScoreDifficultyMenuTick(void)
{
    u32 lastRow;
    s32 i;

    sub_0801E0D8();

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
                g_dwHippogriffForceOverworldExit = 0;
                break;
            case 2:
                g_dwRiddikulusMinigameScriptFlag_candidate = 0;
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
            sub_0802CDB8();
        }
    }
    else if (g_wKeysPressed & KeyB)
    {
        PlaySoundById(2);
        PushGameMode_2(MinigameMenu, 6, g_dwSelectedMinigame);
    }
}
