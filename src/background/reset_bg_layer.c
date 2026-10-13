#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

static const FixedPoint sOrigin = {0, 0};

void ResetBgLayer(u32 bg)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->dwFlags = 0;
    pLayer->step = sOrigin;
    pLayer->scroll = sOrigin;
    pLayer->out = sOrigin;
    REG_BGHOFS(bg) = 0;
    REG_BGVOFS(bg) = 0;
}
