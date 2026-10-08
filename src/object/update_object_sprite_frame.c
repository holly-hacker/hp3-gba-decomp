#include "types.h"
#include "graphics/object.h"
#include "hw/mem.h"
#include "game/game_modes.h"

// ObjectDrawFlagShareTiles: one allocation per pool aux record, reloaded at
// most once per tick. ObjectDrawFlagShareFrameTiles: one refcounted
// allocation per animation frame. Otherwise a fresh allocation per object.
void UpdateObjectSpriteFrame(Object *obj, u32 mode)
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
    u32 slotAllocId;
    u8 i;
    ObjectAssetRecord *record;
    ObjectFrameData *frameData;
    ObjectFrameData *slotFrameData;
    ObjectFrameDesc *frameDesc;
    void *tileGfx;
    u8 tableIndex;
    u8 variantIndex;
    u32 wrap;
    s32 frame;

    loadTiles = 1;
    flags = obj->dwFlags;
    drawFlags = obj->bDrawFlags;

    if (mode == 1
        && (flags & (ObjectFlagOnscreenForTileAlloc | ObjectFlagSkipSpriteFrameUpdate | ObjectFlagPendingDestroy))
               == ObjectFlagOnscreenForTileAlloc
        && ((flags & ObjectFlagAnimFrameLoaded) || obj->wVramTileAllocId == 0xFFFF)) {
        record = obj->pAnimTable;
        frameData = record->pFrameData;
        frameDesc = (ObjectFrameDesc *)((u8 *)frameData->awFrameOffsets
                                        + frameData->awFrameOffsets[obj->bLastAnimFrameValue]);
        dims[0] = frameDesc->bWidth;
        dims[1] = frameDesc->bHeight;
        pixelCount = dims[0] * dims[1];

        if (drawFlags & (ObjectDrawFlagShareTiles | ObjectDrawFlagShareFrameTiles)) {
            if (drawFlags & ObjectDrawFlagShareTiles) {
                index = 0;
                if ((g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].pAnimTable != record
                     || g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].abRefCounts[index] == 0
                     || g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].bAnimFrame != obj->bLastAnimFrameValue)
                    && g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].dwAllocTick != g_dwTickCount) {
                    if (obj->wVramTileAllocId != 0xFFFF) {
                        FreeObjectVramTileAllocation(obj->wVramTileAllocId, obj->wVramPixelCount,
                                                     obj->oam.bpp8);
                        obj->wVramTileAllocId |= 0xFFFF;
                    }
                    else {
                        g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].abRefCounts[index]++;
                    }
                    g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].pAnimTable = obj->pAnimTable;
                    allocId = AllocObjectVramTiles(NULL, pixelCount, obj->oam.bpp8);
                    g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].bAnimFrame = obj->bLastAnimFrameValue;
                    g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].awTileAllocIds[index] = allocId;
                    g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].dwAllocTick = g_dwTickCount;
                }
                else {
                    if (obj->wVramTileAllocId == 0xFFFF)
                        g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].abRefCounts[index]++;
                    allocId = g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].awTileAllocIds[index];
                    loadTiles = 0;
                }
            }
            else {
                index = obj->bLastAnimFrameValue;
                if (g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].abRefCounts[index] == 0) {
                    allocId = AllocObjectVramTiles(NULL, pixelCount, obj->oam.bpp8);
                    g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].awTileAllocIds[index] = allocId;
                }
                else {
                    allocId = g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].awTileAllocIds[index];
                    loadTiles = 0;
                }
                g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].abRefCounts[index]++;

                prevIndex = obj->bAnimFrameIndex_candidate;
                if (index != prevIndex && obj->wVramTileAllocId != 0xFFFF) {
                    g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].abRefCounts[prevIndex]--;
                    if (g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].abRefCounts[obj->bAnimFrameIndex_candidate] == 0) {
                        FreeObjectVramTileAllocation(obj->wVramTileAllocId, obj->wVramPixelCount,
                                                     obj->oam.bpp8);
                        obj->wVramTileAllocId |= 0xFFFF;
                        g_pObjectPoolAuxBuffer[obj->bObjectPoolAuxSlot].awTileAllocIds[obj->bAnimFrameIndex_candidate] |= 0xFFFF;
                    }
                }
            }
        }
        else {
            if (obj->wVramTileAllocId != 0xFFFF)
                FreeObjectVramTileAllocation(obj->wVramTileAllocId, obj->wVramPixelCount, obj->oam.bpp8);
            allocId = AllocObjectVramTiles(NULL, pixelCount, obj->oam.bpp8);

            if (obj->bDrawFlags & ObjectDrawFlagVariantSlots) {
                for (i = 0; i < ARRAY_COUNT(obj->aVariantSlots); i++) {
                    if (obj->aVariantSlots[i].pSpriteVariantTables != NULL) {
                        GetObjectVariantFrameSize(obj, dims, i);
                        slotPixelCount = dims[0] * dims[1];
                        if (obj->aVariantSlots[i].wVramTileAllocId != 0xFFFF)
                            FreeObjectVramTileAllocation(obj->aVariantSlots[i].wVramTileAllocId,
                                                         obj->aVariantSlots[i].wVramPixelCount,
                                                         obj->oam.bpp8);
                        slotAllocId = AllocObjectVramTiles(NULL, slotPixelCount, obj->oam.bpp8);
                        if (slotAllocId != 0xFFFF) {
                            obj->aVariantSlots[i].wVramTileAllocId = slotAllocId;
                            obj->aVariantSlots[i].wVramPixelCount = slotPixelCount;
                        }
                        else {
                            obj->aVariantSlots[i].wVramTileAllocId |= 0xFFFF;
                            obj->aVariantSlots[i].wVramPixelCount = 0;
                        }
                    }
                }
            }
        }

        if (allocId == 0xFFFF) {
            loadTiles = 0;
            pixelCount = 0;
        }
        obj->wVramTileAllocId = allocId;
        obj->oam.tileNum = allocId;
        obj->wVramPixelCount = pixelCount;

        if (loadTiles) {
            if (obj->bDrawFlags & ObjectDrawFlagVariantSlots) {
                for (i = 0; i < ARRAY_COUNT(obj->aVariantSlots); i++) {
                    if (obj->aVariantSlots[i].pSpriteVariantTables != NULL
                        && obj->aVariantSlots[i].wVramTileAllocId != 0xFFFF) {
                        tileGfx = GetObjectVariantFrameTileGfx(obj, i);
                        tableIndex = obj->bSpriteVariantTableIndex;
                        variantIndex = obj->bSpriteVariantIndex;
                        slotFrameData = obj->aVariantSlots[i].pSpriteVariantTables[tableIndex][variantIndex].pFrameData;
                        wrap = obj->aVariantSlots[i].bFrameFlags & ObjectVariantSlotFlagPrevFrameWrap;
                        if (wrap || (obj->aVariantSlots[i].bFrameFlags & ObjectVariantSlotFlagPrevFrameClamp)) {
                            frame = obj->bLastAnimFrameValue - 1;
                            if (frame < 0) {
                                if (wrap)
                                    frame = slotFrameData->wFrameCount - 1;
                                else
                                    frame = 0;
                            }
                        }
                        else {
                            frame = obj->bLastAnimFrameValue;
                        }
                        LoadObjTileAt(obj->aVariantSlots[i].pSpriteVariantTables[tableIndex][variantIndex].pFrameData,
                                      tileGfx, obj->aVariantSlots[i].wVramTileAllocId, frame,
                                      obj->aVariantSlots[i].wVramPixelCount);
                    }
                }
            }
            else {
                ObjectFrameData *animFrameData;
                ObjectFrameDesc *animFrameDesc;

                animFrameData = obj->pAnimTable->pFrameData;
                animFrameDesc = (ObjectFrameDesc *)((u8 *)animFrameData->awFrameOffsets
                                                    + animFrameData->awFrameOffsets[obj->bLastAnimFrameValue]);
                tileGfx = (u8 *)obj->pAnimTable->pTileGfx + animFrameDesc->wTileGfxOffset;
                LoadObjTile(obj, tileGfx);
            }
        }
        obj->dwFlags |= ObjectFlagAnimFrameLoaded;
    }

    obj->bAnimFrameIndex_candidate = obj->bLastAnimFrameValue;
}
