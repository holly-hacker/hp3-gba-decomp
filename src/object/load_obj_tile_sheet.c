#include "types.h"
#include "graphics/graphics.h"
#include "graphics/object.h"
#include "hw/io_regs.h"

// Decompresses every frame of a sprite record's tile graphics into OBJ VRAM,
// back to back starting at tile firstTile. Each frame occupies width * height / 2
// bytes (4bpp).
void LoadObjTileSheet(ObjectAssetRecord *record, u16 firstTile)
{
    ObjectFrameData *frameData = record->pFrameData;
    u32 byteOffset = 0;
    u32 i;

    for (i = 0; i < ((ObjectFrameData *)record->pFrameData)->wFrameCount; i++) {
        ObjectFrameDesc *desc = (ObjectFrameDesc *)((u8 *)frameData->awFrameOffsets
                                                    + frameData->awFrameOffsets[i]);
        u8 *pDest = OBJ_VRAM_TILES + firstTile * 32 + byteOffset;

        byteOffset += desc->bWidth * desc->bHeight / 2;
        DecompressResourceVram((u8 *)record->pTileGfx + desc->wTileGfxOffset, pDest);
    }
}
