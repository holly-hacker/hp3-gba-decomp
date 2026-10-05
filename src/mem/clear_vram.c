#include "hw/mem.h"
#include "graphics/display.h"
#include "hw/io_regs.h"

void ClearVram(void)
{
    memset(VRAM_BASE, 0, VRAM_SIZE);
}
