#include "graphics/palette.h"
#include "hw/mem.h"

void StepPaletteEffect(PaletteEffect *pEffect)
{
    u8 aStep[32];
    u32 active;
    s32 i;
    u32 accum;
    u32 level;
    s32 value;
    u32 n;
    u16 *pDst;
    const u16 *pSrc;
    u32 dst;
    u32 src;
    u32 c1;
    u32 c2;

    if (pEffect->wFlags & 0x20)
    {
        if (--pEffect->bDelayTimer_candidate == 0xFF)
        {
            active = 1;
            pEffect->bDelayTimer_candidate = pEffect->bDelay_candidate;
        }
        else
            active = 0;
    }
    else
        active = 1;

    if (pEffect->bStepTimer_candidate == 0)
    {
        if (pEffect->wFlags & 0x10)
        {
            pEffect->bFrameIndex++;
            if (pEffect->bFrameIndex >= pEffect->bFrameCount)
                pEffect->bFrameIndex = 0;
            pEffect->bStepTimer_candidate = pEffect->bStepTicks_candidate;
            pEffect->pCurrentFrame = pEffect->pFrames + pEffect->bFrameIndex * 16;
        }
        else
        {
            pEffect->wFlags &= ~PALETTE_ANIM_ACTIVE;
            memset(pEffect, 0, sizeof(PaletteEffect));
            if (g_dwPaletteEffectCount != 0)
                g_dwPaletteEffectCount--;
        }
    }
    else if (active)
    {
        level = 0;
        value = pEffect->bStepTimer_candidate;
        i = 0;
        for (; i < 32; i++)
        {
            if (value-- == 0)
            {
                value += pEffect->bStepTimer_candidate;
                level++;
            }
            aStep[i] = level;
        }

        if (pEffect->wFlags & PALETTE_ANIM_OBJ)
            pDst = g_PaletteState.obj.pShadow;
        else
            pDst = g_PaletteState.bg.pShadow;
        pDst += pEffect->bStartColor;

        if (pEffect->wFlags & 8)
            pSrc = pEffect->pCurrentFrame + (pEffect->bStartColor & 0xF);
        else
            pSrc = pEffect->pCurrentFrame + pEffect->bStartColor;

        n = pEffect->wColorCount;
        while (n != 0)
        {
            dst = *pDst;
            src = *pSrc;
            if (dst != src)
            {
                accum = 0;
                i = 3;
                for (;;)
                {
                    c1 = dst & 0x1F;
                    c2 = src & 0x1F;
                    accum += c1 << 10;
                    if (c1 <= c2)
                        accum += aStep[c2 - c1] << 10;
                    else
                        accum -= aStep[c1 - c2] << 10;
                    if (--i == 0)
                        break;
                    dst >>= 5;
                    src >>= 5;
                    accum >>= 5;
                }
                *pDst = accum;
            }
            pDst++;
            pSrc++;
            n--;
        }

        pEffect->wFlags |= PALETTE_ANIM_DIRTY;
        pEffect->bStepTimer_candidate--;
    }
}
