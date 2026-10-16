#include "types.h"
#include "color.h"
#include "cursor.h"
#include "graphics/display.h"
#include "gen/graphics/menus.h"

void LoadMenuCursor8bppColors(void)
{
    u32 i;

    for (i = 3; i < 16; i++)
        QueueObjPaletteLoadAtOffset(gMenuPalette001Palette, i * 32, i * 16, 1);
}
