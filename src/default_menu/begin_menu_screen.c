#include "types.h"
#include "background.h"
#include "color.h"
#include "cursor.h"
#include "default_menu.h"
#include "gen/graphics/menus.h"

void BeginMenuScreen(u32 titleStringId, u32 cursorKind, u32 pulseSelection)
{
    ClearBgTilemap(2);
    DrawMenuScreenTitle(titleStringId);

    if (cursorKind != MENU_SCREEN_NO_CURSOR)
    {
        g_pMenuCursorActor = SpawnMenuCursorActor(cursorKind);
        SetMenuCursorPosition(g_pMenuCursorActor, 0, 0);
    }
    else
    {
        g_pMenuCursorActor = NULL;
    }

    if (pulseSelection)
        g_nMenuScreenPaletteEffectSlot = StartPaletteEffectWithFrameCount(
            6, 3, 8, 0x10, 0x19, GRAPHIC_BLOB_PALETTE_COLORS(gMenuSelectionPalette), 2);
    else
        g_nMenuScreenPaletteEffectSlot = -1;
}
