#include "types.h"
#include "font.h"
#include "graphics/text.h"
#include "menu/folio_bruti.h"

void DrawFolioBrutiHeading(void)
{
    u32 tileCursor;

    SelectTextFont(3, 0, -1);
    tileCursor = DrawStringAligned(1, 0x78, 2, GetDialogText(0x4A0), 1);  // "Folio Bruti"
    g_FolioBrutiState.dwHeadingTileCursor = tileCursor;
    g_FolioBrutiState.dwDetailTileCursor = DrawFolioBrutiSpellLabels(tileCursor);
}
