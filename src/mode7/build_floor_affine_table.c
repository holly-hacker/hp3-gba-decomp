#include "types.h"
#include "mode7.h"
#include "hw/bios.h"
#include "math.h"

// Defined old-style: callers pass the heading promoted to int, the definition narrows it.
void BuildFloorAffineTable(heading, cameraX, cameraY, cameraHeight, viewDistance, horizonOffset)
    u8 heading;
    s32 cameraX;
    s32 cameraY;
    s32 cameraHeight;
    s32 viewDistance;
    s32 horizonOffset;
{
    BgAffineSrc src;
    s32 i;
    s32 scale;
    s32 floorTop;
    s32 depth;

    for (i = 0; i < FLOOR_SCANLINE_COUNT; i++)
    {
        if (i < g_nFloorHorizonLine)
        {
            src.texX = 0x8C00;
            src.texY = 0xE000;
            src.scrX = 120;
            src.scrY = g_nFloorHorizonLine + (viewDistance - i);
            src.sx = 0x100;
            src.sy = 0x100;
            src.alpha = 0xFF;
            bios_BgAffineSet(&src, &g_pFloorAffineTable[i], 1);
        }
        else
        {
            src.texX = cameraX;
            src.texY = cameraY;
            src.scrX = 120;
            src.scrY = viewDistance;
            scale = cameraHeight * 80;
            floorTop = horizonOffset + 3;

            depth = i - (g_nFloorHorizonLine - floorTop);
            depth = depth > 0 ? depth : 1;
            src.sx = iwramDivideSignedQuotient(scale, depth);

            depth = i - (g_nFloorHorizonLine - floorTop);
            depth = depth > 0 ? depth : 1;
            src.sy = iwramDivideSignedQuotient(scale, depth);

            src.alpha = heading << 8;
            bios_BgAffineSet(&src, &g_pFloorAffineTable[i], 1);
        }
    }
}
