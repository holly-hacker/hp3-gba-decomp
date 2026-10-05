#include "graphics/display.h"
#include "hw/dma.h"
#include "hw/io_regs.h"

void ClearPaletteRamDma(void)
{
    volatile u16 zero;

    zero = 0;
    REG_DMA3.src = (const void *)&zero;
    REG_DMA3.dst = (void *)BG_PLTT;
    REG_DMA3.cnt = 0x81000200;
    (void)REG_DMA3.cnt;
}
