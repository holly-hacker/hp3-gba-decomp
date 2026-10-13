#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "menu/main_menu.h"
#include "font.h"
#include "game/game_modes.h"
#include "boggart_minigame.h"

void ResumeBoggartMinigame(void)
{
    FillBgTilemapRect(3, 0, 8, 0x1E, 6, 0);
    SelectTextFont(5, 0, -1);
    ReleaseMenuCursor(g_BoggartMinigame.pCursorActor);
    g_BoggartMinigame.pCursorActor = NULL;
    FreeAllParticles();
    StartBoggartMinigameBoggartMotion();
    g_GameModeStackContext.dwModeState = BoggartMinigameStateInput;
}
