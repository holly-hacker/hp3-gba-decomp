#include "types.h"
#include "modes.h"
#include "input.h"
#include "minigame_menu.h"
#include "landmarks.h"

void UpdateUnusedHogwartsMapScreen(void)
{
    u32 prevEntry = g_GameModeStackContext.dwCurrentGameModeArg2;

    if (g_GameModeStackContext.dwModeState != 0)
        return;

    if (StepCursorUpDown(&g_GameModeStackContext.dwCurrentGameModeArg2, 0,
                         UNUSED_HOGWARTS_MAP_ENTRY_COUNT - 1, 1, 0))
    {
        sub_080280CC();
        SetActorMoveTargetWithDuration(g_apUnusedHogwartsMapActors[prevEntry], 0xDA,
                                                  (s16)(g_apUnusedHogwartsMapActors[prevEntry]->pos.y >> 16), 3);
        SetActorMoveTargetWithDuration(
            g_apUnusedHogwartsMapActors[g_GameModeStackContext.dwCurrentGameModeArg2], 0xD2,
            (s16)(g_apUnusedHogwartsMapActors[g_GameModeStackContext.dwCurrentGameModeArg2]->pos.y >> 16), 3);
        sub_08028240();
    }
    else if (g_wKeysPressed & KeyB)
    {
        PushGameMode_2(MinigameDifficultySelect, 6, 0);
    }
}
