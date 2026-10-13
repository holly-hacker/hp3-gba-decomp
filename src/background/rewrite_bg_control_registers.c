#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

void RewriteBgControlRegisters(void)
{
    u32 bg = 0;
    BgLayer *pLayer = g_BgState.aLayers;
    u32 flags = 0;
    BgLayer *pControl = g_BgState.aLayers;

    for (; bg < 4; bg++)
    {
        flags = pLayer->dwFlags;
        if (flags & BG_LAYER_COMMIT)
        {
            if (flags & 0x200)
                REG_BGCNT(bg) = pControl->control.wRegister;
        }
        pLayer++;
        pControl++;
    }
}
