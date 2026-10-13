#include "types.h"
#include "background.h"

void ClearBgTilemapRect(u32 bg, u32 x, u32 y, s32 w, s32 h)
{
    FillBgTilemapRect(bg, x, y, w, h, 0);
}
