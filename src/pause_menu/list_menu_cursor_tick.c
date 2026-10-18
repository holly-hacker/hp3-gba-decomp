#include "pause_menu.h"

// Moves the menu cursor to the selected row over two frames.
void ListMenuCursorTick(Actor *pActor)
{
    SetActorMoveTargetWithDuration(pActor,
                 g_ListMenuState.pDefinition->stride.x * g_GameModeStackContext.dwModeScratchB
                     + g_ListMenuState.pDefinition->base.x
                     + g_ListMenuState.pDefinition->cursorOffset.x,
                 g_ListMenuState.pDefinition->stride.y * g_GameModeStackContext.dwModeScratchB
                     + g_ListMenuState.pDefinition->base.y
                     + g_ListMenuState.pDefinition->cursorOffset.y,
                 2);
}
