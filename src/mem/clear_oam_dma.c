#include "graphics/display.h"
#include "hw/dma.h"
#include "graphics/oam.h"

void ClearOamDma(void)
{
    volatile u32 zero;

    zero = 0;
    REG_DMA3.src = (const void *)&zero;
    REG_DMA3.dst = OAM_BASE;
    REG_DMA3.cnt = 0x85000100;
    (void)REG_DMA3.cnt;
}
