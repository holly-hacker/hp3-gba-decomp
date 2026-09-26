#include "types.h"
#include "object.h"
#include "room.h"
#include "oam.h"

// Queues this frame's OAM entries for an object. Returns 0 without drawing when
// ObjectFlagOnscreenForTileAlloc is clear and 2 when the object has no VRAM tile
// allocation. Otherwise it draws and returns 2 after drawing through
// WriteObjectOamCells, else 1. TickObjectList queues objects that returned 2
// for CommitQueuedObjectTileUpdates.
//
// A nonzero bForceOnscreen_candidate draws a horizontal strip: obj->oam itself
// is queued unk_DC.wOamStripCount times, 32 pixels apart. Otherwise the cells
// of the current animation frame are drawn, either inline (while
// ObjectFlagSkipSpriteFrameUpdate is set) or with WriteObjectOamCells, from
// the animation table or from each variant slot in bDrawOrder order.
u8 UpdateObjectOamCells(Object *obj)
{
    OamEntry oam;
    s32 screenPos[2];
    OamEntry cell;
    s32 dims[2];
    FixedPoint position;
    u32 flags;
    u32 cellFlags;
    ObjectFrameData *frameData;
    ObjectFrameDesc *frameDesc;
    ObjectFrameCell *frameCell;
    u32 tileBase;
    u32 result;
    u32 i;
    u32 affineMode;
    u32 slot;
    s32 order;
    s32 frame;
    u32 wrap;
    u32 count;

    oam = obj->oam;
    position = *(FixedPoint *)&obj->nXPrev;
    flags = obj->dwFlags;
    cellFlags = (obj->bDrawFlags & ObjectDrawFlagExtraOamPass) ? 2 : 0;

    if (!(flags & ObjectFlagOnscreenForTileAlloc))
        return 0;
    if (obj->wVramTileAllocId == 0xFFFF)
        return 2;

    if (obj->bForceOnscreen_candidate == 0) {
        if (flags & ObjectFlagHasSpriteCells) {
            screenPos[0] = position.x >> 16;
            screenPos[1] = position.y >> 16;
        }
        else {
            GetCameraPosition(screenPos);
            screenPos[0] = (position.x >> 16) - screenPos[0];
            screenPos[1] = (position.y >> 16) - screenPos[1];
            oam.x = screenPos[0];
            oam.y = screenPos[1];
            obj->oam = oam;
        }
        result = 1;

        if (flags & ObjectFlagSkipSpriteFrameUpdate) {
            frameData = obj->pAnimTable->pFrameData;
            frameDesc = (ObjectFrameDesc *)((u8 *)frameData->awFrameOffsets
                                            + frameData->awFrameOffsets[obj->bLastAnimFrameValue]);
            count = frameDesc->bCellCount & 0x1F;
            frameCell = (ObjectFrameCell *)((u8 *)frameDesc + (frameData->bFramePartCount * 6 + 10)
                                            + frameData->bFrameHeaderExtra * 2);
            if (!obj->oam.bpp8)
                tileBase = (frameDesc->wTileGfxOffset >> 5) + obj->wVramTileAllocId;
            else
                tileBase = (frameDesc->wTileGfxOffset >> 6) + obj->wVramTileAllocId;

            for (i = 0; i < count; i++) {
                cell = oam;
                cell.tileNum = tileBase + frameCell->tileOffset;
                cell.size = frameCell->size;
                cell.shape = frameCell->shape;
                affineMode = obj->oam.affineMode;
                if (affineMode == 3) {
                    cell.x = screenPos[0] + frameCell->x * 2;
                    cell.y = screenPos[1] + frameCell->y * 2;
                }
                else if (affineMode == 1) {
                    cell.x = screenPos[0] + frameCell->x;
                    cell.y = screenPos[1] + frameCell->y;
                }
                else {
                    GetOamShapeSizeDims(cell.shape, cell.size, dims);
                    if (cell.hFlip == 1)
                        cell.x = screenPos[0] - frameCell->x - dims[0];
                    else
                        cell.x = screenPos[0] + frameCell->x;
                    if (cell.vFlip)
                        cell.y = screenPos[1] - frameCell->y - dims[1];
                    else
                        cell.y = screenPos[1] + frameCell->y;
                }
                frameCell++;

                if (obj->bDrawFlags & ObjectDrawFlagBlink)
                    HideOamEntryOnAlternateVblanks(g_bOamEntryCount);
                if (obj->bDrawFlags & ObjectDrawFlagPostActionFlash)
                    SubmitOamAttrsNudged(g_bOamEntryCount, &cell);
                else
                    QueueOamEntry(g_bOamEntryCount, &cell);
            }
            obj->bAnimFrameIndex_candidate = obj->bLastAnimFrameValue;
        }
        else {
            if (obj->bDrawFlags & ObjectDrawFlagVariantSlots) {
                for (order = 7; order >= 0; order--) {
                    for (slot = 0; slot < 1; slot++) {
                        if (obj->aVariantSlots[slot].pSpriteVariantTables != NULL
                            && obj->aVariantSlots[slot].bDrawOrder == order) {
                            s32 tableIndex;
                            s32 variantIndex;

                            cell = oam;
                            tableIndex = obj->bSpriteVariantTableIndex;
                            variantIndex = obj->bSpriteVariantIndex;
                            if (obj->aVariantSlots[slot].bFrameFlags & ObjectVariantSlotFlagBlink)
                                cellFlags |= 1;
                            else
                                cellFlags &= ~1;
                            cell.paletteNum = obj->aVariantSlots[slot].bPaletteBank;
                            frameData = obj->aVariantSlots[slot].pSpriteVariantTables[tableIndex][variantIndex].pFrameData;
                            wrap = obj->aVariantSlots[slot].bFrameFlags & ObjectVariantSlotFlagPrevFrameWrap;
                            if (wrap || (obj->aVariantSlots[slot].bFrameFlags & ObjectVariantSlotFlagPrevFrameClamp)) {
                                frame = obj->bLastAnimFrameValue - 1;
                                if (frame < 0) {
                                    if (wrap)
                                        frame = frameData->wFrameCount - 1;
                                    else
                                        frame = 0;
                                }
                            }
                            else {
                                frame = obj->bLastAnimFrameValue;
                            }
                            WriteObjectOamCells(obj->aVariantSlots[slot].pSpriteVariantTables[tableIndex][variantIndex].pFrameData,
                                                frame, cellFlags, screenPos,
                                                obj->aVariantSlots[slot].wVramTileAllocId, &cell, obj);
                        }
                    }
                }
            }
            else {
                cell = oam;
                if (obj->bDrawFlags & ObjectDrawFlagBlink)
                    cellFlags |= 1;
                else
                    cellFlags &= ~1;
                WriteObjectOamCells(obj->pAnimTable->pFrameData, obj->bLastAnimFrameValue, cellFlags,
                                    screenPos, obj->wVramTileAllocId, &cell, obj);
            }
            result++;
        }
    }
    else {
        GetCameraPosition(screenPos);
        if (flags & ObjectFlagHasSpriteCells) {
            obj->oam.x = (s32)obj->nXPrev >> 16;
            obj->oam.y = (s32)obj->nYPrev >> 16;
        }
        else {
            obj->oam.x = ((s32)obj->nXPrev >> 16) - screenPos[0];
            obj->oam.y = ((s32)obj->nYPrev >> 16) - screenPos[1];
        }
        obj->oam.tileNum = obj->wVramTileAllocId;
        for (count = obj->unk_DC.wOamStripCount; count != 0; count--) {
            if (obj->bDrawFlags & ObjectDrawFlagBlink)
                HideOamEntryOnAlternateVblanks(g_bOamEntryCount);
            if (obj->bDrawFlags & ObjectDrawFlagPostActionFlash)
                SubmitOamAttrsNudged(g_bOamEntryCount, &obj->oam);
            else
                QueueOamEntry(g_bOamEntryCount, &obj->oam);
            obj->oam.x += 32;
            obj->oam.tileNum += obj->oam.size << 2;
        }
        result = 1;
    }
    return result;
}
