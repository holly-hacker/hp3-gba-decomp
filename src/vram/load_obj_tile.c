#include "types.h"
#include "graphics/graphics.h"
#include "actor.h"
#include "hw/io_regs.h"
#include "vram.h"

// Decompresses an object's frame tiles into its allocation in OBJ VRAM.
void LoadObjTile(Object *obj, void *tileGfx)
{
    DecompressResourceVram(tileGfx, OBJ_VRAM_TILES + obj->wVramTileAllocId * 32);
}
