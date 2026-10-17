#include "types.h"
#include "actor.h"
#include "oam.h"
#include "scroll.h"

// Queues this frame's OAM entries for an actor. Returns 0 without drawing when
// ActorFlagOnscreenForTileAlloc is clear and 2 when the actor has no VRAM tile
// allocation. Otherwise it draws and returns 2 after drawing through
// WriteActorOamCells, else 1. TickActorList queues actors that returned 2
// for CommitQueuedActorTileUpdates.
//
// A nonzero bForceOnscreen_candidate draws a horizontal strip: actor->oam itself
// is queued unk_DC.wOamStripCount times, 32 pixels apart. Otherwise the cells
// of the current animation frame are drawn, either inline (while
// ActorFlagSkipSpriteFrameUpdate is set) or with WriteActorOamCells, from
// the animation table or from each variant slot in bDrawOrder order.
u8 UpdateActorOamCells(Actor *actor)
{
    OamEntry oam;
    s32 screenPos[2];
    OamEntry cell;
    s32 dims[2];
    FixedPoint position;
    u32 flags;
    u32 cellFlags;
    ActorFrameData *frameData;
    ActorFrameDesc *frameDesc;
    ActorFrameCell *frameCell;
    u32 tileBase;
    u32 result;
    u32 i;
    u32 affineMode;
    u32 slot;
    s32 order;
    s32 frame;
    u32 wrap;
    u32 count;

    oam = actor->oam;
    position = actor->posPrev;
    flags = actor->dwFlags;
    cellFlags = (actor->bDrawFlags & ActorDrawFlagExtraOamPass) ? 2 : 0;

    if (!(flags & ActorFlagOnscreenForTileAlloc))
        return 0;
    if (actor->wVramTileAllocId == 0xFFFF)
        return 2;

    if (actor->bForceOnscreen_candidate == 0) {
        if (flags & ActorFlagHasSpriteCells) {
            screenPos[0] = position.x >> 16;
            screenPos[1] = position.y >> 16;
        }
        else {
            GetCameraPosition(screenPos);
            screenPos[0] = (position.x >> 16) - screenPos[0];
            screenPos[1] = (position.y >> 16) - screenPos[1];
            oam.x = screenPos[0];
            oam.y = screenPos[1];
            actor->oam = oam;
        }
        result = 1;

        if (flags & ActorFlagSkipSpriteFrameUpdate) {
            frameData = actor->anim.pAnimTable->pFrameData;
            frameDesc = (ActorFrameDesc *)((u8 *)frameData->awFrameOffsets
                                            + frameData->awFrameOffsets[actor->anim.bLastAnimFrameValue]);
            count = frameDesc->bCellCount & 0x1F;
            frameCell = (ActorFrameCell *)((u8 *)frameDesc + (frameData->bFramePartCount * 6 + 10)
                                            + frameData->bAnchorCount * 2);
            if (!actor->oam.bpp8)
                tileBase = (frameDesc->wTileGfxOffset >> 5) + actor->wVramTileAllocId;
            else
                tileBase = (frameDesc->wTileGfxOffset >> 6) + actor->wVramTileAllocId;

            for (i = 0; i < count; i++) {
                cell = oam;
                cell.tileNum = tileBase + frameCell->tileOffset;
                cell.size = frameCell->size;
                cell.shape = frameCell->shape;
                affineMode = actor->oam.affineMode;
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

                if (actor->bDrawFlags & ActorDrawFlagBlink)
                    HideOamEntryOnAlternateVblanks(g_bOamEntryCount);
                if (actor->bDrawFlags & ActorDrawFlagPostActionFlash)
                    SubmitOamAttrsNudged(g_bOamEntryCount, &cell);
                else
                    QueueOamEntry(g_bOamEntryCount, &cell);
            }
            actor->anim.bAnimFrameIndex_candidate = actor->anim.bLastAnimFrameValue;
        }
        else {
            if (actor->bDrawFlags & ActorDrawFlagVariantSlots) {
                for (order = 7; order >= 0; order--) {
                    for (slot = 0; slot < ARRAY_COUNT(actor->aVariantSlots); slot++) {
                        if (actor->aVariantSlots[slot].pSpriteVariantTables != NULL
                            && actor->aVariantSlots[slot].bDrawOrder == order) {
                            s32 tableIndex;
                            s32 variantIndex;

                            cell = oam;
                            tableIndex = actor->bSpriteVariantTableIndex;
                            variantIndex = actor->bSpriteVariantIndex;
                            if (actor->aVariantSlots[slot].bFrameFlags & ActorVariantSlotFlagBlink)
                                cellFlags |= 1;
                            else
                                cellFlags &= ~1;
                            cell.paletteNum = actor->aVariantSlots[slot].bPaletteBank;
                            frameData = actor->aVariantSlots[slot].pSpriteVariantTables[tableIndex][variantIndex].pFrameData;
                            wrap = actor->aVariantSlots[slot].bFrameFlags & ActorVariantSlotFlagPrevFrameWrap;
                            if (wrap || (actor->aVariantSlots[slot].bFrameFlags & ActorVariantSlotFlagPrevFrameClamp)) {
                                frame = actor->anim.bLastAnimFrameValue - 1;
                                if (frame < 0) {
                                    if (wrap)
                                        frame = frameData->wFrameCount - 1;
                                    else
                                        frame = 0;
                                }
                            }
                            else {
                                frame = actor->anim.bLastAnimFrameValue;
                            }
                            WriteActorOamCells(actor->aVariantSlots[slot].pSpriteVariantTables[tableIndex][variantIndex].pFrameData,
                                                frame, cellFlags, screenPos,
                                                actor->aVariantSlots[slot].wVramTileAllocId, &cell, actor);
                        }
                    }
                }
            }
            else {
                cell = oam;
                if (actor->bDrawFlags & ActorDrawFlagBlink)
                    cellFlags |= 1;
                else
                    cellFlags &= ~1;
                WriteActorOamCells(actor->anim.pAnimTable->pFrameData, actor->anim.bLastAnimFrameValue, cellFlags,
                                    screenPos, actor->wVramTileAllocId, &cell, actor);
            }
            result++;
        }
    }
    else {
        GetCameraPosition(screenPos);
        if (flags & ActorFlagHasSpriteCells) {
            actor->oam.x = (s32)actor->posPrev.x >> 16;
            actor->oam.y = (s32)actor->posPrev.y >> 16;
        }
        else {
            actor->oam.x = ((s32)actor->posPrev.x >> 16) - screenPos[0];
            actor->oam.y = ((s32)actor->posPrev.y >> 16) - screenPos[1];
        }
        actor->oam.tileNum = actor->wVramTileAllocId;
        for (count = actor->anim.unk_DC.wOamStripCount; count != 0; count--) {
            if (actor->bDrawFlags & ActorDrawFlagBlink)
                HideOamEntryOnAlternateVblanks(g_bOamEntryCount);
            if (actor->bDrawFlags & ActorDrawFlagPostActionFlash)
                SubmitOamAttrsNudged(g_bOamEntryCount, &actor->oam);
            else
                QueueOamEntry(g_bOamEntryCount, &actor->oam);
            actor->oam.x += 32;
            actor->oam.tileNum += actor->oam.size << 2;
        }
        result = 1;
    }
    return result;
}
