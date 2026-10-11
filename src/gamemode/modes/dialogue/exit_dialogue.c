#include "types.h"
#include "graphics/display.h"
#include "actor.h"
#include "menu/dialog.h"
#include "menu/main_menu.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void ExitDialogue(void)
{
    SetActorActionState(g_pPlayerActor, g_pPlayerActor->bPrevActionState_candidate);
    FreeActor(g_pDialogBoxActor);
    ReleaseMenuCursor(g_pDialogCursorActor);
    g_pDialogCursorActor = NULL;
    ClearScanlineEffects();
    StopScanlineEffects();
    g_DialogState_candidate.dwState = 2;
    SetBgPriority(0, g_adwSavedBgPriority[0]);
    SetBgPriority(1, g_adwSavedBgPriority[1]);
}
