#include "types.h"
#include "sound.h"
#include "hw/bios.h"
#include "graphics/display.h"
#include "hw/io_regs.h"
#include "mem.h"
#include "actor.h"
#include "screen_transitions.h"
#include "time_skip_cutscene.h"

void ExitHogwartsUpNightCutscene(void)
{
    volatile u16 zero;

    PlayScreenTransitionOutByIndex(0x3F, 2);
    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    UnmuteAllMusicChannels();
    FreeAllActors(&g_ActiveActorListState.pHead);
}
