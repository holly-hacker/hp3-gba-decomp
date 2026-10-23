#include "types.h"
#include "modes.h"
#include "overworld/overworld.h"
#include "map.h"
#include "hero.h"
#include "main.h"

s32 TickOverworldControlSlots(void)
{
    if (g_OverworldControlState.bSlotCount > 1)
    {
        g_bControlSlotTicks++;
        g_dwGameModeFlags &= ~GameModeFlagUnk10000;
        g_dwGameModeFlags &= ~GameModeFlagUnk20000;
    }

    return 0;
}
