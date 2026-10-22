#include "types.h"
#include "modes.h"
#include "timeturner_cutscene.h"
#include "input.h"
#include "screen_transitions.h"
#include "scroll.h"
#include "hero.h"
#include "map.h"

// Any of A/B/Select/Start skips to the overworld (exit 0xE). Otherwise progress rises until the
// camera focus passes y = 0x1F4, flashes white, then falls back to 0 and leaves for the
// overworld the same way. Arg2 is a frame counter for the delay at each end.
void UpdateHarryHermionePortInTimeCutscene(void)
{
    s32 fade = 0;
    FixedPoint position;

    if ((g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
    {
        g_abRoomScriptExitParams_candidate[0] = 0;
        PushGameMode_2(Overworld, OverworldEntryEnterRoom, 0xE);
    }

    if (g_HarryHermionePortInTime.bRising != 0)
    {
        if (g_GameModeStackContext.dwCurrentGameModeArg2 > 0x1E)
            g_HarryHermionePortInTime.cameraDelta.y += 0xCCC;
        else
            g_GameModeStackContext.dwCurrentGameModeArg2++;

        if (g_HarryHermionePortInTime.cameraDelta.y > 0x7E666)
            g_HarryHermionePortInTime.cameraDelta.y = 0x7E666;

        fade = (g_HarryHermionePortInTime.cameraDelta.y << 2) >> 16;
        GetCameraFocusPosition(&position, 0);
        if (position.y > 0x1F40000)
        {
            SetFadeToWhite(0x2F, 0x10);
            FreeBgTileBitOffsets();
            LoadHarryHermionePortInTimeRoom(1);
            g_HarryHermionePortInTime.bRising = 0;
            g_HarryHermionePortInTime.cameraDelta.x = 0;
            g_HarryHermionePortInTime.cameraDelta.y = 0x70000;
            g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
        }
    }
    else
    {
        g_HarryHermionePortInTime.cameraDelta.y -= 0xCCC;
        if (g_HarryHermionePortInTime.cameraDelta.y < 0)
        {
            g_HarryHermionePortInTime.cameraDelta.y = 0;
            g_GameModeStackContext.dwCurrentGameModeArg2++;
            if (g_GameModeStackContext.dwCurrentGameModeArg2 > 0x1E)
            {
                g_abRoomScriptExitParams_candidate[0] = 0;
                PushGameMode_2(Overworld, OverworldEntryEnterRoom, 0xE);
            }
        }
        fade = (g_HarryHermionePortInTime.cameraDelta.y * 3) >> 16;
    }

    if (fade > 0x10)
        fade = 0x10;
    if (fade < 0)
        fade = 0;

    OffsetCameraFocus(g_HarryHermionePortInTime.cameraDelta, 0);
    GetCameraFocusPosition(&position, 0);
    SetActorPosition(g_HarryHermionePortInTime.apActors[0],
                      g_aHarryHermionePortInTimeActorPos[g_HarryHermionePortInTime.dwPositionIndex].nActorAX,
                      (position.y >> 16) + 0x20);
    SetActorPosition(g_HarryHermionePortInTime.apActors[1],
                      g_aHarryHermionePortInTimeActorPos[g_HarryHermionePortInTime.dwPositionIndex].nActorBX,
                      (position.y >> 16) + 0x20);
    UpdateOverworldCamera(0);
    SetFadeToWhite(0x2F, (u16)fade);
}
