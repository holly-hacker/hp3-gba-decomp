#include "types.h"
#include "background.h"
#include "hw/bios.h"
#include "modes.h"
#include "timeturner_cutscene.h"
#include "hw/io_regs.h"
#include "vram.h"
#include "screen_transitions.h"

void InitializeHarryHermionePortInTimeCutscene(void)
{
    volatile u16 zero;
    FixedPoint position;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    ClearObjPaletteSlots();
    InitObjTileAllocBitmaps(0);
    SetAlphaBlendTargets(0, 0x1F);
    SetAlphaBlendCoefficients(9, 10);
    LoadHarryHermionePortInTimeRoom(0);
    SpawnHarryHermionePortInTimeActor(0);
    SpawnHarryHermionePortInTimeActor(1);

    GetCameraFocusPosition(&position, 0);
    SetActorPosition(g_HarryHermionePortInTime.apActors[0],
                      g_aHarryHermionePortInTimeActorPos[g_HarryHermionePortInTime.dwPositionIndex].nActorAX,
                      (position.y >> 16) + 0x20);
    SetActorPosition(g_HarryHermionePortInTime.apActors[1],
                      g_aHarryHermionePortInTimeActorPos[g_HarryHermionePortInTime.dwPositionIndex].nActorBX,
                      (position.y >> 16) + 0x20);

    g_HarryHermionePortInTime.bRising = 1;
    g_HarryHermionePortInTime.cameraDelta.x = 0;
    g_HarryHermionePortInTime.cameraDelta.y = 0;
    PlayScreenTransitionInByIndex(0x3F, 2);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
}
