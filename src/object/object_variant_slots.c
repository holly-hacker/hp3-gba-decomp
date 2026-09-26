#include "types.h"
#include "object.h"

// Accessors for Object.aVariantSlots. None of them are called.

// Switches the object to drawing from its variant slots and resets each
// slot: no tile allocation, the object's palette bank, and no tables.
void EnableObjectVariantSlots(Object *obj)
{
    s32 i;

    obj->bDrawFlags |= ObjectDrawFlagVariantSlots;
    for (i = 0; i < 1; i++) {
        obj->aVariantSlots[i].wVramTileAllocId |= 0xFFFF;
        obj->aVariantSlots[i].bPaletteBank = obj->bGfxSlot;
        obj->aVariantSlots[i].pSpriteVariantTables = NULL;
    }
}

void DisableObjectVariantSlots(Object *obj)
{
    obj->bDrawFlags &= ~ObjectDrawFlagVariantSlots;
}

void AssignObjectVariantSlot(Object *obj, u8 slot, ObjectAssetRecord **tables, u8 paletteBank)
{
    obj->aVariantSlots[slot].pSpriteVariantTables = tables;
    obj->aVariantSlots[slot].bPaletteBank = paletteBank;
}

// A slot without tables is not drawn.
void ClearObjectVariantSlot(Object *obj, u8 slot)
{
    obj->aVariantSlots[slot].pSpriteVariantTables = NULL;
}

void EnableObjectVariantSlotBlink(Object *obj, u8 slot)
{
    obj->aVariantSlots[slot].bFrameFlags |= ObjectVariantSlotFlagBlink;
}

void DisableObjectVariantSlotBlink(Object *obj, u8 slot)
{
    obj->aVariantSlots[slot].bFrameFlags &= ~ObjectVariantSlotFlagBlink;
}

void SetObjectVariantSlotPalette(Object *obj, u8 slot, u8 paletteBank)
{
    obj->aVariantSlots[slot].bPaletteBank = paletteBank;
}

void SetObjectVariantSlotDrawOrder(Object *obj, u8 slot, u8 drawOrder)
{
    obj->aVariantSlots[slot].bDrawOrder = drawOrder;
}

void EnableObjectVariantSlotBounds(Object *obj, u8 slot)
{
    obj->aVariantSlots[slot].bFrameFlags |= ObjectVariantSlotFlagBounds;
}

void DisableObjectVariantSlotBounds(Object *obj, u8 slot)
{
    obj->aVariantSlots[slot].bFrameFlags &= ~ObjectVariantSlotFlagBounds;
}

void EnableObjectVariantSlotPrevFrame(Object *obj, u8 slot)
{
    obj->aVariantSlots[slot].bFrameFlags |= ObjectVariantSlotFlagPrevFrameWrap;
}

void DisableObjectVariantSlotPrevFrame(Object *obj, u8 slot)
{
    obj->aVariantSlots[slot].bFrameFlags &= ~ObjectVariantSlotFlagPrevFrameWrap;
}
