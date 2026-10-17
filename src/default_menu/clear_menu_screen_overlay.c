#include "background.h"
#include "default_menu.h"

void ClearMenuScreenOverlay(void)
{
    FillBgTilemapWithTile(1, MENU_SCREEN_OVERLAY_FILL_TILE);
}
