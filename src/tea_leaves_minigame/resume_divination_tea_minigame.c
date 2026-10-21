#include "types.h"
#include "background.h"
#include "particles.h"
#include "cursor.h"
#include "tea_leaves_minigame.h"

void ResumeDivinationTeaMinigame(void)
{
    FillBgTilemapRect(0, 0, 8, 0x1E, 6, 0);
    ReleaseMenuCursor(g_DivinationTea.pCursorActor);
    g_DivinationTea.pCursorActor = NULL;
    FreeAllParticleEmitters();
    FreeAllParticles();
    g_DivinationTea.dwPaused = 0;
}
