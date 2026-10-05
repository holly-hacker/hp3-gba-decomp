#pragma once

#include "types.h"

// See docs/memory-map/scanline_effects.md.

// One VCOUNT-triggered callback. A table ends at the first null pfnCallback.
typedef struct ScanlineEffectEntry {
    u16 wLine;               // 0x00, VCOUNT line the callback fires on (0xFFFF = unused)
    u16 wParam;              // 0x02
    u32 dwPayload0;          // 0x04, the callback receives the address of each payload word
    u32 dwPayload1;          // 0x08
    void (*pfnCallback)(u32 *pPayload0, u32 *pPayload1);  // 0x0C
} ScanlineEffectEntry;

#define SCANLINE_EFFECT_TABLE_SIZE 19

typedef struct ScanlineEffectState {
    u32 dwPending;                // 0x000, 1 = aStaging waits to be committed
    volatile u32 dwActiveIndex;   // 0x004, advanced by ScanlineEffectVCountCallback
    ScanlineEffectEntry aEntries[SCANLINE_EFFECT_TABLE_SIZE];  // 0x008, live table
    ScanlineEffectEntry aStaging[SCANLINE_EFFECT_TABLE_SIZE];  // 0x138
} ScanlineEffectState;
extern ScanlineEffectState g_ScanlineEffectState;

// One entry: line 0, ScanlineEffectNop.
extern const ScanlineEffectEntry g_aDefaultScanlineEffects[1];

extern void ScanlineEffectNop(u32 *pPayload0, u32 *pPayload1);
extern void ScanlineEffectVCountCallback(void);
extern void InitScanlineEffects(void);
extern void ClearScanlineEffectStaging(void);
extern void QueueScanlineEffectTable(const void *pEntries, u32 count);
extern void StartScanlineEffects(void);
extern u32 IsScanlineEffectQueueIdle(void);
