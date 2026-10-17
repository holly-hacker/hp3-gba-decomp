#include "types.h"
#include "decompress.h"
#include "actor.h"
#include "hw/io_regs.h"
#include "vram.h"

// Decompresses a variant slot's frame tiles into OBJ VRAM at tile allocId.
void LoadObjTileAt(ActorFrameData *frameData, void *tileGfx, u16 allocId, u16 frame,
                   u16 pixelCount)
{
    DecompressResourceVram(tileGfx, OBJ_VRAM_TILES + allocId * 32);
}
