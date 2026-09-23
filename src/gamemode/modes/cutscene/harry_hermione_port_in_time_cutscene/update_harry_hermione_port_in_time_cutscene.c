#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "harry_hermione_port_in_time_cutscene.h"
#include "input.h"
#include "overworld.h"
#include "room.h"
#include "room_script.h"

// Any of A/B/Select/Start skips to the overworld (exit 0xE). Otherwise progress rises until the
// camera focus passes y = 0x1F4, flashes white, then falls back to 0 and leaves for the
// overworld the same way. Arg2 is a frame counter for the delay at each end.
void UpdateHarryHermionePortInTimeCutscene(void)
{
    s32 fade = 0;
    s32 aPosition[2];

    if ((g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
    {
        g_abRoomScriptExitParams_candidate[0] = 0;
        PushGameMode_2(Overworld, 0, 0xE);
    }

    if (g_HarryHermionePortInTime.bRising != 0)
    {
        if (g_GameModeStackContext.dwCurrentGameModeArg2 > 0x1E)
            g_HarryHermionePortInTime.nProgress += 0xCCC;
        else
            g_GameModeStackContext.dwCurrentGameModeArg2++;

        if (g_HarryHermionePortInTime.nProgress > 0x7E666)
            g_HarryHermionePortInTime.nProgress = 0x7E666;

        fade = (g_HarryHermionePortInTime.nProgress << 2) >> 16;
        sub_0800A3EC(aPosition, 0);
        if (aPosition[1] > 0x1F40000)
        {
            SetFadeToWhite(0x2F, 0x10);
            sub_0803EA3C();
            sub_08043114(1);
            g_HarryHermionePortInTime.bRising = 0;
            g_HarryHermionePortInTime.dwUnk0 = 0;
            g_HarryHermionePortInTime.nProgress = 0x70000;
            g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
        }
    }
    else
    {
        g_HarryHermionePortInTime.nProgress -= 0xCCC;
        if (g_HarryHermionePortInTime.nProgress < 0)
        {
            g_HarryHermionePortInTime.nProgress = 0;
            g_GameModeStackContext.dwCurrentGameModeArg2++;
            if (g_GameModeStackContext.dwCurrentGameModeArg2 > 0x1E)
            {
                g_abRoomScriptExitParams_candidate[0] = 0;
                PushGameMode_2(Overworld, 0, 0xE);
            }
        }
        fade = (g_HarryHermionePortInTime.nProgress * 3) >> 16;
    }

    if (fade > 0x10)
        fade = 0x10;
    if (fade < 0)
        fade = 0;

    sub_0800A420(g_HarryHermionePortInTime.dwUnk0, g_HarryHermionePortInTime.nProgress, 0);
    sub_0800A3EC(aPosition, 0);
    SetObjectPosition(g_HarryHermionePortInTime.pObjectA,
                      g_aHarryHermionePortInTimeObjectPos[g_HarryHermionePortInTime.dwPositionIndex].nObjectAX,
                      (aPosition[1] >> 16) + 0x20);
    SetObjectPosition(g_HarryHermionePortInTime.pObjectB,
                      g_aHarryHermionePortInTimeObjectPos[g_HarryHermionePortInTime.dwPositionIndex].nObjectBX,
                      (aPosition[1] >> 16) + 0x20);
    UpdateOverworldCamera_candidate(0);
    SetFadeToWhite(0x2F, fade);
}
