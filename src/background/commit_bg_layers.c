#include "types.h"
#include "background.h"
#include "hw/io_regs.h"

void CommitBgLayers(void)
{
    u32 bg;
    BgLayer *pLayer;
    volatile u16 *pReg;

    for (bg = 0; bg < 4; bg++)
    {
        pLayer = &g_BgState.aLayers[bg];
        if (!(pLayer->dwFlags & BG_LAYER_COMMIT))
            continue;

        REG_BGHOFS(bg) = pLayer->out.x >> 16;
        REG_BGVOFS(bg) = pLayer->out.y >> 16;
        if (!(pLayer->dwFlags & BG_LAYER_ROTATE))
            continue;

        if (bg == 2)
        {
            pReg = &REG_BG2PA;
            *pReg++ = pLayer->nPa;
            *pReg++ = pLayer->nPb;
            *pReg++ = pLayer->nPc;
            *pReg++ = pLayer->nPd;
            *pReg = pLayer->nRefX;
            REG_BG2X_H = (pLayer->nRefX & 0x0FFF0000) >> 16;
            pReg += 2;
        }
        else if (bg == 3)
        {
            pReg = &REG_BG3PA;
            *pReg++ = pLayer->nPa;
            *pReg++ = pLayer->nPb;
            *pReg++ = pLayer->nPc;
            *pReg++ = pLayer->nPd;
            *pReg++ = pLayer->nRefX;
            *pReg++ = (pLayer->nRefX & 0x0FFF0000) >> 16;
        }
        else
            continue;

        *pReg++ = pLayer->nRefY;
        *pReg = (pLayer->nRefY & 0x0FFF0000) >> 16;
    }
}
