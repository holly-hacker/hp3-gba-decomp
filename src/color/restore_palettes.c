#include "color.h"
#include "mem.h"

// Copies 0x200 bytes of BG colors and then 0x200 bytes of OBJ colors from pColors into both
// shadows and palette RAM, without gamma.
void RestorePalettes(const u16 *pColors)
{
    CopyMemory(g_PaletteState.bg.pShadow, pColors, 0x200);
    CopyMemory((void *)g_PaletteState.bg.pPaletteRam, pColors, 0x200);
    pColors += 0x100;
    CopyMemory(g_PaletteState.obj.pShadow, pColors, 0x200);
    CopyMemory((void *)g_PaletteState.obj.pPaletteRam, pColors, 0x200);
}
