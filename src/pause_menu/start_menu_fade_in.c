#include "pause_menu.h"
#include "pause_menu_inline.h"

void StartMenuFadeIn(void)
{
    g_GameModeStackContext.dwModeSubState = 0x10;
    StartMenuFade();
}
