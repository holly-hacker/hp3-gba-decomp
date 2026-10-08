#include "types.h"
#include "graphics/oam.h"
#include "hw/dma.h"

// Defined const in ROM (hidden_oam_entry.c), but this file's declaration
// lacks const: the ROM code reloads it for every copy.
extern OamEntry g_HiddenOamEntry;

// Hides all 128 entries in both halves of both shadow buffers, then flushes
// g_pOamShadowBuffer to OAM.
void ClearOamShadowBuffers(void)
{
    s32 i;

    for (i = 0; i < 128; i++)
    {
        g_OamShadowBufferA.aHalves[0][i] = g_HiddenOamEntry;
        g_OamShadowBufferA.aHalves[1][i] = g_HiddenOamEntry;
        g_OamShadowBufferB.aHalves[0][i] = g_HiddenOamEntry;
        g_OamShadowBufferB.aHalves[1][i] = g_HiddenOamEntry;
    }

    REG_DMA3.src = g_pOamShadowBuffer;
    REG_DMA3.dst = OAM_BASE;
    REG_DMA3.cnt = 0x84000100;
    (void)REG_DMA3.cnt;
    g_bOamEntryCount = 0;
}
