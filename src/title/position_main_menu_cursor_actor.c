#include "types.h"
#include "modes.h"
#include "minigame_menu.h"
#include "title.h"
#include "cursor.h"

void PositionMainMenuCursorActor(u32 tween)
{
    u32 slot;

    // Load Game's row is skipped when it is unavailable.
    slot = g_GameModeStackContext.dwModeScratchB;
    if (!g_MainMenuState.dwLoadGameAvailable && slot > 1)
        slot--;

    if (tween)
        SetActorMoveTargetWithDuration(g_MainMenuState.pCursorActor, 0x10, slot * 0xC + 0x5B, 3);
    else
        SetMenuCursorPosition(g_MainMenuState.pCursorActor, 0x10, slot * 0xC + 0x5B);
}
