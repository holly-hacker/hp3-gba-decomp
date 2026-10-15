#include "types.h"
#include "mode7.h"
#include "hw/io_regs.h"

void StartFloorAffineHBlankDma(u32 *pPayload0, u32 *pPayload1)
{
    REG_DMA0CNT_H = 0;
    REG_DMA0SAD = (u32)g_pFloorAffineTable;
    REG_DMA0DAD = (u32)&REG_BG2PA;
    // Enabled, HBlank start, repeat, destination increment+reload, 8 halfwords per line.
    REG_DMA0CNT = 0xA2600008;
}
