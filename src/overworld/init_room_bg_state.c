#include "types.h"
#include "hw/mem.h"
#include "graphics/display.h"
#include "overworld/room.h"

void InitRoomBgState_candidate(void)
{
    s32 position[2];
    u32 i;

    g_nCameraYOffset = 18;
    position[0] = 0;
    position[1] = 0;
    SetCameraPosition(position);
    g_dwUnk030059AC = 0;
    for (i = 0; i < ARRAY_COUNT(g_adwBgScrollEnabled); i++)
        g_adwBgScrollEnabled[i] = 1;

    g_apBgTileCacheEntries[0] = AllocBlock(0x400 * sizeof(BgTileCacheEntry));
    g_apBgTileCacheEntries[1] = AllocBlock(0x200 * sizeof(BgTileCacheEntry));
    g_apBgTileCacheFreeSlots[0] = AllocZeroed(0x400 * sizeof(u16));
    g_apBgTileCacheFreeSlots[1] = AllocZeroed(0x200 * sizeof(u16));
    g_apBgTileCacheBuckets[0] = AllocZeroed(0x800 * sizeof(u16));
    g_apBgTileCacheBuckets[1] = AllocZeroed(0x400 * sizeof(u16));
}
