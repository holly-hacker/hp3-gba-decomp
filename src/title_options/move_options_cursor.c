#include "types.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "actor.h"
#include "default_menu.h"
#include "title_options_inline.h"

void MoveOptionsCursor(void)
{
    u32 previous;

    previous = g_GameModeStackContext.dwModeScratchB;
    StepCursorUpDownHeld(&g_GameModeStackContext.dwModeScratchB, 0, OPTIONS_ROW_COUNT - 1, 1, 0);
    DrawOptionsRowLabel(previous, g_GameModeStackContext.dwModeScratchB);
    DrawOptionsRowLabel(g_GameModeStackContext.dwModeScratchB, g_GameModeStackContext.dwModeScratchB);
    SetActorMoveTargetWithDuration(g_pMenuCursorActor,
                                   g_aOptionsMenuItems[g_GameModeStackContext.dwModeScratchB].nX - 14,
                                   g_aOptionsMenuItems[g_GameModeStackContext.dwModeScratchB].nY + 8, 4);
    DrawOptionsLanguageHint();
    PlaySoundById(0);
}
