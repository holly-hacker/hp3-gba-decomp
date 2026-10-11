#include "types.h"
#include "graphics/display.h"
#include "title.h"
#include "gen/graphics/menus.h"

void StartMainMenuPaletteEffect(void)
{
    g_MainMenuState.nPaletteEffectSlot =
        StartPaletteEffectWithFrameCount(7, 3, 8, 0x10, 0x19, GRAPHIC_BLOB_PALETTE_COLORS(gMenuSelectionPalette), 2);
}
