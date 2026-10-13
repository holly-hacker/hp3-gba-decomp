#include "types.h"
#include "background.h"

void FillBgTilemapRect(u32 bg, u32 x, u32 y, s32 w, s32 h, u16 tile)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    FillTilemapRect(pLayer->pScreenBaseAlt, x, y, w, h, tile);
}
