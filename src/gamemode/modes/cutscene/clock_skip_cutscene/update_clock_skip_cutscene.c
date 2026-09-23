#include "types.h"
#include "battle.h"
#include "game_modes.h"
#include "input.h"
#include "room_script.h"

// Arg2 counts frames. After 0x85 frames, or on A/B/Select/Start, leaves for the
// overworld: in room 0x28 by exit 6, elsewhere in the current room.
void UpdateClockSkipCutscene(void)
{
    g_GameModeStackContext.dwCurrentGameModeArg2++;

    if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0x85
        || (g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
    {
        if (g_bCurrentRoomId == 0x28)
        {
            g_abRoomScriptExitParams_candidate[0] = 0;
            PushGameMode_2(Overworld, 0, 6);
            g_dwGameModeFlags |= 0x80000000;
        }
        else
        {
            PushGameMode_3(Overworld, 3, g_bCurrentRoomId, 0xFF);
        }
    }
}
