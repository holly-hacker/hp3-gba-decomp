#include "types.h"
#include "battle/effect_script.h"

// BG control words sub_0800A598 takes for an effect BG record's animation,
// chosen by the BG it targets.
const u32 g_adwEffectBgControlOverride_candidate[4] = { 0x0E02, 0x0F08, 0x0D08, 0x0C00 };

// Scanline effect tables queued by the QueueScanlineEffect script opcode;
// each is followed by unused null entries.
const ScanlineEffectEntry g_aEffectScanlineTable0[6] = {
    {   0, 0, 0, 0, sub_0801BA44 },
    {  88, 0, 0, 0, sub_0801B9F4 },
    { 112, 0, 0, 0, sub_0801B130 },
    { 160, 0, 0, 0, sub_0801BA2C },
};

const ScanlineEffectEntry g_aEffectScanlineTable1[9] = {
    {   0, 0, 0, 0, sub_0801B9BC },
    {  15, 0, 0, 1, sub_0801B9BC },
    {  23, 0, 0, 2, sub_0801B9BC },
    {  31, 0, 0, 3, sub_0801B9BC },
    {  64, 0, 0, 0, sub_0801B9F4 },
    { 112, 0, 0, 0, sub_0801B130 },
    { 125, 0, 0, 0, sub_0801B998 },
    { 160, 0, 0, 0, sub_0801BA2C },
};

const ScanlineEffectEntry g_aEffectScanlineTable2[6] = {
    {   0, 0, 0, 0, sub_0801B950 },
    {  88, 0, 0, 0, sub_0801B9F4 },
    { 112, 0, 0, 0, sub_0801B130 },
    { 160, 0, 0, 0, sub_0801BA2C },
};

const ScanlineEffectEntry *const g_apEffectScanlineTables_candidate[3] = {
    g_aEffectScanlineTable0,
    g_aEffectScanlineTable1,
    g_aEffectScanlineTable2,
};

// Entry counts queued for each table.
const u8 g_abEffectScanlineTableSizes_candidate[3] = { 4, 8, 4 };
