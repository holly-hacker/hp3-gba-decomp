#include "types.h"
#include "combat_fx_script.h"
#include "combat_fx.h"

// BG control words RegisterBgTileAnimation takes for an effect BG record's animation,
// chosen by the BG it targets: BG2, BG1, BG0, BG3.
const u32 g_adwEffectBgControls[4] = { 0x0E02, 0x0F08, 0x0D08, 0x0C00 };

// Scanline effect tables queued by the QueueScanlineEffect script opcode;
// each is followed by unused null entries.
const ScanlineEffectEntry g_aEffectScanlineTable0[6] = {
    {   0, 0, 0, 0, EffectScanlineStopHBlankDma },
    {  88, 0, 0, 0, EffectScanlineCopyTilemap },
    { 112, 0, 0, 0, BeginEffectHudScanline },
    { 160, 0, 0, 0, EffectScanlineEnableBlend },
};

const ScanlineEffectEntry g_aEffectScanlineTable1[9] = {
    {   0, 0, 0, 0, EffectScanlineSetBandScroll },
    {  15, 0, 0, 1, EffectScanlineSetBandScroll },
    {  23, 0, 0, 2, EffectScanlineSetBandScroll },
    {  31, 0, 0, 3, EffectScanlineSetBandScroll },
    {  64, 0, 0, 0, EffectScanlineCopyTilemap },
    { 112, 0, 0, 0, BeginEffectHudScanline },
    { 125, 0, 0, 0, EffectScanlineAdvanceScroll },
    { 160, 0, 0, 0, EffectScanlineEnableBlend },
};

const ScanlineEffectEntry g_aEffectScanlineTable2[6] = {
    {   0, 0, 0, 0, EffectScanlineRestoreBgs },
    {  88, 0, 0, 0, EffectScanlineCopyTilemap },
    { 112, 0, 0, 0, BeginEffectHudScanline },
    { 160, 0, 0, 0, EffectScanlineEnableBlend },
};

const ScanlineEffectEntry *const g_apEffectScanlineTables[3] = {
    g_aEffectScanlineTable0,
    g_aEffectScanlineTable1,
    g_aEffectScanlineTable2,
};

// Entry counts queued for each table.
const u8 g_abEffectScanlineTableSizes[3] = { 4, 8, 4 };
