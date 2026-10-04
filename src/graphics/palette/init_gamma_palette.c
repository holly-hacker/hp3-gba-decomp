#include "graphics/palette.h"
#include "game/save.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "menu/options.h"

void InitGammaPalette(void)
{
    InitPaletteBuffer(&g_PaletteState.bg, BG_PLTT);
    InitPaletteBuffer(&g_PaletteState.obj, OBJ_PLTT);
    ResetPaletteAnimations();
    g_pPaletteWorkBuffer = AllocZeroed(0x400);

    if (!g_saveManager.header.bHeaderFlags.bits.bGammaHigh)
        ApplyGammaRemapTable(g_abGammaNormalRemap);
    else
        ApplyGammaRemapTable(g_abGammaHighRemap);
}
