#include "types.h"
#include "menu/choose_character.h"

const ScanlineEffectEntry g_aChooseCharacterScanlineEffects[2] = {
    { 0x3F, 0, 0, 0, BeginChooseCharacterPanelScanline },
    { 0x7F, 0, 0, 0, EndChooseCharacterPanelScanline },
};
