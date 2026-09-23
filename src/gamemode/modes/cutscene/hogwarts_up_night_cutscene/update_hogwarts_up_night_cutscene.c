#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "input.h"
#include "room.h"

// Arg2 counts frames. The layers scroll from frame 0x20 to 0x80; the cutscene
// ends at frame 0xC0 or on A/B/Select/Start, back in the current room.
void UpdateHogwartsUpNightCutscene(void)
{
    g_GameModeStackContext.dwCurrentGameModeArg2++;

    if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0x20)
    {
        sub_08007D14(0, 0, 0xFFFF0000);
        sub_08007D14(1, 0, 0xFFFEA070);
        sub_08007D14(2, 0, 0x10000);
    }
    else if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0x68)
    {
        DisableBg(1);
    }
    else if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0x80)
    {
        sub_08007D14(0, 0, 0);
        sub_08007D14(1, 0, 0);
        sub_08007D14(2, 0, 0);
    }

    if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0xC0
        || (g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
        PushGameMode_3(Overworld, 3, g_bCurrentRoomId, 0xFF);
}
