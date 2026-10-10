#include "types.h"
#include "font.h"
#include "hw/io_regs.h"

// Points the text renderer at the tilemap and tiles of the BG whose BGxCNT
// value is bgControl: screen block (bits 8-12), character block (bits 2-3)
// and 8 bpp flag (bit 7).
void SetTextTargetFromBgControl(u32 bgControl)
{
    u8 *pTilemap;
    u8 *pTiles;
    u32 tileSize;

    pTilemap = (u8 *)VRAM_BASE + ((bgControl << 19) >> 27) * 0x800;
    pTiles = (u8 *)VRAM_BASE + ((bgControl << 28) >> 30) * 0x4000;
    gTextRenderState.pTilemap = (u16 *)pTilemap;
    gTextRenderState.pTilemapBase = (u16 *)pTilemap;
    gTextRenderState.pTiles = pTiles;
    tileSize = (bgControl << 24) >> 31;
    tileSize = (tileSize + 1) * 0x20;
    gTextRenderState.tileSize = tileSize;
    gTextRenderState.is8bpp = (bgControl << 24) >> 31;
}
