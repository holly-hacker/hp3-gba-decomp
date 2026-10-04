#include "graphics/display.h"
#include "hw/dma.h"

void ClearOamDma(void)
{
    volatile u32 zero;

    zero = 0;
    REG_DMA3.src = (const void *)&zero;
    REG_DMA3.dst = (void *)0x07000000;
    REG_DMA3.cnt = 0x85000100;
    (void)REG_DMA3.cnt;
}
