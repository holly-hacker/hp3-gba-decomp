#include "types.h"
#include "sound.h"
#include "cheat_sound_test.h"
#include "modes.h"
#include "input.h"
#include "minigame_menu.h"

void UpdateCheatSoundTest(void)
{
    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorUpDown(&g_CheatSoundTestState.dwRow, 0, 1, 1, 0))
    {
        SetActorMoveTargetWithDuration(g_CheatSoundTestState.pCursorActor, 0x9C,
                                                  g_CheatSoundTestState.dwRow * 18 + 0x3A, 5);
    }

    if (StepCursorLeftRight(&g_CheatSoundTestState.adwSelection[g_CheatSoundTestState.dwRow],
                            0, g_CheatSoundTestState.dwRow != 0 ? 0x33 : 0xB2, 1, 0))
    {
        DrawCheatSoundTestValues();
        if (g_CheatSoundTestState.dwRow == 1)
        {
            if (g_bMusicPaused)
                StopMusic();
            if (g_CheatSoundTestState.dwMusicPlaying)
            {
                StopMusic();
                PlayMusicModule(g_CheatSoundTestState.adwSelection[g_CheatSoundTestState.dwRow]);
            }
        }
    }

    if (g_wKeysPressed & KeyA)
    {
        switch (g_CheatSoundTestState.dwRow)
        {
        case 0:
            if (g_CheatSoundTestState.nSoundHandle != CHEAT_SOUND_TEST_NO_HANDLE)
                StopSoundEffect(g_CheatSoundTestState.nSoundHandle);
            g_CheatSoundTestState.nSoundHandle = PlaySoundById(g_CheatSoundTestState.adwSelection[g_CheatSoundTestState.dwRow]);
            break;
        case 1:
            if (g_CheatSoundTestState.dwMusicPlaying == 0)
            {
                if (g_bMusicPaused)
                    ResumeMusic();
                else
                    PlayMusicModule(g_CheatSoundTestState.adwSelection[1]);
                g_CheatSoundTestState.dwMusicPlaying = 1;
            }
            else
            {
                PauseMusic();
                g_CheatSoundTestState.dwMusicPlaying = 0;
            }
            break;
        }
    }
    else if (g_wKeysPressed & KeyB)
    {
        if (g_CheatSoundTestState.dwMusicPlaying != 0 || g_bMusicPaused)
            StopMusic();
        PushGameMode_2(Cheat, 0, g_GameModeStackContext.dwCurrentGameModeArg2);
    }
}
