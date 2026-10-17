#include "types.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "pause_menu.h"

void MoveListMenuCursor(void)
{
    u32 previous;

    previous = g_GameModeStackContext.dwModeScratchB;
    StepCursorUpDownHeld(&g_GameModeStackContext.dwModeScratchB, 0,
                         g_ListMenuState.pDefinition->wEntryCount - 1, 1, 0);
    DrawListMenuRow(previous);
    DrawListMenuRow(g_GameModeStackContext.dwModeScratchB);
    PlaySoundById(0);
}
