#include "types.h"
#include "game/game_modes.h"
#include "hw/input.h"
#include "menu/minigame_menu.h"
#include "menu/unused_hogwarts_map_screen.h"

void UpdateUnusedHogwartsMapScreen(void)
{
    u32 prevEntry = g_GameModeStackContext.dwCurrentGameModeArg2;

    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepWrappedSelectionVertical_candidate(&g_GameModeStackContext.dwCurrentGameModeArg2, 0,
                                               UNUSED_HOGWARTS_MAP_ENTRY_COUNT - 1, 1, 0))
    {
        sub_080280CC();
        SetObjectMoveTargetWithDuration_candidate(g_apUnusedHogwartsMapObjects[prevEntry], 0xDA,
                                                  (s16)(g_apUnusedHogwartsMapObjects[prevEntry]->nY >> 16), 3);
        SetObjectMoveTargetWithDuration_candidate(
            g_apUnusedHogwartsMapObjects[g_GameModeStackContext.dwCurrentGameModeArg2], 0xD2,
            (s16)(g_apUnusedHogwartsMapObjects[g_GameModeStackContext.dwCurrentGameModeArg2]->nY >> 16), 3);
        sub_08028240();
    }
    else if (g_wKeysPressed & KeyB)
    {
        PushGameMode_2(MinigameDifficultySelect, 6, 0);
    }
}
