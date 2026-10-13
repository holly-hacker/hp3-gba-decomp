#include "types.h"
#include "background.h"

void SetBgTilemapRectPalette(u32 bg, u32 x, u32 y, s32 w, s32 h, u16 palBank)
{
    BgLayer *pLayer = &g_BgState.aLayers[bg];

    SetTilemapRectPalette(pLayer->pScreenBaseAlt, x, y, w, h, palBank);
}
