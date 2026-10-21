#include "types.h"
#include "actor.h"
#include "modes.h"
#include "tea_leaves_minigame.h"

void MoveDivinationTeaMenuCursor(Actor *pCursor)
{
    if (g_DivinationTea.dwPaused != 0 && g_DivinationTea.pCursorActor != NULL)
        SetActorMoveTargetWithDuration(pCursor, 0x78, g_GameModeStackContext.dwModeScratchB * 16 + 0x48, 4);
}
