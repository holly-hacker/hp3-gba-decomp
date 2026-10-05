#include "hw/mem.h"
#include "hw/dma.h"
#include "hw/io_regs.h"

void ClearWorkRam(void)
{
    u32 iwramSize;
    u32 ewramSize;
    volatile u32 zero;

    iwramSize = (u32)g_pIwramSectionEnd - (u32)g_pIwramSectionStart;
    ewramSize = (u32)g_pEwramSectionEnd - (u32)g_pEwramSectionStart;

    zero = 0;
    REG_DMA3.src = (const void *)&zero;
    REG_DMA3.dst = IWRAM_BASE + iwramSize;
    REG_DMA3.cnt = 0x85000000 | ((IWRAM_STACKS - IWRAM_BASE - iwramSize) >> 2);
    (void)REG_DMA3.cnt;

    zero = 0;
    REG_DMA3.src = (const void *)&zero;
    REG_DMA3.dst = EWRAM_BASE + ewramSize;
    REG_DMA3.cnt = 0x85000000 | ((EWRAM_END - EWRAM_BASE - ewramSize) >> 2);
    (void)REG_DMA3.cnt;
}
