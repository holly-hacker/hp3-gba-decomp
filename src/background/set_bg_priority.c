#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

void SetBgPriority(u32 bg, u8 priority)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->control.bPriority = priority;
    REG_BGCNT(bg) = *(u16 *)&pLayer->control;
}
