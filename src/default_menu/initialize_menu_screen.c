#include "types.h"
#include "default_menu.h"

void InitializeMenuScreen(u32 titleStringId, u32 cursorKind, u32 pulseSelection,
                          const u8 *pOverlayGraphic, u32 overlayX, u32 overlayY)
{
    LoadMenuScreenFrame(pOverlayGraphic, overlayX, overlayY);
    BeginMenuScreen(titleStringId, cursorKind, pulseSelection);
}
