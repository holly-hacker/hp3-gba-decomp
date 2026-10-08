#include "types.h"
#include "graphics/oam.h"

void HideOamEntryOnAlternateVblanks(u32 index)
{
    OamEntry *entry;

    entry = g_pOamShadowBuffer->aHalves[1];
    entry += index;
    entry->affineMode = 2;
}
