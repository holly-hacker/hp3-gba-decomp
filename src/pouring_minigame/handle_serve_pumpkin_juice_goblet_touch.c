#include "types.h"
#include "actor.h"
#include "modes.h"
#include "pouring_minigame.h"

// The bartender catches an empty goblet for points.
void HandleServePumpkinJuiceGobletTouch(Actor *goblet, Actor *other)
{
    if (g_GameModeStackContext.dwModeState == ServePumpkinJuiceStatePlaying
        && other->bKind == ServePumpkinJuiceActorBartender
        && g_ServePumpkinJuice.dwLane == goblet->bActionSubState
        && goblet->bActionState <= 1)
    {
        if (goblet->bKind == ServePumpkinJuiceActorEmptyGoblet)
        {
            g_ServePumpkinJuice.dwScore += (2 << g_GameModeStackContext.dwCurrentGameModeArg3) * 20;
            g_ServePumpkinJuice.dwScoreChanged = 1;
        }

        goblet->bActionState = 4;
    }
}
