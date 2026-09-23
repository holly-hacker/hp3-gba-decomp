#include "types.h"
#include "audio.h"
#include "bios.h"
#include "display.h"
#include "io_regs.h"
#include "mem.h"

void ExitHogwartsUpNightCutscene(void)
{
    volatile u16 zero;

    PlayScreenTransitionOutByIndex(0x3F, 2);
    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    UnmuteAllMusicChannels();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
