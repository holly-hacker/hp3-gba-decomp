#include "types.h"
#include "background.h"
#include "default_menu.h"

void LoadMenuScreenOverlay(const u8 *pGraphic, u32 x, u32 y)
{
    if (pGraphic != NULL)
    {
        SetBgControl(1, g_dwCommonBg1Control);
        FillBgTilemapWithTile(1, MENU_SCREEN_OVERLAY_FILL_TILE);
        LoadGraphicBlob(1, pGraphic, MENU_SCREEN_OVERLAY_TILE_OFFSET, 0, x, y);
        SetBgScroll(1, 0, 0);
    }
}
