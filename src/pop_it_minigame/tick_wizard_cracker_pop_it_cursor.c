#include "types.h"
#include "actor.h"
#include "modes.h"
#include "pop_it_minigame.h"

void TickWizardCrackerPopItCursor(Actor *pCursor)
{
    switch (g_GameModeStackContext.dwModeState)
    {
    case WizardCrackerPopItStateSelect:
    case WizardCrackerPopItStatePopping:
    case WizardCrackerPopItStateSettling:
    case WizardCrackerPopItStateFadeIn:
    case WizardCrackerPopItStateRoundWon:
    case WizardCrackerPopItStateRoundLost:
        SetActorMoveTargetWithDuration(pCursor, g_pWizardCrackerPopIt->nCursorColumn * 24 + 28,
                                       g_pWizardCrackerPopIt->nCursorRow * 24 + 16, 4);
        break;
    case WizardCrackerPopItStatePauseMenu:
    case WizardCrackerPopItStateResultsMenu:
        SetActorMoveTargetWithDuration(pCursor, 120, g_GameModeStackContext.dwModeScratchB * 16 + 72, 4);
        break;
    }
}
