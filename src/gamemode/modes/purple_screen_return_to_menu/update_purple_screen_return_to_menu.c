#include "types.h"
#include "game/game_modes.h"
#include "input.h"

void UpdatePurpleScreenReturnToMenu(void)
{
    if (g_wKeysPressed & 0xF)
        PushGameMode_2(MainMenu, 0, 0);
}
