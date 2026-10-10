#include "types.h"
#include "font.h"
#include "graphics/text.h"
#include "menu/folio_universitas.h"

#ifdef VERSION_JP
#define CATEGORY_FONT 0xB
#else
#define CATEGORY_FONT 1
#endif

void DrawFolioUniversitasHeadings(void)
{
    u32 tileCursor;
    u32 category;

    SelectTextFont(3, 0, -1);
    DrawStringAligned(1, 0x78, 4, GetDialogText(0x40D), 1);  // "Folio Universitas"

    SelectTextFont(CATEGORY_FONT, 3, -1);
    tileCursor = 0xE7;
    for (category = 0; category < 6; category++)
        tileCursor = DrawString(tileCursor, 8, 0x20 + category * 8, GetDialogText(0x405 + category));
}
