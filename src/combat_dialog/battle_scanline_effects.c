#include "combat_dialog.h"
#include "combat_effects_hblank.h"
#include "mode7.h"

const ScanlineEffectEntry g_aBattleScanlineEffects[4] = {
    { 0x00, 0, 0, 0, StartFloorAffineHBlankDma },
    { 0x20, 0, 0, 0, EndBattleWallScanline },
    { 0x58, 0, 0, 0, RestoreBattleHudPanelTilemap },
    { 0x70, 0, 0, 0, BeginBattleHudScanline },
};
