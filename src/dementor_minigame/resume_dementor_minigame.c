#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "particles.h"
#include "font.h"
#include "modes.h"
#include "dementor_minigame.h"
#include "cursor.h"

void ResumeDementorMinigame(void)
{
    s32 direction;

    FillBgTilemapRect(3, 0, 8, 0x1E, 6, 0);
    SelectTextFont(5, 0, -1);
    ReleaseMenuCursor(g_DementorMinigame.pCursorActor);
    g_DementorMinigame.pCursorActor = NULL;
    FreeAllParticles();

    for (direction = 0; direction < 4; direction++)
    {
        switch (g_DementorMinigame.adwDementorStates[direction])
        {
        case DementorIdle:
            break;
        case DementorApproaching:
            StartDementorMinigameDementorApproach(direction);
            break;
        case DementorRetreating:
            StartDementorMinigameDementorRetreat(direction);
            break;
        }
    }

    g_GameModeStackContext.dwModeState = DementorMinigameStatePlaying;
}
