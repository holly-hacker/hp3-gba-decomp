#include "types.h"
#include "decompress.h"
#include "graphics/graphics.h"
#include "actor.h"
#include "hw/io_regs.h"
#include "vram.h"

// Decompresses an actor's frame tiles into its allocation in OBJ VRAM.
void LoadObjTile(Actor *actor, void *tileGfx)
{
    DecompressResourceVram(tileGfx, OBJ_VRAM_TILES + actor->wVramTileAllocId * 32);
}
