#include "hw/mem.h"
#include "hw/dma.h"

void ClearWorkRam(void)
{
    u32 iwramSize;
    u32 ewramSize;
    volatile u32 zero;

    iwramSize = (u32)g_pIwramSectionEnd - (u32)g_pIwramSectionStart;
    ewramSize = (u32)g_pEwramSectionEnd - (u32)g_pEwramSectionStart;

    zero = 0;
    REG_DMA3.src = (const void *)&zero;
    REG_DMA3.dst = (void *)(0x03000000 + iwramSize);
    REG_DMA3.cnt = 0x85000000 | ((0x7D00 - iwramSize) >> 2);
    (void)REG_DMA3.cnt;

    zero = 0;
    REG_DMA3.src = (const void *)&zero;
    REG_DMA3.dst = (void *)(0x02000000 + ewramSize);
    REG_DMA3.cnt = 0x85000000 | ((0x40000 - ewramSize) >> 2);
    (void)REG_DMA3.cnt;
}
