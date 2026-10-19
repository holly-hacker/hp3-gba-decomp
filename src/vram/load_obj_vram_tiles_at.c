#include "types.h"
#include "actor.h"
#include "vram.h"

// AllocObjVramTiles for an existing allocation: loads record's tile sheet at
// firstTile when record is given. Returns firstTile.
u16 LoadObjVramTilesAt(const ActorAssetRecord *record, u32 pixelCount, u8 is8bpp, u16 firstTile)
{
    if (record != NULL) {
        // Both pixel formats load through the 4bpp tile sheet loader.
        if (!is8bpp)
            LoadObjTileSheet(record, firstTile);
        else
            LoadObjTileSheet(record, firstTile);
    }

    return firstTile;
}
