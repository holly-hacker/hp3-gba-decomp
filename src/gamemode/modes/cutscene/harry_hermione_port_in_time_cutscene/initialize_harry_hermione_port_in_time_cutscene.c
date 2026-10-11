#include "types.h"
#include "hw/bios.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "graphics/graphics.h"
#include "cutscene/harry_hermione_port_in_time_cutscene.h"
#include "hw/io_regs.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "vram.h"

void InitializeHarryHermionePortInTimeCutscene(void)
{
    volatile u16 zero;
    s32 aPosition[2];

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    ClearObjPaletteSlots();
    InitObjTileAllocBitmaps(0);
    SetAlphaBlendTargets(0, 0x1F);
    SetAlphaBlendCoefficients(9, 10);
    sub_08043114(0);
    sub_08043308(0);
    sub_08043308(1);

    sub_0800A3EC(aPosition, 0);
    SetActorPosition(g_HarryHermionePortInTime.pActorA,
                      g_aHarryHermionePortInTimeActorPos[g_HarryHermionePortInTime.dwPositionIndex].nActorAX,
                      (aPosition[1] >> 16) + 0x20);
    SetActorPosition(g_HarryHermionePortInTime.pActorB,
                      g_aHarryHermionePortInTimeActorPos[g_HarryHermionePortInTime.dwPositionIndex].nActorBX,
                      (aPosition[1] >> 16) + 0x20);

    g_HarryHermionePortInTime.bRising = 1;
    g_HarryHermionePortInTime.dwUnk0 = 0;
    g_HarryHermionePortInTime.nProgress = 0;
    PlayScreenTransitionInByIndex(0x3F, 2);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
}
