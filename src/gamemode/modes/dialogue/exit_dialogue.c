#include "types.h"
#include "graphics/display.h"
#include "graphics/object.h"
#include "menu/dialog.h"
#include "menu/main_menu.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void ExitDialogue(void)
{
    SetObjectActionState(g_pPlayerObject, g_pPlayerObject->bPrevActionState_candidate);
    FreeObject(g_pDialogBoxObject);
    ReleaseMenuCursor(g_pDialogCursorObject);
    g_pDialogCursorObject = NULL;
    ClearScanlineEffects();
    StopScanlineEffects();
    g_DialogState_candidate.dwState = 2;
    SetBgPriority(0, g_adwSavedBgPriority[0]);
    SetBgPriority(1, g_adwSavedBgPriority[1]);
}
