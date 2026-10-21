#include "types.h"
#include "background.h"
#include "hedwig_minigame.h"

// Draws a meter as a 6x1-tile bar filled to value / 250 of 48 pixels.
void DrawOwlStatMeterBar(u32 meter, u32 value)
{
    u32 empty;
    u32 srcX;
    u32 srcY;

    empty = 48 - (value * 48 + 249) / 250;
    if (empty <= 28)
    {
        srcX = 0;
        srcY = empty + 20;
    }
    else
    {
        srcX = 24;
        srcY = empty - 8;
    }
    CopyBgTilemapRectByCell(0, g_BgState.aLayers[0].pTilemap, 0x156, 0, srcX, srcY, 3, meter * 2 + 2, 6, 1);
}
