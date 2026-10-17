#include "ram_clear.h"
#include "sound.h"
#include "hw/io_regs.h"

void ClearWorkRam(void)
{
    u32 krawallIwramSize;
    u32 krawallEwramSize;
    volatile u32 zero;

    krawallIwramSize = (u32)g_pKrawallIwramEnd - (u32)g_pKrawallIwramStart;
    krawallEwramSize = (u32)g_pKrawallEwramEnd - (u32)g_pKrawallEwramStart;

    zero = 0;
    REG_DMA3.src = (const void *)&zero;
    REG_DMA3.dst = IWRAM_BASE + krawallIwramSize;
    REG_DMA3.cnt = 0x85000000 | ((IWRAM_STACKS - IWRAM_BASE - krawallIwramSize) >> 2);
    (void)REG_DMA3.cnt;

    zero = 0;
    REG_DMA3.src = (const void *)&zero;
    REG_DMA3.dst = EWRAM_BASE + krawallEwramSize;
    REG_DMA3.cnt = 0x85000000 | ((EWRAM_END - EWRAM_BASE - krawallEwramSize) >> 2);
    (void)REG_DMA3.cnt;
}
