#include "modes.h"
#include "input.h"
#include "time_skip_cutscene.h"
#include "hero.h"
#include "main.h"
#include "map.h"

// Arg2 counts frames. After 0x85 frames, or on A/B/Select/Start, leaves for the
// overworld: in RoomLeakyCauldronHallway by exit 6, elsewhere in the current room.
void UpdateClockSkipCutscene(void)
{
    g_GameModeStackContext.dwCurrentGameModeArg2++;

    if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0x85
        || (g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
    {
        if (g_bCurrentRoomId == RoomLeakyCauldronHallway)
        {
            g_abRoomEntryIds[0] = 0;
            PushGameMode_2(Overworld, OverworldEntryEnterRoom, RoomHogwartsExpressPassengerCar);
            g_dwGameModeFlags |= GameModeFlagModeChangeRequested;
        }
        else
        {
            PushGameMode_3(Overworld, OverworldEntryReturn, g_bCurrentRoomId, 0xFF);
        }
    }
}
