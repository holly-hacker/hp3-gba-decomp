#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

void ResetBgLayer(u32 bg)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    pLayer->dwFlags = 0;
    pLayer->step = g_FixedOrigin;
    pLayer->scroll = g_FixedOrigin;
    pLayer->out = g_FixedOrigin;
    REG_BGHOFS(bg) = 0;
    REG_BGVOFS(bg) = 0;
}
