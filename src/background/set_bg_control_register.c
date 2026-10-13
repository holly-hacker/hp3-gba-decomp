#include "types.h"
#include "background.h"
#include "hw/io_regs.h"
#include "hw/mem.h"

// The control word as the 4-byte aggregate it is passed as; callers pass a u32.
typedef struct BgControlArg {
    u16 awHalves[2];
} BgControlArg;

void SetBgControlRegister(u32 bg, BgControlArg control)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];
    BgControl *pControl = (BgControl *)&control;

    pLayer->control = *pControl;
    pLayer->pScreenBase = pLayer->pScreenBaseAlt = (u16 *)VRAM_BASE + pControl->bScreenBlock * 0x400;
    pLayer->pCharBase = (u8 *)VRAM_BASE + pControl->bCharBlock * 0x4000;
    REG_BGCNT(bg) = control.awHalves[0];
}
