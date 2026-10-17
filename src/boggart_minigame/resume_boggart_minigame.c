#include "background.h"
#include "particles.h"
#include "font.h"
#include "modes.h"
#include "boggart_minigame.h"
#include "cursor.h"

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
