#include "types.h"
#include "graphics/audio.h"
#include "game/game_modes.h"
#include "menu/menu.h"
#include "menu/minigame_menu.h"

void MoveListMenuCursor(void)
{
    u32 previous;

    previous = g_GameModeStackContext.dwModeScratchB;
    sub_08025A18(&g_GameModeStackContext.dwModeScratchB, 0,
                 g_ListMenuState.pDefinition->wEntryCount - 1, 1, 0);
    DrawListMenuRow(previous);
    DrawListMenuRow(g_GameModeStackContext.dwModeScratchB);
    PlaySoundById(0);
}
