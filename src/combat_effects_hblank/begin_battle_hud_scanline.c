#include "types.h"
#include "background.h"
#include "combat.h"
#include "combat_effects_hblank.h"
#include "hw/io_regs.h"

void BeginBattleHudScanline(u32 *pPayload0, u32 *pPayload1)
{
    while (!(REG_DISPSTAT & 2))
        ;

    REG_BGVOFS(1) = 40;
    REG_BGVOFS(0) = 80;
    REG_BGHOFS(1) = 0;
    REG_DMA3.src = g_pFightState->awPalette;
    REG_DMA3.dst = (void *)BG_PLTT;
    REG_DMA3.cnt = 0x80000200;
    (void)REG_DMA3.cnt;
    SetBgPriority(1, 0);
    REG_BLDALPHA = 0x0808;
}
