#include "types.h"
#include "graphics/graphics.h"
#include "graphics/object.h"
#include "hw/io_regs.h"

// Decompresses a variant slot's frame tiles into OBJ VRAM at tile allocId.
void LoadObjTileAt(ObjectFrameData *frameData, void *tileGfx, u16 allocId, u16 frame,
                   u16 pixelCount)
{
    DecompressResourceVram(tileGfx, OBJ_VRAM_TILES + allocId * 32);
}
