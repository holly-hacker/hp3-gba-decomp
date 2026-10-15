#include "types.h"
#include "mode7.h"
#include "hw/io_regs.h"
#include "math.h"

void UpdateFloorAffineTable(void)
{
    u8 heading;
    s32 sine;
    s32 cosine;

    heading = g_FloorEffect.bHeading;
    sine = g_anSineTable[heading] >> 8;
    cosine = g_anSineTable[(heading + 0x40) & 0xFF] >> 8;

    if (g_FloorEffect.wForwardSpeed != 0)
    {
        g_FloorEffect.dwCameraX += (sine * g_FloorEffect.wForwardSpeed) >> 8;
        g_FloorEffect.dwCameraY -= (cosine * g_FloorEffect.wForwardSpeed) >> 8;
    }

    if (g_dwFloorScrollSky)
    {
        REG_BGHOFS(1) = (s8)g_FloorEffect.bHeading * 3;
        REG_BGVOFS(1) = g_FloorEffect.nHorizonOffset + 20;
    }

    BuildFloorAffineTable((s8)heading,
                          g_FloorEffect.dwCameraX - sine * g_FloorEffect.dwCameraBackoff,
                          g_FloorEffect.dwCameraY + cosine * g_FloorEffect.dwCameraBackoff,
                          g_FloorEffect.dwCameraHeight, g_FloorEffect.dwViewDistance,
                          g_FloorEffect.nHorizonOffset + 26);
}
