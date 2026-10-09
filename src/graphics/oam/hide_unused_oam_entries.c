#include "types.h"
#include "graphics/oam.h"
#include "hw/vblank.h"

// Hides every entry not queued this frame in both halves of the current
// shadow buffer, then flags the buffer as ready for HandleVBlankInterrupt.
void HideUnusedOamEntries(void)
{
    u32 i;
    OamEntry *entry;

    for (i = g_bOamEntryCount; i < 128; i++)
    {
        g_pOamShadowBuffer->aHalves[0][i].affineMode = 2;
        entry = g_pOamShadowBuffer->aHalves[1];
        entry += i;
        entry->affineMode = 2;
    }

    g_pVBlankState->wOamFrameReady = 1;
}
