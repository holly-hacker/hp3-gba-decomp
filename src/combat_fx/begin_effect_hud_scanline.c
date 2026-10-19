#include "types.h"
#include "combat_fx.h"
#include "hw/io_regs.h"

// Scanline callback at line 112 of the effect scanline tables: brings BG0
// and BG1 to the front for the battle HUD and restores the HUD palette.
void BeginEffectHudScanline(u32 *pPayload0, u32 *pPayload1)
{
    u16 bgControl[2];

    bgControl[0] = REG_BG0CNT & ~3;
    bgControl[1] = REG_BG1CNT & ~3;
    g_BgState.aLayers[0].control.bits.bPriority = 0;
    g_BgState.aLayers[1].control.bits.bPriority = 0;

    while (!(REG_DISPSTAT & 2))
        ;

    REG_BGVOFS(1) = 40;
    REG_BGVOFS(0) = 80;
    REG_BGHOFS(1) = 0;
    REG_BGHOFS(0) = 0;
    REG_WINOUT |= 2;
    REG_BLDCNT = 0x1F40;
    REG_BG0CNT = bgControl[0];
    REG_BG1CNT = bgControl[1];
    REG_DMA3.src = g_pFightState->awPalette;
    REG_DMA3.dst = (void *)BG_PLTT;
    REG_DMA3.cnt = 0x80000200;
    (void)REG_DMA3.cnt;
}
