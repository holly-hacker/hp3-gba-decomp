#include "types.h"
#include "background.h"
#include "interrupts.h"
#include "video.h"
#include "hw/dma.h"
#include "hw/io_regs.h"
#include "dialog.h"
#include "dialog_box.h"

void BeginDialogBoxPanelScanline(u32 *pPayload0, u32 *pPayload1)
{
    s32 scrollY;
    volatile u16 *pBgControl;
    u32 bg0Control;
    u32 bg1Control;

    scrollY = g_dwDialogBoxTileRow * 8 - GetScanlineEffectLine(0) + 3;
    pBgControl = &REG_BG0CNT;
    g_BgState.aLayers[1].dwFlags |= BG_LAYER_COMMIT;
    g_bForcePendingBgWritesFlush = 1;
    bg0Control = (*pBgControl++ & 0xFFFC) + 1;
    bg1Control = *pBgControl-- & 0xFFFC;

    while (!(REG_DISPSTAT & 2))
        ;

    REG_DMA3.src = g_awDialogBoxPalette;
    REG_DMA3.dst = (void *)BG_PLTT;
    REG_DMA3.cnt = 0x84000008;
    (void)REG_DMA3.cnt;
    *pBgControl++ = bg0Control;
    *pBgControl = bg1Control;
    REG_BGHOFS(1) = 0;
    REG_BGVOFS(1) = scrollY;
}
