#include "types.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "tea_leaves_minigame.h"

void UpdateDivinationTeaPauseMenu(void)
{
    if (g_wKeysPressed & KeyA)
    {
        PlaySoundById(1);
        switch (g_GameModeStackContext.dwModeScratchB)
        {
        case 0:
            ResumeDivinationTeaMinigame();
            break;
        case 1:
            PushGameMode_2(MinigameMenu, 6, 3);
            break;
        }
    }
    else if (g_wKeysPressed & (KeyB | KeyStart))
    {
        PlaySoundById(2);
        ResumeDivinationTeaMinigame();
    }
    else if (StepCursorUpDown(&g_dwListMenuSelection, 0, 1, 1, 0))
    {
        PlaySoundById(0);
    }
}
