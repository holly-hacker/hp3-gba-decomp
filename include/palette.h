#pragma once

#include "types.h"

// OBJ palette bank cache (ROM 0x0803071C-0x08030A1C): the 16 OBJ palette banks
// are handed out as reference-counted slots, shared between objects that
// use the same palette. Gamma, color cycles and palette effects are in
// graphics/palette.h.

struct Actor;

// OBJ palette resource: 16 BGR555 entries. Entry 0 is the transparent color and is
// not uploaded; entries 1-15 fill the OBJ palette bank (see AttachObjectPalette).
typedef struct ObjPalette {
    u16 aColors[16];
} ObjPalette;

// One OBJ palette bank (slot index = bank index).
typedef struct ObjPaletteSlot {
    void *pData;  // the ObjPalette loaded into the bank
    u16 wRefcount;
    u16 wFlags;  // ObjPaletteSlotFlags
} ObjPaletteSlot;

typedef enum {
    ObjPaletteSlotFlagUnshared = 0x1,  // not matched by FindObjPaletteSlot; cleared when
                                       // wRefcount reaches 0
    ObjPaletteSlotFlagReserved = 0x2,  // skipped by FindObjPaletteSlot and AllocObjPaletteSlot
} ObjPaletteSlotFlags;

extern ObjPaletteSlot g_aObjPaletteSlots[16];  // 0x03005114

// Rebinds the palette ReleaseObjectPalette saved in the object's pending
// palette, then clears it.
extern void BindObjectPendingPalette(struct Actor *obj);
extern u32 AllocObjPaletteSlot(void);
extern void ClearObjPaletteSlots(void);
// Sets the palette the object binds once it is onscreen (see TickActor).
extern void SetObjectPendingPalette(struct Actor *obj, const void *pPalette);
// Like SetObjectPendingPalette, but the palette is bound to an unshared slot.
extern void SetObjectPendingPaletteUnshared(struct Actor *obj, const void *pPalette);
extern u32 AttachObjectPalette(struct Actor *obj, const ObjPalette *pPalette);
// Like AttachObjectPalette, but always binds a newly allocated slot
// instead of sharing one already holding pPalette, and marks the slot
// ObjPaletteSlotFlagUnshared. Returns the slot index.
extern u32 AttachObjectPaletteUnshared(struct Actor *obj, const ObjPalette *pPalette);
extern void ReleaseObjectPalette(struct Actor *obj);
extern void ReleaseObjPaletteSlot(s32 slotIndex);
extern void ReserveObjPaletteSlot(u32 slotIndex);
extern void UnreserveObjPaletteSlot(u32 slotIndex);
extern void BindObjPaletteSlot(u32 slotIndex, struct Actor *obj, const ObjPalette *pPalette);
extern u32 IsObjPaletteSlotReserved(u32 slotIndex);
extern u32 FindObjPaletteSlot(const ObjPalette *pPalette);

// Bodies of AttachObjectPalette and AttachObjectPaletteUnshared, which the
// ROM also inlines in BindObjectPendingPalette.
static inline u32 AttachSharedPalette(struct Actor *obj, const ObjPalette *pPalette)
{
    u32 slot = FindObjPaletteSlot(pPalette);

    if (slot != 0xFF)
        pPalette = NULL;
    else
        slot = AllocObjPaletteSlot();

    BindObjPaletteSlot(slot, obj, pPalette);
    return slot;
}

static inline u32 AttachUnsharedPalette(struct Actor *obj, const ObjPalette *pPalette)
{
    u32 slot = AllocObjPaletteSlot();

    BindObjPaletteSlot(slot, obj, pPalette);
    g_aObjPaletteSlots[slot].wFlags |= ObjPaletteSlotFlagUnshared;
    return slot;
}
