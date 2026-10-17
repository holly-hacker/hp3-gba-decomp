#include "mode7.h"
#include "hw/io_regs.h"
#include "mem.h"
#include "video.h"

void FreeFloorEffect(void)
{
    ClearScanlineEffects();
    REG_DMA0CNT_H = 0;
    FreeBlock(g_pFloorAffineTable);
}
