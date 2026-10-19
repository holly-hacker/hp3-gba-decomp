#include "types.h"
#include "interrupts.h"
#include "video.h"

void ClearScanlineEffects(void)
{
    QueueScanlineEffectTable(g_aDefaultScanlineEffects, ARRAY_COUNT(g_aDefaultScanlineEffects));
    WaitForVBlankIntr();
}
