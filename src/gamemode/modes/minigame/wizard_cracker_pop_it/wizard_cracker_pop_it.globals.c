#include "types.h"
#include "minigame/wizard_cracker_pop_it.h"

const u32 g_dwWizardCrackerPopItBg1Control = 0x1F03;
const u32 g_dwWizardCrackerPopItBg2Control = 0x1E06;
const u32 g_dwWizardCrackerPopItBg0Control = 0x1D09;
const u32 g_dwWizardCrackerPopItBg3Control = 0x1C0C;

const WizardCrackerPopItPaletteEntry g_aWizardCrackerPopItPalettes[5] = {
    { gWizardCrackerPopItPalette001Palette, 12, 10 },
    { gWizardCrackerPopItPalette002Palette, 13, 11 },
    { gWizardCrackerPopItPalette003Palette, 14,  8 },
    { gWizardCrackerPopItPalette004Palette, 15,  7 },
    { gWizardCracker001Palette,              6,  9 },
};
