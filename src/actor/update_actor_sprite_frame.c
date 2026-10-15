#include "types.h"
#include "actor.h"
#include "mem.h"
#include "game/game_modes.h"
#include "vram.h"

// ActorDrawFlagShareTiles: one allocation per pool aux record, reloaded at
// most once per tick. ActorDrawFlagShareFrameTiles: one refcounted
// allocation per animation frame. Otherwise a fresh allocation per actor.
void UpdateActorSpriteFrame(Actor *actor, u32 mode)
{
    u32 dims[2];
    u16 allocId;
    u32 pixelCount;
    u32 loadTiles;
    u32 flags;
    u32 drawFlags;
    u32 index;
    u32 prevIndex;
    u16 slotPixelCount;
    u16 slotAllocId;
    u8 i;
    ActorAssetRecord *record;
    ActorFrameData *frameData;
    ActorFrameData *slotFrameData;
    ActorFrameDesc *frameDesc;
    void *tileGfx;
    u8 tableIndex;
    u8 variantIndex;
    u32 wrap;
    s32 frame;

    loadTiles = 1;
    flags = actor->dwFlags;
    drawFlags = actor->bDrawFlags;

    if (mode == 1
        && (flags & (ActorFlagOnscreenForTileAlloc | ActorFlagSkipSpriteFrameUpdate | ActorFlagPendingDestroy))
               == ActorFlagOnscreenForTileAlloc
        && ((flags & ActorFlagAnimFrameLoaded) || actor->wVramTileAllocId == 0xFFFF)) {
        record = actor->anim.pAnimTable;
        frameData = record->pFrameData;
        frameDesc = (ActorFrameDesc *)((u8 *)frameData->awFrameOffsets
                                        + frameData->awFrameOffsets[actor->anim.bLastAnimFrameValue]);
        dims[0] = frameDesc->bWidth;
        dims[1] = frameDesc->bHeight;
        pixelCount = dims[0] * dims[1];

        if (drawFlags & (ActorDrawFlagShareTiles | ActorDrawFlagShareFrameTiles)) {
            if (drawFlags & ActorDrawFlagShareTiles) {
                index = 0;
                if ((g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].pAnimTable != record
                     || g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].abRefCounts[index] == 0
                     || g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].bAnimFrame != actor->anim.bLastAnimFrameValue)
                    && g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].dwAllocTick != g_dwTickCount) {
                    if (actor->wVramTileAllocId != 0xFFFF) {
                        FreeObjVramTileAllocation(actor->wVramTileAllocId, actor->wVramPixelCount,
                                                     actor->oam.bpp8);
                        actor->wVramTileAllocId |= 0xFFFF;
                    }
                    else {
                        g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].abRefCounts[index]++;
                    }
                    g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].pAnimTable = actor->anim.pAnimTable;
                    allocId = AllocObjVramTiles(NULL, pixelCount, actor->oam.bpp8);
                    g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].bAnimFrame = actor->anim.bLastAnimFrameValue;
                    g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].awTileAllocIds[index] = allocId;
                    g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].dwAllocTick = g_dwTickCount;
                }
                else {
                    if (actor->wVramTileAllocId == 0xFFFF)
                        g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].abRefCounts[index]++;
                    allocId = g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].awTileAllocIds[index];
                    loadTiles = 0;
                }
            }
            else {
                index = actor->anim.bLastAnimFrameValue;
                if (g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].abRefCounts[index] == 0) {
                    allocId = AllocObjVramTiles(NULL, pixelCount, actor->oam.bpp8);
                    g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].awTileAllocIds[index] = allocId;
                }
                else {
                    allocId = g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].awTileAllocIds[index];
                    loadTiles = 0;
                }
                g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].abRefCounts[index]++;

                prevIndex = actor->anim.bAnimFrameIndex_candidate;
                if (index != prevIndex && actor->wVramTileAllocId != 0xFFFF) {
                    g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].abRefCounts[prevIndex]--;
                    if (g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].abRefCounts[actor->anim.bAnimFrameIndex_candidate] == 0) {
                        FreeObjVramTileAllocation(actor->wVramTileAllocId, actor->wVramPixelCount,
                                                     actor->oam.bpp8);
                        actor->wVramTileAllocId |= 0xFFFF;
                        g_pActorPoolAuxBuffer[actor->bActorPoolAuxSlot].awTileAllocIds[actor->anim.bAnimFrameIndex_candidate] |= 0xFFFF;
                    }
                }
            }
        }
        else {
            if (actor->wVramTileAllocId != 0xFFFF)
                FreeObjVramTileAllocation(actor->wVramTileAllocId, actor->wVramPixelCount, actor->oam.bpp8);
            allocId = AllocObjVramTiles(NULL, pixelCount, actor->oam.bpp8);

            if (actor->bDrawFlags & ActorDrawFlagVariantSlots) {
                for (i = 0; i < ARRAY_COUNT(actor->aVariantSlots); i++) {
                    if (actor->aVariantSlots[i].pSpriteVariantTables != NULL) {
                        GetActorVariantFrameSize(actor, dims, i);
                        slotPixelCount = dims[0] * dims[1];
                        if (actor->aVariantSlots[i].wVramTileAllocId != 0xFFFF)
                            FreeObjVramTileAllocation(actor->aVariantSlots[i].wVramTileAllocId,
                                                         actor->aVariantSlots[i].wVramPixelCount,
                                                         actor->oam.bpp8);
                        slotAllocId = AllocObjVramTiles(NULL, slotPixelCount, actor->oam.bpp8);
                        if (slotAllocId != 0xFFFF) {
                            actor->aVariantSlots[i].wVramTileAllocId = slotAllocId;
                            actor->aVariantSlots[i].wVramPixelCount = slotPixelCount;
                        }
                        else {
                            actor->aVariantSlots[i].wVramTileAllocId |= 0xFFFF;
                            actor->aVariantSlots[i].wVramPixelCount = 0;
                        }
                    }
                }
            }
        }

        if (allocId == 0xFFFF) {
            loadTiles = 0;
            pixelCount = 0;
        }
        actor->wVramTileAllocId = allocId;
        actor->oam.tileNum = allocId;
        actor->wVramPixelCount = pixelCount;

        if (loadTiles) {
            if (actor->bDrawFlags & ActorDrawFlagVariantSlots) {
                for (i = 0; i < ARRAY_COUNT(actor->aVariantSlots); i++) {
                    if (actor->aVariantSlots[i].pSpriteVariantTables != NULL
                        && actor->aVariantSlots[i].wVramTileAllocId != 0xFFFF) {
                        tileGfx = GetActorVariantFrameTileGfx(actor, i);
                        tableIndex = actor->bSpriteVariantTableIndex;
                        variantIndex = actor->bSpriteVariantIndex;
                        slotFrameData = actor->aVariantSlots[i].pSpriteVariantTables[tableIndex][variantIndex].pFrameData;
                        wrap = actor->aVariantSlots[i].bFrameFlags & ActorVariantSlotFlagPrevFrameWrap;
                        if (wrap || (actor->aVariantSlots[i].bFrameFlags & ActorVariantSlotFlagPrevFrameClamp)) {
                            frame = actor->anim.bLastAnimFrameValue - 1;
                            if (frame < 0) {
                                if (wrap)
                                    frame = slotFrameData->wFrameCount - 1;
                                else
                                    frame = 0;
                            }
                        }
                        else {
                            frame = actor->anim.bLastAnimFrameValue;
                        }
                        LoadObjTileAt(actor->aVariantSlots[i].pSpriteVariantTables[tableIndex][variantIndex].pFrameData,
                                      tileGfx, actor->aVariantSlots[i].wVramTileAllocId, frame,
                                      actor->aVariantSlots[i].wVramPixelCount);
                    }
                }
            }
            else {
                ActorFrameData *animFrameData;
                ActorFrameDesc *animFrameDesc;

                animFrameData = actor->anim.pAnimTable->pFrameData;
                animFrameDesc = (ActorFrameDesc *)((u8 *)animFrameData->awFrameOffsets
                                                    + animFrameData->awFrameOffsets[actor->anim.bLastAnimFrameValue]);
                tileGfx = (u8 *)actor->anim.pAnimTable->pTileGfx + animFrameDesc->wTileGfxOffset;
                LoadObjTile(actor, tileGfx);
            }
        }
        actor->dwFlags |= ActorFlagAnimFrameLoaded;
    }

    actor->anim.bAnimFrameIndex_candidate = actor->anim.bLastAnimFrameValue;
}
