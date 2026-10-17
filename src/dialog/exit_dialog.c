#include "background.h"
#include "actor.h"
#include "dialog.h"
#include "cursor.h"
#include "video.h"
#include "hero.h"

void ExitDialog(void)
{
    SetActorActionState(g_pPlayerActor, g_pPlayerActor->bPrevActionState_candidate);
    FreeActor(g_pDialogPortraitActor);
    ReleaseMenuCursor(g_pDialogCursorActor);
    g_pDialogCursorActor = NULL;
    ClearScanlineEffects();
    StopScanlineEffects();
    g_DialogState_candidate.dwState = 2;
    SetBgPriority(0, g_adwSavedBgPriority[0]);
    SetBgPriority(1, g_adwSavedBgPriority[1]);
}
