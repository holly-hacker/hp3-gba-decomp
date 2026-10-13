#include "types.h"
#include "background.h"

void GetBgSizePixels(u32 bg, u16 *pWidth, u16 *pHeight)
{
    switch (g_BgState.aLayers[bg].control.bSize)
    {
    case 1:
        *pWidth = 0x200;
        *pHeight = 0x100;
        break;
    case 2:
        *pWidth = 0x100;
        *pHeight = 0x200;
        break;
    case 3:
        *pWidth = 0x200;
        *pHeight = 0x200;
        break;
    default:
        *pWidth = 0x100;
        *pHeight = 0x100;
        break;
    }
}
