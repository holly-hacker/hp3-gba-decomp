#include "types.h"
#include "combat.h"
#include "combat_dispatch.h"
#include "mem.h"

// Clears OBJ palettes 0-3 of the battle palette buffer.
void ClearStatsPortraitPalette(void)
{
    memset(&g_pFightState->awPalette[256], 0, 4 * 16 * sizeof(u16));
}
