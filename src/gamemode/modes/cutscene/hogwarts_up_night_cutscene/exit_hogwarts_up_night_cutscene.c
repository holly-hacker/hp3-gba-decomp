#include "types.h"
#include "graphics/audio.h"
#include "hw/bios.h"
#include "graphics/display.h"
#include "hw/io_regs.h"
#include "hw/mem.h"

void ExitHogwartsUpNightCutscene(void)
{
    volatile u16 zero;

    PlayScreenTransitionOutByIndex(0x3F, 2);
    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    UnmuteAllMusicChannels();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
}
