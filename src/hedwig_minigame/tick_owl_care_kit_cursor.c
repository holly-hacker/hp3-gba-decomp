#include "types.h"
#include "actor.h"
#include "modes.h"
#include "hedwig_minigame.h"

// Glides under the selected menu entry; see DrawOwlCareKitMenuIcon.
void TickOwlCareKitCursor(Actor *pCursor)
{
    u32 column;

    if (pCursor->wActionVariant == 0)
    {
        column = g_GameModeStackContext.dwModeScratchB * 3 + 1;
        if (g_GameModeStackContext.dwModeScratchB > 5)
            column = g_GameModeStackContext.dwModeScratchB * 3 + 6;
        SetActorPosition(pCursor, column * 8 + 12, 156);
        pCursor->wActionVariant = 1;
    }

    column = g_GameModeStackContext.dwModeScratchB * 3 + 1;
    if (g_GameModeStackContext.dwModeScratchB > 5)
        column = g_GameModeStackContext.dwModeScratchB * 3 + 6;
    SetActorMoveTargetWithDuration(pCursor, column * 8 + 12, 156, 5);
}
