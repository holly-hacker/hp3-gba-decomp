#include "types.h"
#include "background.h"
#include "color.h"
#include "pop_it_minigame.h"
#include "gen/graphics/menus.h"

// Pulses the selected-cracker palette slots 7-11.
void StartWizardCrackerPopItPaletteEffects(void)
{
    s32 i;

    for (i = 0; i < WIZARD_CRACKER_POP_IT_KINDS; i++)
        StartPaletteEffectWithFrameCount(0x70 + i * 16, 16, 15, 0, 0x1D,
                                         GRAPHIC_BLOB_PALETTE_COLORS(gMenuSelectionPalette) + 0x60 + i * 0x20, 2);
}
