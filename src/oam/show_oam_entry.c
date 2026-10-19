#include "types.h"
#include "oam.h"

void ShowOamEntry(u32 index)
{
    OamEntry *entry;

    g_pOamShadowBuffer->aHalves[0][index].affineMode = 0;
    entry = g_pOamShadowBuffer->aHalves[1];
    entry += index;
    entry->affineMode = 0;
}
