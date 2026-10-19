#include "color.h"
#include "hw/bios.h"

void SaveBgPaletteShadow(u16 *pDst)
{
    bios_CPUFastSet(g_PaletteState.bg.pShadow, pDst, 0x200 / 4);
}
