#include "types.h"
#include "cutscene/lupin_potion_cutscene.h"
#include "graphics/scanline_effects.h"

const ScanlineEffectEntry g_aLupinPotionScanlineTable[2] = {
    { 120, 0, 1, 0, LupinPotionPanelScanlineCallback_candidate },
    { 159, 0, 0, 0, LupinPotionPanelScanlineCallback_candidate },
};

const u32 g_dwLupinPotionBg3Control = 0x4603;
const u32 g_dwLupinPotionBg1Control = 0x5E07;
const u32 g_dwLupinPotionTextBgControl = 0x560B;  // BG2
const u32 g_dwLupinPotionBg0Control = 0x0F0F;
