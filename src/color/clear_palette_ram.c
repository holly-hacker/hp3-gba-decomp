#include "color.h"
#include "hw/io_regs.h"
#include "mem.h"

void ClearPaletteRam(void)
{
    memset((void *)BG_PLTT, 0, 0x400);
}
