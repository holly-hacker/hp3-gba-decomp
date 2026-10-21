#include "types.h"
#include "background.h"
#include "hedwig_minigame.h"

// Mail and Upload sit 5 tiles further right than the care actions.
void DrawOwlCareKitMenuIcon(u32 entry, u32 highlighted)
{
    u32 srcX;
    u32 srcY;
    u32 dstX;

    srcX = entry * 3 + 6;
    srcY = 20;
    dstX = entry * 3 + 1;
    if (highlighted)
        srcY = 24;
    if (entry > 5)
    {
        srcX = entry * 3 - 12;
        srcY += 8;
        dstX = entry * 3 + 6;
    }
    CopyBgTilemapRectByCell(0, g_BgState.aLayers[0].pTilemap, 0x156, 0, srcX, srcY, dstX, 16, 3, 4);
}
