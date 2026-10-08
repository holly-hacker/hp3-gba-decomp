#include "types.h"
#include "graphics/oam.h"

s32 QueueOamEntry(u8 index, OamEntry *pEntry)
{
    OamShadowBuffer *buf;
    OamEntry *first;
    OamEntry *second;

    if ((s8)g_bOamEntryCount < 0)
        return -1;
    buf = g_pOamShadowBuffer;
    first = buf->aHalves[0];
    first += index;
    *first = *pEntry;
    second = buf->aHalves[1];
    second += index;
    *second = *pEntry;
    g_bOamEntryCount++;
    return 0;
}
