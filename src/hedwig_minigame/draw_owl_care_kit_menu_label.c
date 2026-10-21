#include "types.h"
#include "background.h"
#include "font.h"
#include "modes.h"
#include "text.h"
#include "hedwig_minigame.h"

void DrawOwlCareKitMenuLabel(void)
{
    CopyBgTilemapRectByCell(0, g_BgState.aLayers[0].pTilemap, 0x156, 0, 0, 8, 0, 8, 10, 2);
    SelectTextFont(2, 0, -1);
    // 0x669: "Feed", the first of the 8 menu entries
    DrawStringAligned(0x28C, 0x28, 0x42, GetDialogText(0x669 + g_GameModeStackContext.dwModeScratchB), 1);
    g_OwlCareKitScreen.bShownSelection = g_GameModeStackContext.dwModeScratchB;
}
