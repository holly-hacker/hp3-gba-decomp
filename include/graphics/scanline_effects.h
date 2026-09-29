#pragma once

#include "types.h"

// See docs/memory-map/scanline_effects.md.
extern void QueueScanlineEffectTable(const void *pEntries, u32 count);
extern void StartScanlineEffects(void);
extern u32 IsScanlineEffectQueueIdle(void);
