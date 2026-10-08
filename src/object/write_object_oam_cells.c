#include "types.h"
#include "graphics/object.h"
#include "graphics/oam.h"
#include "hw/mem.h"

// cellFlags bit 1 (TickObjectList's extra OAM pass) mirrors the sprite
// vertically; bits 0-1 show the cells on alternate vblanks only.
void WriteObjectOamCells(ObjectFrameData *frameData, u16 frame, u8 cellFlags, s32 *pos,
                         u16 tileBase, OamEntry *pTemplate, Object *obj)
{
    OamEntry cell;
    s32 dims[2];
    ObjectFrameDesc *frameDesc;
    ObjectFrameCell *frameCell;
    s32 scaleX;
    s32 scaleY;
    u32 count;
    s32 x;
    s32 y;
    s32 screenY;

    frameDesc = (ObjectFrameDesc *)((u8 *)frameData->awFrameOffsets + frameData->awFrameOffsets[frame]);
    frameCell = (ObjectFrameCell *)((u8 *)frameDesc + (frameData->bFramePartCount * 6 + 10)
                                    + frameData->bFrameHeaderExtra * 2);
    scaleX = obj->nAffineScaleX;
    scaleY = obj->nAffineScaleY;

    for (count = frameDesc->bCellCount & 0x1F; count != 0; count--) {
        cell = *pTemplate;
        if (!cell.bpp8)
            cell.tileNum = tileBase + frameCell->tileOffset;
        else
            cell.tileNum = tileBase + frameCell->tileOffset * 2;
        cell.size = frameCell->size;
        cell.shape = frameCell->shape;
        GetOamShapeSizeDims(cell.shape, cell.size, dims);

        if (cell.affineMode == 0) {
            if (cell.hFlip == 1)
                x = -(frameCell->x + dims[0]);
            else
                x = frameCell->x;
        }
        else {
            x = (frameCell->x + dims[0] / 2) * scaleX;
            if (x >= 0)
                x = (x + g_dwUnk03001DC4) >> 16;
            else
                x = -((g_dwUnk03001DC4 - x) >> 16);
            if (cell.affineMode == 3)
                x -= dims[0];
            else
                x -= dims[0] / 2;
        }
        cell.x = pos[0] + x;

        if (cell.affineMode == 0) {
            if (cell.vFlip)
                y = -(frameCell->y + dims[1]);
            else if (cellFlags & 2) {
                y = -(frameCell->y + dims[1]);
                cell.vFlip = 1;
                cell.priority = g_ObjectPoolState.bExtraOamPassEnabled_candidate;
            }
            else
                y = frameCell->y;
        }
        else {
            y = (frameCell->y + dims[1] / 2) * scaleY;
            if (y >= 0)
                y = (y + g_dwUnk03001DC4) >> 16;
            else
                y = -((g_dwUnk03001DC4 - y) >> 16);
            if (cell.affineMode == 3)
                y -= dims[1];
            else
                y -= dims[1] / 2;
        }
        screenY = pos[1] + y;
        frameCell++;

        if ((u32)(screenY + 64) <= 256) {
            cell.y = screenY;
            if (obj->bDrawFlags & ObjectDrawFlagPostActionFlash)
                SubmitOamAttrsNudged(g_bOamEntryCount, &cell);
            else
                QueueOamEntry(g_bOamEntryCount, &cell);
            if (cellFlags & 3)
                HideOamEntryOnAlternateVblanks(g_bOamEntryCount - 1);
        }
    }
}
