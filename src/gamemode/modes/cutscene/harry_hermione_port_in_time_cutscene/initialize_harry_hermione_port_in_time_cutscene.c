#include "types.h"
#include "hw/bios.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/graphics.h"
#include "cutscene/harry_hermione_port_in_time_cutscene.h"
#include "hw/io_regs.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void InitializeHarryHermionePortInTimeCutscene(void)
{
    volatile u16 zero;
    s32 aPosition[2];

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    ClearResourceCacheSlots();
    InitObjTileAllocBitmaps(0);
    SetAlphaBlendTargets(0, 0x1F);
    SetAlphaBlendCoefficients(9, 10);
    sub_08043114(0);
    sub_08043308(0);
    sub_08043308(1);

    sub_0800A3EC(aPosition, 0);
    SetObjectPosition(g_HarryHermionePortInTime.pObjectA,
                      g_aHarryHermionePortInTimeObjectPos[g_HarryHermionePortInTime.dwPositionIndex].nObjectAX,
                      (aPosition[1] >> 16) + 0x20);
    SetObjectPosition(g_HarryHermionePortInTime.pObjectB,
                      g_aHarryHermionePortInTimeObjectPos[g_HarryHermionePortInTime.dwPositionIndex].nObjectBX,
                      (aPosition[1] >> 16) + 0x20);

    g_HarryHermionePortInTime.bRising = 1;
    g_HarryHermionePortInTime.dwUnk0 = 0;
    g_HarryHermionePortInTime.nProgress = 0;
    PlayScreenTransitionInByIndex(0x3F, 2);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
}
