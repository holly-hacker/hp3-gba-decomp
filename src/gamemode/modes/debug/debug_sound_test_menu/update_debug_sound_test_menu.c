#include "types.h"
#include "audio.h"
#include "debug_menu.h"
#include "game_modes.h"
#include "input.h"
#include "minigame_menu.h"

void UpdateDebugSoundTestMenu(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepWrappedSelectionVertical_candidate(&g_DebugSoundTestState.dwRow, 0, 1, 1, 0))
    {
        SetObjectMoveTargetWithDuration_candidate(g_DebugSoundTestState.pCursorObject, 0x9C,
                                                  g_DebugSoundTestState.dwRow * 18 + 0x3A, 5);
    }

    if (StepWrappedSelectionHorizontal_candidate(&g_DebugSoundTestState.adwSelection[g_DebugSoundTestState.dwRow],
                                                 0, g_DebugSoundTestState.dwRow != 0 ? 0x33 : 0xB2, 1, 0))
    {
        sub_0800B9BC();
        if (g_DebugSoundTestState.dwRow == 1)
        {
            if (g_bMusicPaused)
                StopMusic();
            if (g_DebugSoundTestState.dwMusicPlaying)
            {
                StopMusic();
                PlayMusicModule(g_DebugSoundTestState.adwSelection[g_DebugSoundTestState.dwRow]);
            }
        }
    }

    if (g_wKeysPressed & KeyA)
    {
        switch (g_DebugSoundTestState.dwRow)
        {
        case 0:
            if (g_DebugSoundTestState.nSoundHandle != DEBUG_SOUND_TEST_NO_HANDLE)
                StopSoundEffect(g_DebugSoundTestState.nSoundHandle);
            g_DebugSoundTestState.nSoundHandle = PlaySoundById(g_DebugSoundTestState.adwSelection[g_DebugSoundTestState.dwRow]);
            break;
        case 1:
            if (g_DebugSoundTestState.dwMusicPlaying == 0)
            {
                if (g_bMusicPaused)
                    ResumeMusic();
                else
                    PlayMusicModule(g_DebugSoundTestState.adwSelection[1]);
                g_DebugSoundTestState.dwMusicPlaying = 1;
            }
            else
            {
                PauseMusic();
                g_DebugSoundTestState.dwMusicPlaying = 0;
            }
            break;
        }
    }
    else if (g_wKeysPressed & KeyB)
    {
        if (g_DebugSoundTestState.dwMusicPlaying != 0 || g_bMusicPaused)
            StopMusic();
        PushGameMode_2(DebugMenuMain, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
}
