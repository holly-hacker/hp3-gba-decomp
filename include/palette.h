#pragma once

#include "types.h"

// OBJ palette bank cache: the 16 OBJ palette banks
// are handed out as reference-counted slots, shared between actors that
// use the same palette. Gamma, color cycles and palette effects are in
// color.h.

struct Actor;

// OBJ palette resource: 16 BGR555 entries. Entry 0 is the transparent color and is
// not uploaded; entries 1-15 fill the OBJ palette bank (see AttachActorPalette).
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

// Rebinds the palette ReleaseActorPalette saved in the actor's pending
// palette, then clears it.
extern void BindActorPendingPalette(struct Actor *actor);
extern u32 AllocObjPaletteSlot(void);
extern void ClearObjPaletteSlots(void);
// Sets the palette the actor binds once it is onscreen (see TickActor).
extern void SetActorPendingPalette(struct Actor *actor, const void *pPalette);
// Like SetActorPendingPalette, but the palette is bound to an unshared slot.
extern void SetActorPendingPaletteUnshared(struct Actor *actor, const void *pPalette);
extern u32 AttachActorPalette(struct Actor *actor, const ObjPalette *pPalette);
// Like AttachActorPalette, but always binds a newly allocated slot
// instead of sharing one already holding pPalette, and marks the slot
// ObjPaletteSlotFlagUnshared. Returns the slot index.
extern u32 AttachActorPaletteUnshared(struct Actor *actor, const ObjPalette *pPalette);
extern void ReleaseActorPalette(struct Actor *actor);
extern void ReleaseObjPaletteSlot(s32 slotIndex);
extern void ReserveObjPaletteSlot(u32 slotIndex);
extern void UnreserveObjPaletteSlot(u32 slotIndex);
extern void BindObjPaletteSlot(u32 slotIndex, struct Actor *actor, const ObjPalette *pPalette);
extern u32 IsObjPaletteSlotReserved(u32 slotIndex);
extern u32 FindObjPaletteSlot(const ObjPalette *pPalette);

// Bodies of AttachActorPalette and AttachActorPaletteUnshared, which the
// ROM also inlines in BindActorPendingPalette.
static inline u32 AttachSharedPalette(struct Actor *actor, const ObjPalette *pPalette)
{
    u32 slot = FindObjPaletteSlot(pPalette);

    if (slot != 0xFF)
        pPalette = NULL;
    else
        slot = AllocObjPaletteSlot();

    BindObjPaletteSlot(slot, actor, pPalette);
    return slot;
}

static inline u32 AttachUnsharedPalette(struct Actor *actor, const ObjPalette *pPalette)
{
    u32 slot = AllocObjPaletteSlot();

    BindObjPaletteSlot(slot, actor, pPalette);
    g_aObjPaletteSlots[slot].wFlags |= ObjPaletteSlotFlagUnshared;
    return slot;
}
