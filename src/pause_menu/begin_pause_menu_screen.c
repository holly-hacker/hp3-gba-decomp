#include "background.h"
#include "interrupts.h"
#include "pause_menu.h"
#include "default_menu.h"
#include "sound.h"

void BeginPauseMenuScreen(u32 showObjective)
{
    RestoreDefaultVBlankCallback();
    LoadMenuScreenFrame(NULL, 0, 0);
    SetBgControl(1, g_dwCommonBg1Control);
    FillBgTilemapWithTile(1, MENU_SCREEN_OVERLAY_FILL_TILE);

    if (showObjective)
        DrawPauseMenuObjective();

    PlayMusicModule(3);
}
