#include "types.h"
#include "mode7.h"
#include "video.h"

void InitFloorEffect(void)
{
    QueueScanlineEffectTable(g_aFloorScanlineEffects, 1);
    // BUG: This should call IsScanlineEffectQueueIdle(). Without the parentheses it tests the
    // function's address, which is never null, so this never waits.
    while (!IsScanlineEffectQueueIdle)
        ;
    StartScanlineEffects();

    g_FloorEffect.bHeading = 0x7C;
    g_FloorEffect.dwCameraHeight = 40;
    g_FloorEffect.dwViewDistance = 160;
    g_FloorEffect.dwCameraBackoff = 12;
    g_FloorEffect.wForwardSpeed = 0;
    g_FloorEffect.nHorizonOffset = 0;
}
