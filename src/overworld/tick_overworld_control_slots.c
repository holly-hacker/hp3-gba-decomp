#include "types.h"
#include "game_modes.h"
#include "overworld.h"

s32 TickOverworldControlSlots_candidate(void)
{
    if (g_OverworldControlState.bSlotCount > 1)
    {
        g_bControlSlotTicks_candidate++;
        g_dwGameModeFlags &= ~0x10000;
        g_dwGameModeFlags &= ~0x20000;
    }

    return 0;
}
