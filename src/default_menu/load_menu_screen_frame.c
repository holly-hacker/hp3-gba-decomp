#include "types.h"
#include "background.h"
#include "default_menu.h"
#include "gen/graphics/cutscenes.h"

void LoadMenuScreenFrame(const u8 *pOverlayGraphic, u32 overlayX, u32 overlayY)
{
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwCommonBg0Control);
    SetBgControl(2, g_dwCommonBg2Control);
    LoadEmbeddedPalette(gMenuBg3Graphic, 0, 16);
    LoadGraphicBlob(0, gMenuScreenFrameGraphic, 0, 0, 0, 0);
    SetBgScroll(0, 8, 0);
    LoadMenuScreenOverlay(pOverlayGraphic, overlayX, overlayY);
}
