#include "types.h"
#include "game_modes.h"
#include "overworld.h"

// Overworld mode's pUpdateFn (per-frame tick). Room logic runs in the room's
// objects, so this only ticks the pause-menu cooldown and Owl Care Kit clock.
void UpdateOverworld(void)
{
    if (g_dwPauseMenuCooldown != 0)
        g_dwPauseMenuCooldown--;

    // TickOverworldControlSlots_candidate always returns 0, so the first branch is dead.
    if (TickOverworldControlSlots_candidate() == 1)
        g_dwGameModeFlags &= ~LinkSessionActive;
    else
        TickOwlCareKitFromOverworld();
}
