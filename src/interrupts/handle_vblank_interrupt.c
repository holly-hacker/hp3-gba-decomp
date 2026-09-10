#include "vblank.h"
#include "interrupts.h"
#include "io_regs.h"
#include "dma.h"
#include "oam.h"

extern void sub_08007130(void);
extern void sub_0800D354(void);
extern void sub_08045260(void);
extern void sub_0801FBBC(void);
extern void sub_08045988(void);
extern void sub_0800D304(void);
extern void sub_08049E3C(void);

// gIntrTable slot 1 (INTR_FLAG_VBLANK).
void HandleVBlankInterrupt(void)
{
    g_dwVBlankIntrNestCount++;
    if (g_dwVBlankIntrNestCount == 1)
    {
        g_bOamDmaHalfToggle ^= 1;

        if (g_pVBlankState->wSuppressOamSwap != 0 || g_bForcePendingBgWritesFlush != 0)
        {
            sub_08007130();
            g_bForcePendingBgWritesFlush = 0;
        }

        if (g_pVBlankState->wSuppressOamSwap != 0)
        {
            // swap: flush the buffer NOT currently marked as the DMA source
            if (g_pOamDmaShadowBuffer == g_aOamShadowBufferA)
            {
                REG_DMA3.src = g_aOamShadowBufferB + g_bOamDmaHalfToggle * 0x400;
                REG_DMA3.dst = OAM_BASE;
                REG_DMA3.cnt = 0x84000100;
                (void)REG_DMA3.cnt;
            }
            else
            {
                REG_DMA3.src = g_aOamShadowBufferA + g_bOamDmaHalfToggle * 0x400;
                REG_DMA3.dst = OAM_BASE;
                REG_DMA3.cnt = 0x84000100;
                (void)REG_DMA3.cnt;
            }

            g_bOamEntryCountPrev = g_bOamEntryCount;
            g_bOamEntryCount = 0;
            sub_0800D354();

            g_pOamDmaShadowBuffer = g_pOamShadowBuffer;
            if (g_pOamShadowBuffer == g_aOamShadowBufferA)
                g_pOamShadowBuffer = g_aOamShadowBufferB;
            else
                g_pOamShadowBuffer = g_aOamShadowBufferA;
        }
        else
        {
            // no swap: just re-flush the current DMA source buffer
            if (g_pOamDmaShadowBuffer == g_aOamShadowBufferA)
            {
                REG_DMA3.src = g_aOamShadowBufferA + g_bOamDmaHalfToggle * 0x400;
                REG_DMA3.dst = OAM_BASE;
                REG_DMA3.cnt = 0x84000100;
                (void)REG_DMA3.cnt;
            }
            else
            {
                REG_DMA3.src = g_aOamShadowBufferB + g_bOamDmaHalfToggle * 0x400;
                REG_DMA3.dst = OAM_BASE;
                REG_DMA3.cnt = 0x84000100;
                (void)REG_DMA3.cnt;
            }
        }

        sub_08045260();
        sub_0801FBBC();
        sub_08045988();

        if (g_pVBlankState->pVBlankCallback != NULL)
            ((void (*)(void))g_pVBlankState->pVBlankCallback)();

        sub_0800D304();

        g_pVBlankState->wSuppressOamSwap = 0;
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
        sub_08049E3C();
    }
    g_dwVBlankIntrNestCount--;

    REG_IME = 0;
    REG_IFBIOS |= 1;
    REG_IME = 1;
}
