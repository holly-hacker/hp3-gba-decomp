#include "types.h"
#include "decompress.h"
#include "actor.h"
#include "hw/io_regs.h"
#include "vram.h"

// Decompresses every frame of a sprite record's tile graphics into OBJ VRAM,
// back to back starting at tile firstTile. Each frame occupies width * height / 2
// bytes (4bpp).
void LoadObjTileSheet(const ActorAssetRecord *record, u16 firstTile)
{
    ActorFrameData *frameData = record->pFrameData;
    u32 byteOffset = 0;
    u32 i;

    for (i = 0; i < record->pFrameData->wFrameCount; i++) {
        ActorFrameDesc *desc = ACTOR_FRAME_DESC(frameData, i);
        u8 *pDest = OBJ_VRAM_TILES + firstTile * 32 + byteOffset;

        byteOffset += desc->bWidth * desc->bHeight / 2;
        DecompressResourceVram((u8 *)record->pTileGfx + desc->wTileGfxOffset, pDest);
    }
}
