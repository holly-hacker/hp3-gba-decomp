#include "types.h"
#include "mode7.h"
#include "background.h"
#include "hw/io_regs.h"
#include "mem.h"

void InitFloorDisplay(const u8 *pFloorBlob, const u32 *pFloorControl, const u8 *pSkyBlob,
                      const u32 *pSkyControl, s32 horizonLine, u32 scrollSky)
{
    g_pFloorAffineTable = AllocZeroed(FLOOR_SCANLINE_COUNT * sizeof(BgAffineDst));
    ResetDisplayState(1);
    SetFloorHorizonLineAndSkyScroll(horizonLine, scrollSky);

    if (pSkyBlob)
    {
        SetBgControl(1, *pSkyControl);
        ClearBgTilemap(1);
        REG_BGVOFS(1) = 0;
        REG_BGHOFS(1) = 0;
        LoadGraphicBlob(1, pSkyBlob, 0, 0, 0, 0);
    }

    if (pFloorBlob)
    {
        SetBgControl(2, *pFloorControl);
        ClearBgTilemap(2);
        REG_BG2Y_L = 0;
        REG_BG2X_L = 0;
        REG_BG2PA = 0x100;
        REG_BG2PB = 0;
        REG_BG2PC = 0;
        REG_BG2PD = 0x100;
        LoadGraphicBlob(2, pFloorBlob, 0, 0, 0, 0);
    }

    InitFloorEffect();
}
