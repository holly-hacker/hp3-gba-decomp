#include "types.h"
#include "actor.h"

// Accessors for Actor.aVariantSlots. None of them are called.

// Switches the actor to drawing from its variant slots and resets each
// slot: no tile allocation, the actor's palette bank, and no tables.
void EnableActorVariantSlots(Actor *actor)
{
    s32 i;

    actor->bDrawFlags |= ActorDrawFlagVariantSlots;
    for (i = 0; i < ARRAY_COUNT(actor->aVariantSlots); i++) {
        actor->aVariantSlots[i].wVramTileAllocId |= 0xFFFF;
        actor->aVariantSlots[i].bPaletteBank = actor->oam.paletteNum;
        actor->aVariantSlots[i].pSpriteVariantTables = NULL;
    }
}

void DisableActorVariantSlots(Actor *actor)
{
    actor->bDrawFlags &= ~ActorDrawFlagVariantSlots;
}

void AssignActorVariantSlot(Actor *actor, u8 slot, ActorAssetRecord **tables, u8 paletteBank)
{
    actor->aVariantSlots[slot].pSpriteVariantTables = tables;
    actor->aVariantSlots[slot].bPaletteBank = paletteBank;
}

// A slot without tables is not drawn.
void ClearActorVariantSlot(Actor *actor, u8 slot)
{
    actor->aVariantSlots[slot].pSpriteVariantTables = NULL;
}

void EnableActorVariantSlotBlink(Actor *actor, u8 slot)
{
    actor->aVariantSlots[slot].bFrameFlags |= ActorVariantSlotFlagBlink;
}

void DisableActorVariantSlotBlink(Actor *actor, u8 slot)
{
    actor->aVariantSlots[slot].bFrameFlags &= ~ActorVariantSlotFlagBlink;
}

void SetActorVariantSlotPalette(Actor *actor, u8 slot, u8 paletteBank)
{
    actor->aVariantSlots[slot].bPaletteBank = paletteBank;
}

void SetActorVariantSlotDrawOrder(Actor *actor, u8 slot, u8 drawOrder)
{
    actor->aVariantSlots[slot].bDrawOrder = drawOrder;
}

void EnableActorVariantSlotBounds(Actor *actor, u8 slot)
{
    actor->aVariantSlots[slot].bFrameFlags |= ActorVariantSlotFlagBounds;
}

void DisableActorVariantSlotBounds(Actor *actor, u8 slot)
{
    actor->aVariantSlots[slot].bFrameFlags &= ~ActorVariantSlotFlagBounds;
}

void EnableActorVariantSlotPrevFrame(Actor *actor, u8 slot)
{
    actor->aVariantSlots[slot].bFrameFlags |= ActorVariantSlotFlagPrevFrameWrap;
}

void DisableActorVariantSlotPrevFrame(Actor *actor, u8 slot)
{
    actor->aVariantSlots[slot].bFrameFlags &= ~ActorVariantSlotFlagPrevFrameWrap;
}
