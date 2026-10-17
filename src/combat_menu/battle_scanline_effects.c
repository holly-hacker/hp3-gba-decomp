#include "combat_menu.h"
#include "mode7.h"

const ScanlineEffectEntry g_aBattleScanlineEffects[4] = {
    { 0x00, 0, 0, 0, StartFloorAffineHBlankDma },
    { 0x20, 0, 0, 0, sub_08013360 },
    { 0x58, 0, 0, 0, sub_08013424 },
    { 0x70, 0, 0, 0, sub_080133AC },
};
