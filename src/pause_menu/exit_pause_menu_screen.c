#include "background.h"
#include "pause_menu.h"
#include "default_menu.h"

void ExitPauseMenuScreen(void)
{
    ClearBgTilemap(2);
    ExitMenuScreen();
}
