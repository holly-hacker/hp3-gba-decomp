#include "pause_menu.h"
#include "pause_menu_inline.h"

void StartMenuFadeOut(void)
{
    g_GameModeStackContext.dwModeSubState = 0;
    StartMenuFade();
}
