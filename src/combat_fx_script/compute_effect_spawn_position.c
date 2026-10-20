#include "types.h"
#include "combat_fx.h"
#include "combat_fx_script.h"

// Screen position of the effect's slot: slots 0-2 share one, 3-4 and 5+ have their own.
IntPoint ComputeEffectSpawnPosition(void)
{
    IntPoint pos;

    if (g_effectStaging.bSlotParam <= 2)
    {
        pos.x = 176;
        pos.y = 114;
    }
    else if (g_effectStaging.bSlotParam <= 4)
    {
        pos.x = 48;
        pos.y = 80;
    }
    else
    {
        pos.x = 64;
        pos.y = 80;
    }
    return pos;
}
