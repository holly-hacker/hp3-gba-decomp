#include "types.h"
#include "modes.h"
#include "default_menu.h"
#include "screen_transitions.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "title_load.h"
#include "title_new.h"

// Shared by the New Game and Load Game screens.
void InitializeSaveSlotScreen(u32 titleStringId)
{
    g_GameModeStackContext.dwModeScratchB = 0;
    g_GameModeStackContext.dwModeTimer = 0;
    g_GameModeStackContext.dwModeState = 0;
    InitializeMenuScreen(titleStringId, 9, 1, gMenuScreenGraphic, 0, 1);
    SpawnSaveSlotActors();
    DrawSaveSlots();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
