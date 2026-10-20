#include "types.h"
#include "hw/io_regs.h"
#include "actor.h"
#include "screen_transitions.h"
#include "screen_transitions_inline.h"

// Turns on mosaic for the displayed layers, then shrinks it from 15x15 pixels while
// undarkening the screen. The BG mosaic bits stay set.
void TransitionInMosaic(u16 blendArg)
{
    s16 hSize = 16;
    s16 vSize = 16;
    volatile u16 layers;
    ListNode *node;

    REG_BLDCNT = blendArg | BLDCNT_DARKEN;
    layers = REG_DISPCNT & ~7;
    if (layers & 0x100)
        REG_BG0CNT |= BGCNT_MOSAIC;
    if (layers & 0x200)
        REG_BG1CNT |= BGCNT_MOSAIC;
    if (layers & 0x400)
        REG_BG2CNT |= BGCNT_MOSAIC;
    if (layers & 0x800)
        REG_BG3CNT |= BGCNT_MOSAIC;
    if (layers & 0x1000)
        for (node = g_ActiveActorListState.pHead; node != NULL; node = node->pNext)
            ((Actor *)node)->oam.mosaic = 1;

    while (hSize > 0)
    {
        hSize -= 2;
        vSize -= 2;
        REG_MOSAIC = (vSize << 12) | (hSize << 8) | (vSize << 4) | hSize;
        REG_BLDY = hSize;
        TickTransitionFrame();
    }

    if (layers & 0x1000)
        for (node = g_ActiveActorListState.pHead; node != NULL; node = node->pNext)
            ((Actor *)node)->oam.mosaic = 0;
}
