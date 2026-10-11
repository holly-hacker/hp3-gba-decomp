#include "types.h"
#include "palette.h"

static inline u32 FindEmptyObjPaletteSlot(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aObjPaletteSlots); i++)
    {
        if (g_aObjPaletteSlots[i].pData == NULL
            && !(g_aObjPaletteSlots[i].wFlags & ObjPaletteSlotFlagReserved))
            return i;
    }

    return 0xFF;
}

static inline u32 FindUnreferencedObjPaletteSlot(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aObjPaletteSlots); i++)
    {
        if (g_aObjPaletteSlots[i].wRefcount == 0
            && !(g_aObjPaletteSlots[i].wFlags & ObjPaletteSlotFlagReserved))
            return i;
    }

    return 0xFF;
}

static inline u32 FindSharedObjPaletteSlot(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_aObjPaletteSlots); i++)
    {
        if (!(g_aObjPaletteSlots[i].wFlags & (ObjPaletteSlotFlagUnshared | ObjPaletteSlotFlagReserved)))
            return i;
    }

    return 0xFF;
}

// Prefers an empty slot, then one no actor references, then any shared slot;
// reserved slots are skipped. Falls back to the last slot.
u32 AllocObjPaletteSlot(void)
{
    u32 slot;

    slot = FindEmptyObjPaletteSlot();
    if (slot == 0xFF)
    {
        slot = FindUnreferencedObjPaletteSlot();
        if (slot == 0xFF)
        {
            slot = FindSharedObjPaletteSlot();
            if (slot == 0xFF)
                slot = ARRAY_COUNT(g_aObjPaletteSlots) - 1;
        }
    }

    return slot;
}
