#include "types.h"
#include "pop_it_minigame.h"
#include "gen/graphics/minigames/wizard_cracker.h"

const u32 g_dwWizardCrackerPopItBg1Control = 0x1F03;
const u32 g_dwWizardCrackerPopItBg2Control = 0x1E06;
const u32 g_dwWizardCrackerPopItBg0Control = 0x1D09;
const u32 g_dwWizardCrackerPopItBg3Control = 0x1C0C;

const WizardCrackerPopItPaletteEntry g_aWizardCrackerPopItPalettes[WIZARD_CRACKER_POP_IT_KINDS] = {
    { gWizardCrackerWrappedPalette,  12, 10 },
    { gWizardCrackerTrianglePalette, 13, 11 },
    { gWizardCrackerOvalPalette,     14,  8 },
    { gWizardCrackerDumbbellPalette, 15,  7 },
    { gWizardCrackerSweetPalette,     6,  9 },
};
