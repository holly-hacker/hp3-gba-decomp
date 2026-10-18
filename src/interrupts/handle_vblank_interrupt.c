#include "background.h"
#include "interrupts.h"
#include "hw/io_regs.h"
#include "oam.h"
#include "dialog_box.h"
#include "color.h"
#include "video.h"
#include "windows.h"
#include "3rd_party/krawall.h"

// gIntrTable slot 1 (INTR_FLAG_VBLANK).
void HandleVBlankInterrupt(void)
{
    g_dwVBlankIntrNestCount++;
    if (g_dwVBlankIntrNestCount == 1)
    {
        g_bOamDmaHalfToggle ^= 1;

        if (g_pVBlankState->wOamFrameReady != 0 || g_bForcePendingBgWritesFlush != 0)
        {
            CommitBgLayers();
            g_bForcePendingBgWritesFlush = 0;
        }

        if (g_pVBlankState->wOamFrameReady != 0)
        {
            // swap: flush the buffer NOT currently marked as the DMA source
            if (g_pOamDmaShadowBuffer == &g_OamShadowBufferA)
            {
                REG_DMA3.src = g_OamShadowBufferB.aHalves[g_bOamDmaHalfToggle];
                REG_DMA3.dst = OAM_BASE;
                REG_DMA3.cnt = 0x84000100;
                (void)REG_DMA3.cnt;
            }
            else
            {
                REG_DMA3.src = g_OamShadowBufferA.aHalves[g_bOamDmaHalfToggle];
                REG_DMA3.dst = OAM_BASE;
                REG_DMA3.cnt = 0x84000100;
                (void)REG_DMA3.cnt;
            }

            g_bOamEntryCountPrev = g_bOamEntryCount;
            g_bOamEntryCount = 0;
            sub_0800D354();

            g_pOamDmaShadowBuffer = g_pOamShadowBuffer;
            if (g_pOamShadowBuffer == &g_OamShadowBufferA)
                g_pOamShadowBuffer = &g_OamShadowBufferB;
            else
                g_pOamShadowBuffer = &g_OamShadowBufferA;
        }
        else
        {
            // no swap: just re-flush the current DMA source buffer
            if (g_pOamDmaShadowBuffer == &g_OamShadowBufferA)
            {
                REG_DMA3.src = g_OamShadowBufferA.aHalves[g_bOamDmaHalfToggle];
                REG_DMA3.dst = OAM_BASE;
                REG_DMA3.cnt = 0x84000100;
                (void)REG_DMA3.cnt;
            }
            else
            {
                REG_DMA3.src = g_OamShadowBufferB.aHalves[g_bOamDmaHalfToggle];
                REG_DMA3.dst = OAM_BASE;
                REG_DMA3.cnt = 0x84000100;
                (void)REG_DMA3.cnt;
            }
        }

        CommitScanlineEffects();
        RestoreBgAboveDialogBox();
        sub_08045988();

        if (g_pVBlankState->pVBlankCallback != NULL)
            g_pVBlankState->pVBlankCallback();

        sub_0800D304();

        g_pVBlankState->wOamFrameReady = 0;
        g_pVBlankState->dwVBlankCount++;
        g_pVBlankState->dwSecondTick++;
        if (g_pVBlankState->dwSecondTick > 59)
        {
            g_pVBlankState->dwFramesLastSecond = g_pVBlankState->dwFrameCounter;
            g_pVBlankState->dwFrameCounter = 0;
            g_pVBlankState->dwSecondTick = 0;
        }

        REG_IF = 1;
        g_wPendingIntrFlags |= 1;
        kramWorker();
    }
    g_dwVBlankIntrNestCount--;

    REG_IME = 0;
    REG_IFBIOS |= 1;
    REG_IME = 1;
}
