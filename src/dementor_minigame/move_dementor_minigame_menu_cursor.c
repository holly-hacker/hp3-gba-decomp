#include "actor.h"
#include "modes.h"
#include "dementor_minigame.h"

void MoveDementorMinigameMenuCursor(Actor *pCursor)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case DementorMinigameStateResultsMenu:
    case DementorMinigameStatePauseMenu:
        SetActorMoveTargetWithDuration(pCursor, 0x78, g_GameModeStackContext.dwModeScratchB * 16 + 0x48,
                                       4);
        break;
    }
}
