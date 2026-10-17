#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "modes.h"
#include "input.h"
#include "overworld/room.h"
#include "time_skip_cutscene.h"
#include "map.h"

// Arg2 counts frames. The layers scroll from frame 0x20 to 0x80; the cutscene
// ends at frame 0xC0 or on A/B/Select/Start, back in the current room.
void UpdateHogwartsUpNightCutscene(void)
{
    g_GameModeStackContext.dwCurrentGameModeArg2++;

    if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0x20)
    {
        SetBgScrollStep(0, 0, 0xFFFF0000);
        SetBgScrollStep(1, 0, 0xFFFEA070);
        SetBgScrollStep(2, 0, 0x10000);
    }
    else if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0x68)
    {
        DisableBg(1);
    }
    else if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0x80)
    {
        SetBgScrollStep(0, 0, 0);
        SetBgScrollStep(1, 0, 0);
        SetBgScrollStep(2, 0, 0);
    }

    if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0xC0
        || (g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
        PushGameMode_3(Overworld, 3, g_bCurrentRoomId, 0xFF);
}
