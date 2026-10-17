#include "interrupts.h"
#include "hw/io_regs.h"

void InitInterruptSystem(void)
{
    g_pVBlankState = &g_VBlankState;
    InstallInterruptHandler(IntrMain);
    REG_DMA3.src = gIntrTableTemplate;
    REG_DMA3.dst = gIntrTable;
    REG_DMA3.cnt = 0x8400000D;
    (void)REG_DMA3.cnt;
}
