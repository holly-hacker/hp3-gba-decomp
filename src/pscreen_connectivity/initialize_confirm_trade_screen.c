#include "types.h"
#include "modes.h"
#include "font.h"
#include "text.h"
#include "pscreen_connectivity.h"
#include "pause_menu.h"
#include "default_menu.h"

void InitializeConfirmTradeScreen(void)
{
    g_GameModeStackContext.dwModeScratchB = 0;
    DrawMenuScreenTitle(0x538);  // "Trade Cards"
    BuildListMenu(&g_ConfirmTradeMenuDefinition);
    SelectTextFont(1, 0, -1);
    // "Completing a card trade will automatically save your game.  Do you wish to continue?"
    PrintTextBox(0xC1, 0x78, 0x30, 0x90, GetDialogText(0x8CC), 1);
    g_GameModeStackContext.dwModeState = 1;
    StartMenuFadeIn();
}
