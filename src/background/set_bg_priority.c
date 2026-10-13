#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

void SetBgPriority(u32 bg, u8 priority)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->control.bits.bPriority = priority;
    REG_BGCNT(bg) = pLayer->control.wRegister;
}
