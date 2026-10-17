#include "types.h"
#include "modes.h"
#include "overworld/overworld.h"
#include "game_state.h"
#include "map.h"

// Overworld mode's pUpdateFn (per-frame tick). Room logic runs in the room's
// actors, so this only ticks the pause-menu cooldown and Owl Care Kit clock.
void UpdateOverworld(void)
{
    if (g_dwPauseMenuCooldown != 0)
        g_dwPauseMenuCooldown--;

    // TickOverworldControlSlots_candidate always returns 0, so the first branch is dead.
    if (TickOverworldControlSlots_candidate() == 1)
        g_dwGameModeFlags &= ~SerialSessionActive;
    else
        TickOwlCareKitFromOverworld();
}
