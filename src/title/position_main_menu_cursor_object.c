#include "types.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "menu/minigame_menu.h"
#include "title.h"

void PositionMainMenuCursorObject(u32 tween)
{
    u32 slot;

    // Load Game's row is skipped when it is unavailable.
    slot = g_GameModeStackContext.dwModeScratchB;
    if (!g_MainMenuState.dwLoadGameAvailable && slot > 1)
        slot--;

    if (tween)
        SetObjectMoveTargetWithDuration_candidate(g_MainMenuState.pCursorObject, 0x10, slot * 0xC + 0x5B, 3);
    else
        SetMenuCursorPosition(g_MainMenuState.pCursorObject, 0x10, slot * 0xC + 0x5B);
}
