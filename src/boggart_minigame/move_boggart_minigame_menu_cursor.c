#include "types.h"
#include "actor.h"
#include "game/game_modes.h"
#include "boggart_minigame.h"

void MoveBoggartMinigameMenuCursor(Actor *pCursor)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case BoggartMinigameStateResultsMenu:
    case BoggartMinigameStatePauseMenu:
        SetActorMoveTargetWithDuration(pCursor, 0x78, g_GameModeStackContext.dwModeScratchB * 16 + 0x48, 4);
        break;
    }
}
