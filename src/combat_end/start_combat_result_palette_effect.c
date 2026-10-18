#include "color.h"
#include "background.h"
#include "combat_end.h"
#include "gen/graphics/menus.h"

void StartCombatResultPaletteEffect(void)
{
    StartPaletteEffectWithFrameCount(7, 3, 8, 0x10, 0x19, GRAPHIC_BLOB_PALETTE_COLORS(gMenuSelectionPalette), 2);
}
