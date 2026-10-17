#include "modes.h"
#include "input.h"

void UpdateUnusedMinigame(void)
{
    if (g_wKeysPressed & 0xF)
        PushGameMode_2(MainMenu, 0, 0);
}
